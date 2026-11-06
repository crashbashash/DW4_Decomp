extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003630b0();
void FUN_00362f90(int arg0);
}

void FUN_00362f90(int arg0) {
    FUN_003630b0();
    igMetaObject_CreateInstance(*(int *)0x589780, arg0);
}
