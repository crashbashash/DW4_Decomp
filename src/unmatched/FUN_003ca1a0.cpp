extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003ca2d0();

void FUN_003ca1a0(int arg0) {
    FUN_003ca2d0();
    igMetaObject_CreateInstance(*(int *)0x58C100, arg0);
}
}
