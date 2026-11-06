extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b8c70();
void FUN_003b8b60(int arg0);
}

void FUN_003b8b60(int arg0) {
    FUN_003b8c70();
    igMetaObject_CreateInstance(*(int *)0x58AE18, arg0);
}
