extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c41e0();
void FUN_003c40c0(int arg0);
}

void FUN_003c40c0(int arg0) {
    FUN_003c41e0();
    igMetaObject_CreateInstance(*(int *)0x58BA00, arg0);
}
