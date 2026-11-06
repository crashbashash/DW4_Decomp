extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c9210();

void FUN_003c90f0(int arg0) {
    FUN_003c9210();
    igMetaObject_CreateInstance(*(int *)0x58BF88, arg0);
}
}
