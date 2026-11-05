/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct O { char p0[20]; int m; } O;
void beMessenger_SelectReceivers(int, const char *, const char *, int);
void beMessenger_AppendString(int, const char *);
void beMessenger_DispatchSelected(int, const char *);
extern char DAT_0051dad0[], DAT_0051dad8[], DAT_0051dae8[], DAT_0051daf0[], DAT_0051daf8[], DAT_0051db00[], DAT_0051db08[], DAT_0051db10[], DAT_0051db20[], DAT_0051db28[], DAT_0051db30[];
void FUN_0044a8d0(O *arg0) {
    beMessenger_SelectReceivers(arg0->m, DAT_0051dad0, 0, -1);
    beMessenger_AppendString(arg0->m, DAT_0051dad8);
    beMessenger_AppendString(arg0->m, DAT_0051dae8);
    beMessenger_AppendString(arg0->m, DAT_0051daf0);
    beMessenger_DispatchSelected(arg0->m, DAT_0051daf8);
    beMessenger_SelectReceivers(arg0->m, DAT_0051dad0, 0, -1);
    beMessenger_AppendString(arg0->m, DAT_0051dad8);
    beMessenger_AppendString(arg0->m, DAT_0051db00);
    beMessenger_AppendString(arg0->m, DAT_0051daf0);
    beMessenger_DispatchSelected(arg0->m, DAT_0051daf8);
    beMessenger_SelectReceivers(arg0->m, DAT_0051dad0, 0, -1);
    beMessenger_AppendString(arg0->m, DAT_0051dad8);
    beMessenger_AppendString(arg0->m, DAT_0051db08);
    beMessenger_AppendString(arg0->m, DAT_0051daf0);
    beMessenger_DispatchSelected(arg0->m, DAT_0051daf8);
    beMessenger_SelectReceivers(arg0->m, DAT_0051dad0, 0, -1);
    beMessenger_AppendString(arg0->m, DAT_0051db10);
    beMessenger_AppendString(arg0->m, DAT_0051db00);
    beMessenger_AppendString(arg0->m, DAT_0051daf0);
    beMessenger_DispatchSelected(arg0->m, DAT_0051daf8);
    beMessenger_SelectReceivers(arg0->m, DAT_0051dad0, 0, -1);
    beMessenger_AppendString(arg0->m, DAT_0051db10);
    beMessenger_AppendString(arg0->m, DAT_0051db08);
    beMessenger_AppendString(arg0->m, DAT_0051daf0);
    beMessenger_DispatchSelected(arg0->m, DAT_0051daf8);
    beMessenger_SelectReceivers(arg0->m, DAT_0051dad0, 0, -1);
    beMessenger_AppendString(arg0->m, DAT_0051db10);
    beMessenger_AppendString(arg0->m, DAT_0051db20);
    beMessenger_AppendString(arg0->m, DAT_0051daf0);
    beMessenger_DispatchSelected(arg0->m, DAT_0051daf8);
    beMessenger_SelectReceivers(arg0->m, DAT_0051dad0, 0, -1);
    beMessenger_AppendString(arg0->m, DAT_0051db10);
    beMessenger_AppendString(arg0->m, DAT_0051db28);
    beMessenger_AppendString(arg0->m, DAT_0051daf0);
    beMessenger_DispatchSelected(arg0->m, DAT_0051daf8);
    beMessenger_SelectReceivers(arg0->m, DAT_0051dad0, 0, -1);
    beMessenger_AppendString(arg0->m, DAT_0051db10);
    beMessenger_AppendString(arg0->m, DAT_0051db30);
    beMessenger_AppendString(arg0->m, DAT_0051daf0);
    beMessenger_DispatchSelected(arg0->m, DAT_0051daf8);
}
} /* extern "C" */
