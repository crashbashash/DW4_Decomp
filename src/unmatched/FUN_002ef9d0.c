int igObject_Destroy();
extern int *DAT_00586f48[4];
void FUN_002ef9d0(void) {
    int *o;

    o = DAT_00586f48[0];
    o[1] = o[1] - 1;
    if ((o[1] & 0x7FFFFF) == 0) {
        igObject_Destroy(o);
    }
    DAT_00586f48[0] = 0;
}
