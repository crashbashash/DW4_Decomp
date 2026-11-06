extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b98f0();
void FUN_003b97d0(int arg0);
}

void FUN_003b97d0(int arg0) {
    FUN_003b98f0();
    igMetaObject_CreateInstance(*(int *)0x58AEB0, arg0);
}
