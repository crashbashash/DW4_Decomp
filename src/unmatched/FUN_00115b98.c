typedef struct Node {
    struct Node *next;
    volatile int id;
    int (*func)(int, int, int, int);
    int arg;
} Node;
extern Node *DAT_0055cd40;
int FUN_00113f20(void);
int FUN_00113f78(void);
int FUN_001151a0(void);
int FUN_00115438(int id);
int FUN_001158c0(int id, unsigned long clk, int (*handler)(int, int, int, Node *), Node *n);
int FUN_00115b38(int id, int a1, int a2, Node *n);
int FUN_00115b98(unsigned long clk, int (*cb)(int, int, int, int), int arg) {
    Node *n;
    Node *p;
    int id;
    int s;
    if (cb == 0) return 0x80000016;
    s = FUN_00113f20();
    p = DAT_0055cd40;
    if (p) DAT_0055cd40 = p->next;
    n = p;
    if (n == 0) {
        if (s) FUN_00113f78();
        return 0x80008005;
    }
    id = FUN_001151a0();
    if (id < 0) {
        n->next = DAT_0055cd40;
        DAT_0055cd40 = n;
        n->id = 0;
        if (s) FUN_00113f78();
        return id;
    }
    n->func = cb;
    n->arg = arg;
    n->id = id;
    FUN_001158c0(id, clk, FUN_00115b38, n);
    FUN_00115438(id);
    if (s) FUN_00113f78();
    return ((int)n << 4) | (id & 0xfe) | 1;
}
