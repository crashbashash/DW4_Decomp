extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bcdd0();
void FUN_003bcc80(int arg0);
}

void FUN_003bcc80(int arg0) {
    FUN_003bcdd0();
    igMetaObject_CreateInstance(*(int *)0x58B160, arg0);
}
