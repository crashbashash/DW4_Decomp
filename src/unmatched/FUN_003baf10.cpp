extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bb040();
void FUN_003baf10(int arg0);
}

void FUN_003baf10(int arg0) {
    FUN_003bb040();
    igMetaObject_CreateInstance(*(int *)0x58AF98, arg0);
}
