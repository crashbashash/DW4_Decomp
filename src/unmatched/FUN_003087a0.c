void *FUN_00308a90(void *);
void *igProperty_FindByName(int, int, int);
int igStrCmp(int, int *);
extern int DAT_004fb390[4];
extern int DAT_00586670[4];

struct R {
    int pad;
    int rc;
};

void FUN_003087a0(struct R **arg0, void *arg1, int arg2) {
    struct R *t;

    if (igStrCmp(arg2, &DAT_004fb390[0]) == 0) {
        *arg0 = (struct R *)FUN_00308a90(arg1);
        t = *arg0;
        if (t != 0) {
            t->rc = t->rc + 1;
        }
        return;
    }
    *arg0 = (struct R *)igProperty_FindByName(*(int *)((char *)arg1 + 16), DAT_00586670[0], arg2);
    t = *arg0;
    if (t != 0) {
        t->rc = t->rc + 1;
    }
}
