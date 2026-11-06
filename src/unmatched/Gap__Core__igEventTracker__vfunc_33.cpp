/* The status temporary is read through an inline Code() into a local, the summed value is read
 * through a volatile view so its load precedes the accumulator load, and the loop counter is
 * initialised before the position. */
extern "C" {
int FUN_002e2130(void *);
int FUN_002e2300(void *, int);
int igStrCmp(char *, int);
extern int DAT_004fb410[4];
}
struct R { int a; inline int Code() { return a; } };
struct Ev { int type; int pad[2]; int val; int pad2[8]; char *str; int rest[26]; };
struct T {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual R v25(int, Ev *);
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void v31();
    virtual int v32(int);
    int pad[9];
    int f40;
};
extern "C" void Gap__Core__igEventTracker__vfunc_33(T *arg0, int arg1, int arg2, int arg3, int *arg4, int *arg5, int *arg6, int *arg7)
{
    Ev ev;
    int key = arg3;
    int var_s0;
    int var_s1;
    var_s1 = 0;
    var_s0 = 0;
    FUN_002e2130(&ev);
    if (arg2 == -1) {
        arg2 = arg0->f40 - 1;
    }
    *arg4 = 0;
    *arg5 = 0;
    *arg6 = 0;
    *arg7 = 0;
    while (var_s1 < arg1) {
        var_s0 = arg0->v32(var_s0);
        var_s1 += 1;
    }
    for (;;) {
        int c = arg0->v25(var_s0, &ev).Code();
        if (c != DAT_004fb410[0]) break;
        if (ev.str != 0 && *ev.str != 0 && igStrCmp(ev.str, key) == 0) {
            switch (ev.type) {
            case 6:
                *arg4 += 1;
                *arg6 = *arg6 + ((volatile Ev &)ev).val;
                break;
            case 8:
                *arg5 += 1;
                *arg7 = *arg7 + ((volatile Ev &)ev).val;
                break;
            }
        }
        var_s0 = arg0->v32(var_s0);
        var_s1 += 1;
        if (var_s1 >= arg2 || var_s0 == -1) break;
    }
    FUN_002e2300(&ev, -1);
}
