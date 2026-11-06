extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b4ea0();
void FUN_003b4d90(int arg0);
}

void FUN_003b4d90(int arg0) {
    FUN_003b4ea0();
    igMetaObject_CreateInstance(*(int *)0x58ABC0, arg0);
}
