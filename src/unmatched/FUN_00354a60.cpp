extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00354b80();
void FUN_00354a60(int arg0);
}

void FUN_00354a60(int arg0) {
    FUN_00354b80();
    igMetaObject_CreateInstance(*(int *)0x588D20, arg0);
}
