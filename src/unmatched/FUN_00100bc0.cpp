extern "C" {
typedef struct N { struct N *next; int (*fn)(int, int); int arg; } N;
extern N * DAT_00555048[4];
void FUN_00100bc0(void) {
    N *e;

    while ((e = DAT_00555048[0]) != 0) {
        DAT_00555048[0] = e->next;
        e->fn(e->arg, -1);
    }
}
}
