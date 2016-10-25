typedef struct node {
    void *val;
    struct node *next;
} node_t;

node_t *new_list();
void add_start(node_t **head, void *val);
void add_end(node_t **head, void *val);
void *remove_first(node_t **head);
void *remove_last(node_t **head);
void *getelement(node_t *head, int n);
void clear_list(node_t **head);