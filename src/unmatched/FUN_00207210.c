typedef long long s128;
int CreateSema();
int p2RegisterPredicateName();
int FUN_00204240();
int FUN_00206610();
int FUN_00207f30();
void FUN_00207400(void);
extern int DAT_00490b60[4];
struct Sema { int w0; int b; int c; int d; long long e; };
extern struct Sema DAT_00491700;
extern int DAT_004e5330[4];
extern int DAT_004e5350[4];
extern short DAT_00568e12[];
extern short DAT_00568e14[];
extern short DAT_00568e16[];
extern int DAT_0056bf38[4];
extern int DAT_0056bf40[4];
extern int DAT_0056bf48[4];
extern int DAT_0056bf50[4];
extern int DAT_0056bf58[4];
extern int DAT_0056bf60[4];
extern int DAT_0056bf68[4];
extern long long DAT_0056bf70[4];
extern long long DAT_0056bf78[4];
extern int DAT_0056bf80[4];
extern int DAT_0056bf88[4];
extern int DAT_0056bf90[4];
extern long long DAT_0056bf98[4];
extern int DAT_0056bfb8[4];
extern int DAT_0056bfc0[4];
extern int DAT_0056bfc8[4];
extern int DAT_0056bfd0[4];
extern int DAT_0056bfd8[4];
extern long long DAT_0056bff0[4];
int FUN_00207420();

void FUN_00207210(void) {
    struct Sema sp;
    sp = DAT_00491700;
    if (DAT_00490b60[0] != 0) {
        sp.b = 5;
        sp.c = 0;
        DAT_0056bf80[0] = CreateSema(&sp);
        sp.b = 5;
        sp.c = 1;
        DAT_0056bf90[0] = CreateSema(&sp);
        sp.b = 1;
        sp.c = 1;
        DAT_0056bf88[0] = CreateSema(&sp);
        p2RegisterPredicateName(FUN_00207400, &DAT_004e5330[0]);
        p2RegisterPredicateName(&FUN_00207420, &DAT_004e5350[0]);
        FUN_00206610();
    }
    if (DAT_00568e16[0] != 0) {
        DAT_00568e14[0] = 0;
        DAT_00568e12[0] = 0;
    } else {
        DAT_00568e12[0] = 0;
        DAT_00568e14[0] = 1;
    }
    DAT_0056bf40[0] = 0;
    DAT_0056bf48[0] = 0;
    DAT_0056bf50[0] = 0;
    FUN_00204240(9, &DAT_0056bf50[0]);
    DAT_0056bfd8[0] = 0;
    DAT_0056bfc8[0] = 2;
    DAT_0056bfd0[0] = 1;
    DAT_0056bff0[0] = 0;
    DAT_0056bf38[0] = 1;
    DAT_0056bf58[0] = 1;
    DAT_0056bf60[0] = 0;
    DAT_0056bf68[0] = 0;
    DAT_0056bf70[0] = 0;
    DAT_0056bf78[0] = 1;
    DAT_0056bf98[0] = 0;
    DAT_0056bfb8[0] = 1;
    DAT_0056bfc0[0] = 0;
    FUN_00207f30(1);
}
