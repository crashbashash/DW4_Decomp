extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00348e40();

void FUN_00348c70(int arg0) {
    FUN_00348e40();
    igMetaObject_CreateInstance(*(int *)0x588200, arg0);
}
}
