typedef struct {
    int status;
    void (*func)(void *);
    void *stack;
    int stack_size;
    void *gp_reg;
    int initial_priority;
} ThreadParam;
extern int DAT_00483554;
extern int DAT_0055cf98;
extern int DAT_0055cfa0;
extern ThreadParam DAT_0055cfd0;
int FUN_0010add0(void);
int FUN_0010ade0(int id, void *info);
int FUN_0010ace0(ThreadParam *p);
int FUN_0010ad00(int id, void *arg);
int FUN_0010ad70(int id, int prio);
void _sceCd_cbLoop(void *arg);
int FUN_00116310(int prio, void *stack, int size) {
    int r;
    r = 1;
    if (DAT_00483554 == 0) {
        DAT_0055cf98 = FUN_0010add0();
        FUN_0010ade0(DAT_0055cf98, &DAT_0055cfa0);
        DAT_0055cfd0.stack_size = size;
        DAT_0055cfd0.func = _sceCd_cbLoop;
        DAT_0055cfd0.stack = stack;
        DAT_0055cfd0.gp_reg = 0;
        DAT_0055cfd0.initial_priority = prio;
        DAT_00483554 = FUN_0010ace0(&DAT_0055cfd0);
        FUN_0010ad00(DAT_00483554, 0);
    } else {
        FUN_0010ad70(DAT_00483554, prio);
        r = 0;
    }
    return r;
}
