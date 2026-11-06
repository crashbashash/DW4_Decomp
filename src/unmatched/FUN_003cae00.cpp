extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003cb020();

void FUN_003cae00(int arg0) {
    FUN_003cb020();
    igMetaObject_CreateInstance(*(int *)0x58C158, arg0);
}
}
