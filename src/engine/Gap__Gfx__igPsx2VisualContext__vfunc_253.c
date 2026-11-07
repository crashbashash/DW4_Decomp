struct E { unsigned char b0; unsigned char b1; char p[2]; int f4; int f8; float f12; int f16; int f20; };
struct S { char pad[322]; unsigned char b322; char pad2[1025]; unsigned char b1348; unsigned char b1349; char pad3[2]; int f1352; int f1356; float f1360; int f1364; int f1368; };
extern int DAT_004fb418[4];
extern int DAT_004fb410[4];
void Gap__Gfx__igPsx2VisualContext__vfunc_253(int *arg0, struct S *arg1, struct E *arg2) {
    if (arg1->b322 == 1) {
        *arg0 = DAT_004fb418[0];
    } else if (arg2 == 0) {
        *arg0 = DAT_004fb418[0];
    } else {
        arg1->b1348 = arg2->b0;
        arg1->b1349 = arg2->b1;
        arg1->f1352 = arg2->f4;
        arg1->f1356 = arg2->f8;
        arg1->f1360 = arg2->f12;
        arg1->f1364 = arg2->f16;
        arg1->f1368 = arg2->f20;
        *arg0 = DAT_004fb410[0];
    }
}
