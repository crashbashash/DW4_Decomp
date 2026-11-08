typedef struct Node {
    struct Node *next;
    volatile int id;
    int (*func)(int, int, int, int);
    int arg;
} Node;
extern Node *DAT_0055cd40;
int FUN_00113f20(void);
int FUN_00113f78(void);
int FUN_00115288(int id);
int ReleaseTimerAlarm(int id) {
    Node *n;
    int s;
    n = (Node *)(((unsigned int)id >> 8) << 4);
    s = FUN_00113f20();
    if (id < 0 || ((id ^ n->id) & 0xff) != 0) {
        if (s) FUN_00113f78();
        return 0x80008002;
    }
    FUN_00115288(n->id);
    n->next = DAT_0055cd40;
    DAT_0055cd40 = n;
    n->id = 0;
    if (s) FUN_00113f78();
    return 0;
}
