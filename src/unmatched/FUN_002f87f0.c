int FUN_00126308();
int igObject_AllocateRawStorageDefault();
extern unsigned char * DAT_00586dc8[4];
void FUN_002f87f0(int arg0) {
    if (*DAT_00586dc8[0] != 0) {
        igObject_AllocateRawStorageDefault(arg0, 0);
        return;
    }
    FUN_00126308();
}
