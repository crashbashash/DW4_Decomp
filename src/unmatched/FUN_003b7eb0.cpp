extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b8060();
void FUN_003b7eb0(int arg0);
}

void FUN_003b7eb0(int arg0) {
    FUN_003b8060();
    igMetaObject_CreateInstance(*(int *)0x58ADA0, arg0);
}
