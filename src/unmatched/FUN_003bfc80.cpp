extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c0280();
void FUN_003bfc80(int arg0);
}

void FUN_003bfc80(int arg0) {
    FUN_003c0280();
    igMetaObject_CreateInstance(*(int *)0x58B3C8, arg0);
}
