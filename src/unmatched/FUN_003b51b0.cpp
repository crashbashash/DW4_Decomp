extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b52c0();
void FUN_003b51b0(int arg0);
}

void FUN_003b51b0(int arg0) {
    FUN_003b52c0();
    igMetaObject_CreateInstance(*(int *)0x58ABD8, arg0);
}
