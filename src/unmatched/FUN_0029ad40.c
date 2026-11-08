extern int DAT_004bd254;
extern char DAT_004f4ab8[];
void FUN_0029a320(const char *, ...);
int FUN_0029af28(void *);
int FUN_0029afd0(void);
int FUN_0029ade0(void *);

typedef struct {
    int f0;
    volatile int state;
} Obj29ad40;

int FUN_0029ad40(Obj29ad40 *obj) {
    int state;

    if (DAT_004bd254 != 1) {
        return 0;
    }
    if (obj == 0) {
        FUN_0029a320(DAT_004f4ab8);
        return 0;
    }
    state = obj->state;
    if (state != DAT_004bd254) {
        return 0;
    }
    if (FUN_0029af28(obj) == state) {
        return 0;
    }
    if (FUN_0029afd0() == state) {
        return 0;
    }
    return FUN_0029ade0(obj);
}
