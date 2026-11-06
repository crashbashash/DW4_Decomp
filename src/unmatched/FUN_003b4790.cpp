extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b48a0();
void FUN_003b4790(int arg0);
}

void FUN_003b4790(int arg0) {
    FUN_003b48a0();
    igMetaObject_CreateInstance(*(int *)0x58ABA0, arg0);
}
