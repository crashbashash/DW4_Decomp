extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003badf0();
void FUN_003bace0(int arg0);
}

void FUN_003bace0(int arg0) {
    FUN_003badf0();
    igMetaObject_CreateInstance(*(int *)0x58AF88, arg0);
}
