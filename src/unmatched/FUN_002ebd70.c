int igObject_Destroy();
extern int DAT_00586f28[4];
extern int *DAT_00586f40[4];
void FUN_002ebd70(void) {
    int *o;

    DAT_00586f28[0] = 0;
    o = DAT_00586f40[0];
    if (o != 0) {
        o[1] = o[1] - 1;
        if ((o[1] & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00586f40[0] = 0;
}
