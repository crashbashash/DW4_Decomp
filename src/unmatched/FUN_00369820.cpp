extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00369a20();
void FUN_00369820(int arg0);
}

void FUN_00369820(int arg0) {
    FUN_00369a20();
    igMetaObject_CreateInstance(*(int *)0x589C90, arg0);
}
