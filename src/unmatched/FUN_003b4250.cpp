extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b4360();
void FUN_003b4250(int arg0);
}

void FUN_003b4250(int arg0) {
    FUN_003b4360();
    igMetaObject_CreateInstance(*(int *)0x58AB88, arg0);
}
