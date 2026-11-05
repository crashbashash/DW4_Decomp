/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
extern int DAT_005159c0[16];
extern int DAT_005159d8[16];
extern int DAT_005159e0[16];
typedef struct O { char p0[12]; int f12; char p1[8]; int f24; int f28; char p2[20]; int f52; } O;
void FUN_003ce890(O *arg0) {
    int n;
    int cur;
    int t;
    n = arg0->f52;
    if (n != 0 && (cur = arg0->f24, cur != (n - 1))) {
        if (cur != 3) {
            arg0->f24 = cur + 1;
            beMessenger_SelectGroup(arg0->f12, &DAT_005159c0[0]);
            beMessenger_AppendString(arg0->f12, &DAT_005159e0[0]);
            beMessenger_DispatchSelected(arg0->f12, &DAT_005159d8[0]);
            return;
        }
        t = arg0->f28;
        if ((t + 4) < n) {
            arg0->f28 = t + 1;
            beMessenger_SelectGroup(arg0->f12, &DAT_005159c0[0]);
            beMessenger_AppendString(arg0->f12, &DAT_005159e0[0]);
            beMessenger_DispatchSelected(arg0->f12, &DAT_005159d8[0]);
        }
    }
}
} /* extern "C" */
