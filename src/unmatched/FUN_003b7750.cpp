extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b78a0();
void FUN_003b7750(int arg0);
}

void FUN_003b7750(int arg0) {
    FUN_003b78a0();
    igMetaObject_CreateInstance(*(int *)0x58AD40, arg0);
}
