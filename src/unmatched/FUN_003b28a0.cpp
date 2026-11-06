extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b2a90();
void FUN_003b28a0(int arg0);
}

void FUN_003b28a0(int arg0) {
    FUN_003b2a90();
    igMetaObject_CreateInstance(*(int *)0x58AB10, arg0);
}
