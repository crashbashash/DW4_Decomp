typedef struct Node {
    struct Node *next;
    volatile int id;
    int (*func)(int, int, int, int);
    int arg;
} Node;
extern Node *DAT_0055cd40;
int iFreeTimerCounter(int id);
int iReleaseTimerAlarm(int id) {
    Node *n;
    int r;
    n = (Node *)(((unsigned int)id >> 8) << 4);
    if (id < 0 || ((id ^ n->id) & 0xff) != 0) return 0x80008002;
    r = iFreeTimerCounter(n->id);
    if (r == 0) {
        n->next = DAT_0055cd40;
        DAT_0055cd40 = n;
        n->id = 0;
    }
    return r;
}
