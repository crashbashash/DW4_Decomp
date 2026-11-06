extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00348b00();

void FUN_00348930(int arg0) {
    FUN_00348b00();
    igMetaObject_CreateInstance(*(int *)0x5881F0, arg0);
}
}
