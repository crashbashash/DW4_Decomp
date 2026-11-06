extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c0e80();
void FUN_003c0d40(int arg0);
}

void FUN_003c0d40(int arg0) {
    FUN_003c0e80();
    igMetaObject_CreateInstance(*(int *)0x58B498, arg0);
}
