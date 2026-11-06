extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00369600();
void FUN_003694a0(int arg0);
}

void FUN_003694a0(int arg0) {
    FUN_00369600();
    igMetaObject_CreateInstance(*(int *)0x589C38, arg0);
}
