#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

pcb *new_pcb(int at)
{
    /* NOTE: static not thread safe */
    static int NUMPROCESS = 0;
    
    pcb *p = malloc(sizeof(pcb));
    p->pid = NUMPROCESS++;
    p->at = at;
    p->pc = 0;
    p->cb = 0;
    p->fn = 1;

    return p;
}

pcb *fork_pcb(pcb *p)
{
    pcb *ret = new_pcb(0);
    ret->fn = 0;
    ret->num_inst = p->num_inst - ret->pc;

    return ret;
}

inst *new_inst(int op, int var)
{
    inst *it = malloc(sizeof(inst));

    it->code = op;
    it->var = var;

    return it;
}

state *new_state()
{
    state *s = malloc(sizeof(s));
    s->num_processes = 0;
    s->process_list = new_list();

    return s;
}

void move_process(state **s1, state **s2)
{
    pcb *temp = (pcb *)remove_first(&(*s1)->process_list);
    (*s1)->num_processes -= 1;
    add_end(&(*s2)->process_list, temp);
    (*s2)->num_processes += 1;
}

void add_process(state **s, pcb *p)
{
    add_end(&(*s)->process_list, p);
    (*s)->num_processes += 1;
}

int run_process(void **mem, pcb **p)
{
    inst *it = (inst*)mem[((*p)->mem_ptr + (*p)->pc)];
    int opcode = it->code;
    int v = it->var;
    int *destination_var = (int*)mem[((*p)->mem_ptr) - (10 - v)];
    int state_transition = 0;

    switch (opcode) {
        case 0:
            *destination_var = 0;
            (*p)->pc += 1;
            break;
        case 1:
            *destination_var += 1;
            (*p)->pc += 1;
            break;
        case 2:
            *destination_var -= 1;
            (*p)->pc += 1;
            break;
        case 3:
            if (*destination_var == 0) {
                (*p)->pc += 1;
            } else {
                (*p)->pc += 2;
            }
            break;
        case 4:
            (*p)->pc -= v;
            break;
        case 5:
            (*p)->pc += v;
            break;
        case 6:
            state_transition = 3;
            (*p)->pc += 1;
            break;
        case 7:
            state_transition = 1;
            (*p)->pc += 1;
            break;
        case 8:
            *(int*)mem[((*p)->mem_ptr) - (10)] = *destination_var;
            (*p)->pc += 1;
            break;
        case 9:
            state_transition = 2;
            (*p)->pc += 1;
            break;
        default:
            printf("ERROR: Invalid Operation???\n");
            break;
    }

    return state_transition;

}