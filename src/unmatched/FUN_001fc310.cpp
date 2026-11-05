extern "C" {
extern int DAT_00491478[4];
extern int DAT_0056b058[4];
void FUN_001fc310(int arg0);
}
void FUN_001fc310(int arg0) {
    int v;

    v = arg0 - 1;
    v = v > 0 ? v : 0;
    DAT_0056b058[0] = v;
    DAT_00491478[0] |= 0x191;
}
