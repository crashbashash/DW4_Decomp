/* 0x002fecb0 - igNamedObject_SetName. old name read after the intern call; typed struct member avoids the CSE of the field address. Verified byte-identical by tools/verify.py. */
int FUN_002eb010();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
void *StringPool_Intern();
extern int DAT_00586f20[4];
struct N { char pad[8]; char *f8; };
void igNamedObject_SetName(struct N *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    char *temp_a0;
    void *temp_s0;
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0 = (void *)(StringPool_Intern(DAT_00586f20[0], arg1));
    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        temp_a1 = (int *)(temp_a0 - 8);
        temp_v1 = *(int *)((char *)temp_a0 - 4) - 1;
        *(int *)((char *)temp_a0 - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->f8 = (char *)temp_s0;
}
