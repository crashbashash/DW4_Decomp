extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c5dc0();
void FUN_003c5cf0(int arg0);
}

void FUN_003c5cf0(int arg0) {
    FUN_003c5dc0();
    igMetaObject_CreateInstance(*(int *)0x58BCA8, arg0);
}
