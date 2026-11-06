extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b46e0();
void FUN_003b45d0(int arg0);
}

void FUN_003b45d0(int arg0) {
    FUN_003b46e0();
    igMetaObject_CreateInstance(*(int *)0x58AB98, arg0);
}
