#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#define QUANTUM 4
#define MAXNEWREADY 4
#define MEMSPACE 300
#define TYPEFIT 1    // Best fit 1, Worst fit 0
#define DEBUGPRINT 1 // Normal 0, Debug Print 1
// TODO ESTRUTURA GERIR MEM;

int read_input(char *file_name, state **cache)
{
    FILE *input;
    char *line = NULL;
    char *token;
    char *half = malloc(2);
    char *half2 = malloc(2);
    int at, op, var;
    int i, j;
    size_t len = 0;
    ssize_t read;
    node_t *inst_list;
    inst *temp_inst;
    pcb *temp_process;

    input = fopen(file_name, "r");
    j = 0;
    while(read = getline(&line, &len, input) != -1) {
        token = strtok(line, " ");
        at = atoi(token);
        i = 0;
        inst_list  = new_list();

        while (token) {
            token = strtok(NULL, " ");
            if(token) {
                if (strlen(token) == 4) {
                    token[2] = 0;
                }
                memcpy(half, token, 1);
                half[1] = '\0';
                memcpy(half2, token + 1, 1);
                half2[1] = '\0';
                op = atoi(half);
                var = atoi(half2);
                temp_inst = new_inst(op, var);
                add_end(&inst_list, temp_inst);
                i++;
            }
        }

        temp_process = new_pcb(at);
        temp_process->instruction_list = inst_list;
        temp_process->num_inst = i;
        add_end(&(*cache)->process_list, temp_process);
        j++;
    }

    free(half);
    free(half2);
    free(line);
    fclose(input);

    return j;
}

void refresh_blocked(state **s)
{
    int i;
    pcb *current;
    for (i = 0; i < (*s)->num_processes; i++) {
        current = (pcb *)getelement(((*s)->process_list), i);
        current->cb--;
    }
}

int scan_worst_fit(void **mem, int required)
{
    int block_size = 0;
    int reset = 0;
    int max_block_size_found = 0;
    int block_start = -1;
    int ret_val = -1;
    int i;

    for (i = 0; i < MEMSPACE; i++) {
        if (mem[i] == NULL) {
            block_size++;
            if (block_start == -1) {
                block_start = i;
            }
        } else {
            block_start = -1;
            block_size = 0;
        }
        if (block_size > max_block_size_found) {
            max_block_size_found = block_size;
            ret_val = block_start;
        }
    }

    if (max_block_size_found < required) {
        ret_val = -1;
    }

    return ret_val;
}

int scan_best_fit(void **mem, int required)
{
    int block_size = 0;
    int reset = 0;
    int found = 0;
    int min_block_size_found = 0;
    int block_start = -1;
    int ret_val = -1;
    int i;

    for (i = 0; i < MEMSPACE; i++) {
        if (mem[i] == NULL) {
            block_size++;
            if (block_start == -1) {
                block_start = i;
            }
        } else {
            if (block_size > 0 && block_size >= required) {
                if (found) {
                    if (block_size < min_block_size_found && block_size >= required) {
                        min_block_size_found = block_size;
                        ret_val = block_size;
                    }
                } else {
                    min_block_size_found = block_size;
                    ret_val = block_start;
                    found = 1;
                }
            }
            block_start = -1;
            block_size = 0;
        }
    }

    if (!found && block_size > required) {
        ret_val = block_start;
    }

    return ret_val;
}

void load_to_memory(void **mem, pcb **p)
{
    int i;
    int j;
    int *var;
    int start;
    if (TYPEFIT) {
        start = scan_best_fit(mem, (10 + (*p)->num_inst));
    } else {
        start = scan_worst_fit(mem, (10 + (*p)->num_inst));
    }
    if (start == -1) {
        printf("ERROR: no memory block big enough available\n");
        return;
    }

    start = start + 10;
    for (i = start - 10, j = 0; i < start; i++, j++) {
        var = malloc(sizeof(var));
        *var = -1;
        mem[i] = var;
    }
    for (i = start; i < (start + (*p)->num_inst); i++) {
        mem[i] = (inst *)remove_first(&((*p)->instruction_list));
    }

    (*p)->mem_ptr = start;
}

void free_from_memory(void **mem, pcb *p)
{
    int i;

    for (i = (p->mem_ptr - 10); i < (p->mem_ptr + p->num_inst); i++) {
        //free(mem[i]);
        mem[i] = NULL;
    }
}

void initialise_memory(void **mem)
{
    int i;
    for (i = 0; i < MEMSPACE; i++) {
        mem[i] = NULL;
    }
}

void print_memory(void **mem)
{
    int i;
    int j = 0;
    int type = 0;
    inst *it;
    for (i = 0; i < MEMSPACE; i++) {
        if (mem[i] != NULL) {
            if (!type) {
                printf("(%d) ", *(int*)mem[i]);
                j++;
                if (j == 10) {
                    type = 1;
                }
            } else {
                it = (inst*)mem[i];
                printf("[%d%d]", it->code, it->var);
                if (it->code == 9) {
                    type = 0;
                    j = 0;
                }
            }
        } else {
            printf("[  ]");
        }
    }
    printf("\n");
}

void print_states(state *new, state *ready, state *run, state *exits, state *blocked)
{
    int i;
    node_t *p;
    printf("PIDs on New:");
    if (new->num_processes > 0) {
        p = new->process_list;
        for (i = 0; i < new->num_processes; i++) {
            printf(" %d ", ((pcb*)p->val)->pid);
            p = p->next;
        }
        printf("\n");
    } else {
        printf(" N/A\n");
    }

    printf("PIDs on Ready:");
    if (ready->num_processes > 0) {
        p = ready->process_list;
        for (i = 0; i < ready->num_processes; i++) {
            printf(" %d ", ((pcb*)p->val)->pid);
            p = p->next;
        }
        printf("\n");
    } else {
        printf(" N/A\n");
    }

    printf("PIDs on Run:");
    if (run->num_processes > 0) {
        p = run->process_list;
        for (i = 0; i < run->num_processes; i++) {
            printf(" %d ", ((pcb*)p->val)->pid);
            p = p->next;
        }
        printf("\n");
    } else {
        printf(" N/A\n");
    }

    printf("PIDs on Blocked:");
    if (blocked->num_processes > 0) {
        p = blocked->process_list;
        for (i = 0; i < blocked->num_processes; i++) {
            printf(" %d ", ((pcb*)p->val)->pid);
            p = p->next;
        }
        printf("\n");
    } else {
        printf(" N/A\n");
    }

    printf("PIDs on Exit:");
    if (exits->num_processes > 0) {
        p = exits->process_list;
        for (i = 0; i < exits->num_processes; i++) {
            printf(" %d ", ((pcb*)p->val)->pid);
            p = p->next;
        }
        printf("\n");
    } else {
        printf(" N/A\n");
    }
}

pcb *fork_process(void **mem, pcb **p, int instant)
{
    int i;
    int j = 0;
    int inst_start = (*p)->mem_ptr + (*p)->pc;
    int var_start = (*p)->mem_ptr - 10;
    node_t *inst_list = new_list();
    inst *it;
    pcb *aux = fork_pcb(*p);
    for (i = inst_start; i < (inst_start + aux->num_inst); i++) {
        // it = new_inst();
        add_end(&inst_list, mem[i]);
    }
    aux->instruction_list = inst_list;
    load_to_memory(mem, &aux);

    for (i = aux->mem_ptr - 10; i < aux->mem_ptr; i++) {
        *(int*)mem[i] = *(int*)mem[var_start+j];
        j++;
    }

    if (!DEBUGPRINT) {
        printf("Process %d loaded to memory from fork. - cicle %d\n", aux->pid, instant);
        print_memory(mem);
        printf("-----------------------------------\n");
    }

    return aux;
}

int main() {
    char *file = "input.xpto";
    int instant = 0;
    int timeoncpu = 0;
    int all_done = 0;
    int from_new = 0;
    int num_debug = 0;
    int aux;
    void *MEM[MEMSPACE];
    pcb *temp_pcb;
    state *cache = new_state();
    state *new = new_state();
    state *ready = new_state();
    state *run = new_state();
    state *exits = new_state();
    state *blocked = new_state();
    int num_pcs = read_input(file, &cache);
    cache->num_processes = num_pcs;
    initialise_memory(MEM);

    while (!all_done) {
        // load process to memory
        if (cache->num_processes > 0) {
            temp_pcb = (pcb *)cache->process_list->val;
        }
        if (cache->num_processes > 0 && temp_pcb->at <= instant) {
            move_process(&cache, &new);
            load_to_memory(MEM, &temp_pcb);
            if (!DEBUGPRINT) {
                printf("Process %d loaded to memory. - cicle %d\n", temp_pcb->pid, instant);
                print_states(new, ready, run, exits, blocked);
                print_memory(MEM);
                printf("-----------------------------------\n");
            }
        }
        // blocked to ready
        if (blocked->num_processes > 0) {
            temp_pcb = (pcb *)blocked->process_list->val;
        }
        if (blocked->num_processes > 0 && temp_pcb->cb == 0) {
            move_process(&blocked, &ready);
        }
        // new to ready
        if (new->num_processes > 0 && from_new <= MAXNEWREADY) {
            move_process(&new, &ready);
            from_new++;
        }
        // ready to run
        if (ready->num_processes > 0) {
            temp_pcb = (pcb *)ready->process_list->val;
        }
        if (ready->num_processes > 0 && run->num_processes == 0) {
            if (temp_pcb->fn) {
                temp_pcb->fn = 0;
                from_new--;
            }
            move_process(&ready, &run);
        }
        // run process
        if (run->num_processes > 0) {
            temp_pcb = (pcb *)run->process_list->val;
        }
        if (run->num_processes > 0) {
            aux = run_process(MEM, &temp_pcb);
            timeoncpu++;
            if (aux == 1) {
                move_process(&run, &blocked);
                temp_pcb->cb = 4;
                timeoncpu = 0;
            } else if (aux == 2) {
                move_process(&run, &exits);
                free_from_memory(MEM, temp_pcb);
                if (!DEBUGPRINT) {
                    printf("Process %d freed from memory. - cicle %d\n", temp_pcb->pid, instant);
                    print_states(new, ready, run, exits, blocked);
                    print_memory(MEM);
                    printf("-----------------------------------\n");
                }
                timeoncpu = 0;
            } else if (aux == 3) {
                add_process(&new, fork_process(MEM, &temp_pcb, instant));
                num_pcs++;
            }

            if (timeoncpu == QUANTUM) {
                move_process(&run, &ready);
                timeoncpu = 0;
            }
        }

        if (blocked->num_processes > 0) {
            refresh_blocked(&blocked);
        }

        if (exits->num_processes >= num_pcs) {
            all_done = 1;
        }

        if (DEBUGPRINT && num_debug < 10) {
            printf("Debug print of cicle %d\n", instant);
            print_states(new, ready, run, exits, blocked);
            print_memory(MEM);
            printf("-----------------------------------\n");
            num_debug++;
        }
        instant++;
    }

    return 0;
}