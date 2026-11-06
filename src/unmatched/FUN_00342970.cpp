extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00342b00();

void FUN_00342970(int arg0) {
    FUN_00342b00();
    igMetaObject_CreateInstance(*(int *)0x587CE8, arg0);
}
}
