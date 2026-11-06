extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b6cf0();
void FUN_003b6bc0(int arg0);
}

void FUN_003b6bc0(int arg0) {
    FUN_003b6cf0();
    igMetaObject_CreateInstance(*(int *)0x58ACC8, arg0);
}
