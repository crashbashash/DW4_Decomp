extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00360d30();
void FUN_00360b70(int arg0);
}

void FUN_00360b70(int arg0) {
    FUN_00360d30();
    igMetaObject_CreateInstance(*(int *)0x5895D0, arg0);
}
