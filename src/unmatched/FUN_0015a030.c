int FUN_0015a100();
int FUN_002eb010();
int FUN_00300f50();
int Gap__Core__igObject__vfunc_15();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
char *StringPool_Intern();
extern int DAT_00586f20[4];
struct A { char pad[56]; int f56; char pad2[28]; int *f88; };
void FUN_0015a030(struct A *arg0) {
    int *a1;
    int v1;
    int var_v0;
    int *old;
    int *s0;
    int tmp;

    Gap__Core__igObject__vfunc_15(arg0);
    tmp = arg0->f56;
    if (tmp != 0) {
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        s0 = (int *)StringPool_Intern(DAT_00586f20[0], tmp);
        old = arg0->f88;
        if (old != 0) {
            a1 = old - 2;
            v1 = old[-1] - 1;
            old[-1] = v1;
            if (v1 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        arg0->f88 = s0;
        FUN_00300f50(arg0, arg0->f56);
        arg0->f56 = 0;
    }
    FUN_0015a100(arg0);
}
