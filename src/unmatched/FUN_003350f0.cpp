extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00335260();

void FUN_003350f0(int arg0) {
    FUN_00335260();
    igMetaObject_CreateInstance(*(int *)0x5876E0, arg0);
}
}
