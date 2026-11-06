extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b8a00();
void FUN_003b8860(int arg0);
}

void FUN_003b8860(int arg0) {
    FUN_003b8a00();
    igMetaObject_CreateInstance(*(int *)0x58AE08, arg0);
}
