extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bf3f0();
void FUN_003bf1b0(int arg0);
}

void FUN_003bf1b0(int arg0) {
    FUN_003bf3f0();
    igMetaObject_CreateInstance(*(int *)0x58B368, arg0);
}
