extern "C" {
typedef struct { int vt; char p[36]; char *m; } S;
int igObject_Destroy(char *);
int thunk_FUN_002ed460__002ff810(S *);
extern int DAT_00539e90[4];
void *FUN_0033e920(S *arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        arg0->vt = (int)(&DAT_00539e90[0]);
        if (((char *)arg0 + 0x28) != 0) {
            o = arg0->m;
            if (o != 0) {
                *(int *)(o + 4) = *(int *)(o + 4) - 1;
                if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        if ((short)arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
}
