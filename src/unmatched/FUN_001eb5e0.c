struct E { unsigned short a : 1; unsigned short c : 15; unsigned short b : 15; unsigned short d : 1; };
extern struct E DAT_00568db0[];
void FUN_001eb5e0(int arg0, int arg1, int arg2, int arg3) {
    DAT_00568db0[arg0].a = arg1;
    DAT_00568db0[arg0].c = arg3;
    DAT_00568db0[arg0].b = arg2;
}
