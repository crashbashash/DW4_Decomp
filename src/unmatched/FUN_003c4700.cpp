extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c4850();
void FUN_003c4700(int arg0);
}

void FUN_003c4700(int arg0) {
    FUN_003c4850();
    igMetaObject_CreateInstance(*(int *)0x58BAC8, arg0);
}
