extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c5fb0();
void FUN_003c5ee0(int arg0);
}

void FUN_003c5ee0(int arg0) {
    FUN_003c5fb0();
    igMetaObject_CreateInstance(*(int *)0x58BCC0, arg0);
}
