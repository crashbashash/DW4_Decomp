/* 0x0032dcf0 — FUN_0032dcf0. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad28[28]; int f1C; } S0;
int Memory_FreeBuffer();
int Gap__Core__igObject__vfunc_02();
int Memory_FreeBufferAlias_002ed5c0();
extern int DAT_00587360[4];
void FUN_0032dcf0(S0 *arg0) {
    void *temp_s0;

    temp_s0 = (void *)(arg0->f1C);
    if (temp_s0 != 0) {
        Memory_FreeBuffer(*(int *)((char *)(temp_s0) + 12));
        Memory_FreeBuffer(*(int *)((char *)(temp_s0) + 8));
        Memory_FreeBufferAlias_002ed5c0(temp_s0);
    }
    arg0->f1C = 0;
    DAT_00587360[0] = 0;
    Gap__Core__igObject__vfunc_02(arg0);
}
