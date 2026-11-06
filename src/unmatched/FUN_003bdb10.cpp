extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bdf00();
void FUN_003bdb10(int arg0);
}

void FUN_003bdb10(int arg0) {
    FUN_003bdf00();
    igMetaObject_CreateInstance(*(int *)0x58B200, arg0);
}
