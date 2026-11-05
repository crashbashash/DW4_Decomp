/* 0x00425fb0 - FUN_00425fb0. stack copy of a 29-word pointer table (struct assignment: lq loop plus float tail), NULL-terminated walk; alternate compiler -O3,p */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct Tb { int p[29]; } Tb;
extern Tb DAT_004cf820;
extern int DAT_0051ac08[4];
extern int DAT_0051ac10[4];
extern int DAT_0051ac30[4];
extern int DAT_0051acc8[4];
extern int DAT_0051ace0[4];
extern int DAT_0051af30[4];
extern int DAT_0051af40[4];
extern int DAT_0051af48[4];
extern int DAT_0051af58[4];
int FUN_00425430(void);
int beMessenger_AppendString(int, void *);
int beMessenger_DispatchSelected(int, void *);
int beMessenger_SelectGroup(int, void *);
int beNDMWWindow_PresentModelAtOrigin(int *, void *, int, void *, void *);
typedef struct W { int p0, p1, p2, f12, p4, f20; } W;
void FUN_00425fb0(W *arg0) {
    Tb sp30;
    int *s1;
    FUN_00425430();
    beNDMWWindow_PresentModelAtOrigin((int *)arg0, DAT_0051af48, arg0->f20, DAT_0051ac08, DAT_0051ac10);
    sp30 = DAT_004cf820;
    s1 = sp30.p;
    if (sp30.p[0] != 0) {
        do {
            beMessenger_SelectGroup(arg0->f12, DAT_0051af30);
            beMessenger_AppendString(arg0->f12, DAT_0051ac30);
            beMessenger_AppendString(arg0->f12, (void *)*s1);
            beMessenger_AppendString(arg0->f12, DAT_0051af58);
            beMessenger_DispatchSelected(arg0->f12, DAT_0051af40);
            s1 += 1;
        } while (*s1 != 0);
    }
    beMessenger_SelectGroup(arg0->f12, DAT_0051af30);
    beMessenger_AppendString(arg0->f12, DAT_0051acc8);
    beMessenger_AppendString(arg0->f12, DAT_0051ace0);
    beMessenger_AppendString(arg0->f12, DAT_0051af58);
    beMessenger_DispatchSelected(arg0->f12, DAT_0051af40);
}
} /* extern "C" */
