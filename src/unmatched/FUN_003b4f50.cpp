extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b5070();
void FUN_003b4f50(int arg0);
}

void FUN_003b4f50(int arg0) {
    FUN_003b5070();
    igMetaObject_CreateInstance(*(int *)0x58ABC8, arg0);
}
