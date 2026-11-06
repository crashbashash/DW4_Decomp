extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b32c0();
void FUN_003b31b0(int arg0);
}

void FUN_003b31b0(int arg0) {
    FUN_003b32c0();
    igMetaObject_CreateInstance(*(int *)0x58AB40, arg0);
}
