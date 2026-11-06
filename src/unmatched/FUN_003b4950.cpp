extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b4a60();
void FUN_003b4950(int arg0);
}

void FUN_003b4950(int arg0) {
    FUN_003b4a60();
    igMetaObject_CreateInstance(*(int *)0x58ABA8, arg0);
}
