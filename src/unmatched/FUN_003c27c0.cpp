extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c28e0();
void FUN_003c27c0(int arg0);
}

void FUN_003c27c0(int arg0) {
    FUN_003c28e0();
    igMetaObject_CreateInstance(*(int *)0x58B5D8, arg0);
}
