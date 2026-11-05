extern int FUN_002ccca0();
extern int FUN_00300c60(int, int);
extern int FUN_002ff800(int, int);
extern int FUN_002d3830(int, int);
extern unsigned char *DAT_00586dc8[4];
int FUN_002ccb50(int arg0, int arg1) {
    int t;
    if (*DAT_00586dc8[0]) {
        FUN_002ccca0();
        FUN_00300c60(arg0, arg1);
        return;
    }
    t = FUN_002ff800(0x34, 0);
    if (t) t = FUN_002d3830(t, arg0);
    return t;
}
