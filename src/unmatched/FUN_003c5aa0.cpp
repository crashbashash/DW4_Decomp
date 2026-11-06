extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c5bc0();
void FUN_003c5aa0(int arg0);
}

void FUN_003c5aa0(int arg0) {
    FUN_003c5bc0();
    igMetaObject_CreateInstance(*(int *)0x58BC98, arg0);
}
