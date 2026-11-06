extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c44e0();
void FUN_003c43c0(int arg0);
}

void FUN_003c43c0(int arg0) {
    FUN_003c44e0();
    igMetaObject_CreateInstance(*(int *)0x58BA30, arg0);
}
