extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c7b60();

void FUN_003c7a40(int arg0) {
    FUN_003c7b60();
    igMetaObject_CreateInstance(*(int *)0x58BEB0, arg0);
}
}
