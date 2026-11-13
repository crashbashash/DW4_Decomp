typedef struct Node {
    struct Node *next;
    volatile int id;
    int (*func)(int, int, int, int);
    int arg;
} Node;
extern Node *DAT_0055cd40;
int DIntr(void);
int EIntr(void);
int AllocTimerCounter(void);
int FUN_00115438(int id);
int SetTimerHandler(int id, unsigned long clk, int (*handler)(int, int, int, Node *), Node *n);
int AlarmHandler(int id, int a1, int a2, Node *n);
int SetTimerAlarm(unsigned long clk, int (*cb)(int, int, int, int), int arg) {
    Node *n;
    Node *p;
    int id;
    int s;
    if (cb == 0) return 0x80000016;
    s = DIntr();
    p = DAT_0055cd40;
    if (p) DAT_0055cd40 = p->next;
    n = p;
    if (n == 0) {
        if (s) EIntr();
        return 0x80008005;
    }
    id = AllocTimerCounter();
    if (id < 0) {
        n->next = DAT_0055cd40;
        DAT_0055cd40 = n;
        n->id = 0;
        if (s) EIntr();
        return id;
    }
    n->func = cb;
    n->arg = arg;
    n->id = id;
    SetTimerHandler(id, clk, AlarmHandler, n);
    FUN_00115438(id);
    if (s) EIntr();
    return ((int)n << 4) | (id & 0xfe) | 1;
}
