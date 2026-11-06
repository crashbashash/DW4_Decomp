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
}
