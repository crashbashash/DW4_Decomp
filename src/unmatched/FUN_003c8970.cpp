extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c8a40();

void FUN_003c8970(int arg0) {
    FUN_003c8a40();
    igMetaObject_CreateInstance(*(int *)0x58BF50, arg0);
}
}
