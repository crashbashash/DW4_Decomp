int memset();
struct T *FUN_001ee1c0();
int FUN_00330730();
extern int DAT_0048dce0[4];
extern int DAT_00562c70[4];
extern int DAT_00568e50[4];
extern int * DAT_00568e60[4];
extern int DAT_00568e70[4];
extern int DAT_00568e90[4];
extern int DAT_00568e94[4];
extern int DAT_00568e98[4];
extern int DAT_00568e9c[4];
extern int DAT_00568ea0[4];
extern struct T * DAT_00568eb8[4];
extern struct T * DAT_00568ec0[4];
extern int * DAT_00568f04[4];
extern int DAT_00569228[4];
extern int DAT_00569230[4];
extern int DAT_00569250[4];
extern int DAT_00569258[4];
extern int DAT_00569330[4];
struct T { int w0; int w4; int w8; int f12; int w16; int f20; char pad[12]; int f36; int f40; };
struct T *FUN_001ee270(int arg0) {
    struct T *temp_v0;

    if (DAT_00568e50[0] != 0) {
        return (struct T *)-1;
    }
    if ((((unsigned int)DAT_00562c70[DAT_00569330[0]]) >> 9) & 1) {
        DAT_00569228[0] = 0x30;
        if (1 < DAT_0048dce0[0]) {
            DAT_00569228[0] = DAT_00569228[0] | 8;
        }
    } else {
        DAT_00569228[0] = 0x20;
    }
    DAT_00568e50[0] = arg0;
    DAT_00569230[0] = 2;
    temp_v0 = FUN_001ee1c0();
    DAT_00568eb8[0] = temp_v0;
    DAT_00568ec0[0] = temp_v0;
    temp_v0->f20 = 0;
    temp_v0->f36 = DAT_00569250[0];
    temp_v0->f40 = DAT_00569258[0];
    memset(&DAT_00568e70[0], 0, 0x48);
    DAT_00568e90[0] = FUN_00330730(0x8000, 0xB);
    DAT_00568ea0[0] = DAT_00568e90[0];
    DAT_00568e94[0] = DAT_00568e90[0] + 0x7FF0;
    DAT_00568e60[0] = DAT_00568f04[0];
    DAT_00568f04[0] = &DAT_00568e70[0];
    DAT_00568e98[0] = DAT_00568e94[0] - 0x1400;
    DAT_00568e9c[0] = DAT_00568e98[0];
    temp_v0->f12 = DAT_00568e90[0];
    return temp_v0;
}
