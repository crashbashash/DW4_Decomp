int FUN_00453a40(int, int, int, int, int *);
int thunk_FUN_00453a40(int, int, int, int, int *);
extern int DAT_0058d0e4[4];
extern int DAT_0058d0f4[4];
extern int DAT_0058d104[4];
extern int DAT_0058d114[4];
extern int DAT_0058d124[4];
extern int DAT_0058d154[4];
extern int DAT_0058d164[4];
typedef struct S { char pad[8]; int f8; int f12; int f16; int f20; int f24; int f28; int f32; } S;

extern int g_igViewerGuiFactory_metaObject[4];

void FUN_0045eda0(void **arg0) {
    void *temp_a0;
    *arg0 = 0;
    temp_a0 = (void *)(*arg0);
    if (temp_a0 != 0) {
        *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) + 1));
    }
}

void Gap__Viewer__igViewerGuiFactory__vfunc_13(S *arg0) {
    FUN_00453a40(arg0->f8, 0, 0, 0, &DAT_0058d154[0]);
    FUN_00453a40(arg0->f8, 0, 1, 0, &DAT_0058d154[0]);
    FUN_00453a40(arg0->f8, 1, 0, 0, &DAT_0058d164[0]);
    FUN_00453a40(arg0->f8, 1, 1, 0, &DAT_0058d164[0]);
    FUN_00453a40(arg0->f8, 0, 0, 1, &DAT_0058d154[0]);
    FUN_00453a40(arg0->f12, 0, 0, 0, &DAT_0058d0f4[0]);
    FUN_00453a40(arg0->f12, 0, 1, 0, &DAT_0058d0f4[0]);
    FUN_00453a40(arg0->f12, 1, 0, 0, &DAT_0058d114[0]);
    FUN_00453a40(arg0->f12, 1, 1, 0, &DAT_0058d124[0]);
    FUN_00453a40(arg0->f12, 0, 0, 1, &DAT_0058d104[0]);
    thunk_FUN_00453a40(arg0->f16, 0, 0, 0, &DAT_0058d0e4[0]);
    thunk_FUN_00453a40(arg0->f16, 1, 0, 0, &DAT_0058d0e4[0]);
    thunk_FUN_00453a40(arg0->f16, 0, 1, 0, &DAT_0058d124[0]);
    thunk_FUN_00453a40(arg0->f16, 1, 1, 0, &DAT_0058d124[0]);
    thunk_FUN_00453a40(arg0->f16, 0, 0, 1, &DAT_0058d0e4[0]);
    FUN_00453a40(arg0->f20, 0, 0, 0, &DAT_0058d154[0]);
    FUN_00453a40(arg0->f20, 1, 0, 0, &DAT_0058d154[0]);
    FUN_00453a40(arg0->f20, 0, 1, 0, &DAT_0058d154[0]);
    FUN_00453a40(arg0->f20, 1, 1, 0, &DAT_0058d154[0]);
    FUN_00453a40(arg0->f20, 0, 0, 1, &DAT_0058d154[0]);
    thunk_FUN_00453a40(arg0->f24, 0, 0, 0, &DAT_0058d0f4[0]);
    thunk_FUN_00453a40(arg0->f24, 1, 0, 0, &DAT_0058d0f4[0]);
    thunk_FUN_00453a40(arg0->f24, 0, 1, 0, &DAT_0058d0f4[0]);
    thunk_FUN_00453a40(arg0->f24, 1, 1, 0, &DAT_0058d0f4[0]);
    thunk_FUN_00453a40(arg0->f24, 0, 0, 1, &DAT_0058d0f4[0]);
    thunk_FUN_00453a40(arg0->f28, 0, 0, 0, &DAT_0058d0e4[0]);
    thunk_FUN_00453a40(arg0->f28, 1, 0, 0, &DAT_0058d114[0]);
    thunk_FUN_00453a40(arg0->f28, 0, 1, 0, &DAT_0058d124[0]);
    thunk_FUN_00453a40(arg0->f28, 1, 1, 0, &DAT_0058d124[0]);
    thunk_FUN_00453a40(arg0->f28, 0, 0, 1, &DAT_0058d0e4[0]);
    thunk_FUN_00453a40(arg0->f32, 0, 0, 0, &DAT_0058d0f4[0]);
    thunk_FUN_00453a40(arg0->f32, 0, 1, 0, &DAT_0058d124[0]);
    thunk_FUN_00453a40(arg0->f32, 1, 0, 0, &DAT_0058d114[0]);
    thunk_FUN_00453a40(arg0->f32, 1, 1, 0, &DAT_0058d124[0]);
    thunk_FUN_00453a40(arg0->f32, 0, 0, 1, &DAT_0058d104[0]);
}

int Gap__Viewer__igViewerGuiFactory__vfunc_22(void) {
    return g_igViewerGuiFactory_metaObject[0];
}

void FUN_0045f1e0(void *arg0, float fparg0, float fparg1) {
    *(float *)((char *)(arg0) + 0) = fparg0;
    *(float *)((char *)(arg0) + 4) = fparg1;
}

int FUN_0045f1f0(int a0)
{
    return a0;
}
