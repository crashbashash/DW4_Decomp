extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b82e0();
void FUN_003b81d0(int arg0);
}

void FUN_003b81d0(int arg0) {
    FUN_003b82e0();
    igMetaObject_CreateInstance(*(int *)0x58ADB8, arg0);
}
