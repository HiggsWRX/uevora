#include "linkedlist.h"

typedef struct inst {
    int code;
    int var;
} inst;

typedef struct pcb {
    int pid;        // process id
    int at;         // arrive time
    int mem_ptr;
    int pc;
    int cb;         // cicles blocked
    int fn;         // process from new
    int num_inst;
    node_t *instruction_list;
} pcb;

typedef struct state {
    int num_processes;
    node_t *process_list;
} state;
pcb *new_pcb(int at);
pcb *fork_pcb(pcb *p);
inst *new_inst(int op, int var);
state *new_state();
void create_process();
void move_process(state **s1, state **s2);
void add_process(state **s, pcb *p);
int run_process(void **mem, pcb **p);