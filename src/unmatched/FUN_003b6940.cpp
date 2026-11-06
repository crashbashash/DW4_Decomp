extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b6a60();
void FUN_003b6940(int arg0);
}

void FUN_003b6940(int arg0) {
    FUN_003b6a60();
    igMetaObject_CreateInstance(*(int *)0x58ACB8, arg0);
}
