extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b4c30();
void FUN_003b4b10(int arg0);
}

void FUN_003b4b10(int arg0) {
    FUN_003b4c30();
    igMetaObject_CreateInstance(*(int *)0x58ABB0, arg0);
}
