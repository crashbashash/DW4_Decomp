/* 0x003ebce0 — TextOrder_PublishLine. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct S0 { char pad16[16]; int f10; } S0;
int beMessenger_SelectReceivers(int, int *, int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_AppendString(int, int *);
extern int DAT_005179b0[4];
extern int DAT_00517a08[4];
extern int DAT_00517a10[4];
void TextOrder_PublishLine(S0 *arg0, int *arg1, int *arg2) {
    beMessenger_SelectReceivers(arg0->f10, &DAT_005179b0[0], 0, -1);
    beMessenger_AppendString(arg0->f10, arg1);
    beMessenger_AppendString(arg0->f10, arg2);
    beMessenger_AppendString(arg0->f10, &DAT_00517a10[0]);
    beMessenger_DispatchSelected(arg0->f10, &DAT_00517a08[0]);
}
} /* extern "C" */
