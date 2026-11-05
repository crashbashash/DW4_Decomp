typedef struct RT { int w0; int references; } RT;
int FUN_00235370();
void *FUN_002b90e0();
int FUN_002eb010();
int Memory_GetAllocatorBySelector();
int StringChunk_ReleaseHeader();
int StringList_AppendRetained();
int StringPool_Construct();
void *StringPool_Intern();
int igObject_Destroy(RT *);
extern int DAT_00586f20[4];
extern int DAT_00587028[4];
extern int DAT_00587060[4];
extern unsigned char GPR_00554c14;

void FUN_00234d70(int arg0, int arg1, int arg2) {
RT * volatile sp6C;
    void *sp68;
    int *temp_a1;
    int temp_s4;
    int temp_v0;
    int var_s0;
    int var_v0;
    int var_v0_3;
    void *var_v0_2;
    RT *g;

    if (GPR_00554c14 != 0) {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587028[0]);
    } else {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587060[0]);
    }
    sp6C = (void *)(FUN_002b90e0(var_v0));
    for (var_s0 = 0; var_s0 < arg1; var_s0++) {
        temp_s4 = *(int *)(arg2 + (var_s0 * 4));
        if (temp_s4 == 0) {
            var_v0_2 = (void *)(0);
        } else {
            if (DAT_00586f20[0] == 0) {
                var_v0_3 = FUN_002eb010(0x10);
                if (var_v0_3 != 0) {
                    var_v0_3 = StringPool_Construct(var_v0_3);
                }
                DAT_00586f20[0] = var_v0_3;
            }
            var_v0_2 = (void *)(StringPool_Intern(DAT_00586f20[0], temp_s4));
        }
        sp68 = (void *)(var_v0_2);
        StringList_AppendRetained(sp6C, &sp68);
        if (sp68 != 0) {
            temp_a1 = (int *)((char *)sp68 - 8);
            temp_v0 = *(int *)((char *)(sp68) - 4) - 1;
            *(int *)((char *)(sp68) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    FUN_00235370(arg0, sp6C);
    g = sp6C;
    if (g != 0) {
        --g->references;
        if (((unsigned long long)(long long)g->references & 0x7fffffULL) == 0) {
            igObject_Destroy(g);
        }
    }
}
