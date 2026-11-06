extern "C" {
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
extern int * DAT_004cf8a0[4];
extern int DAT_0051b3c0[4];
extern int DAT_0051b3c8[4];
extern int DAT_0051b3d8[4];
extern int DAT_0051b680[4];
typedef struct O { char p[12]; int m; } O;
void FUN_004369f0(O *arg0) {
    int i;
    int **p = DAT_004cf8a0;
    for (i = 0; i < 12; i++) {
        beMessenger_SelectGroup(arg0->m, &DAT_0051b3c0[0]);
        beMessenger_AppendString(arg0->m, &DAT_0051b3c8[0]);
        beMessenger_AppendString(arg0->m, *p);
        beMessenger_DispatchSelected(arg0->m, &DAT_0051b3d8[0]);
        beMessenger_SelectGroup(arg0->m, &DAT_0051b3c0[0]);
        beMessenger_AppendString(arg0->m, &DAT_0051b680[0]);
        beMessenger_AppendString(arg0->m, *p);
        beMessenger_DispatchSelected(arg0->m, &DAT_0051b3d8[0]);
        p++;
    }
}
}
