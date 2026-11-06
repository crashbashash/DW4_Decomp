extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b3480();
void FUN_003b3370(int arg0);
}

void FUN_003b3370(int arg0) {
    FUN_003b3480();
    igMetaObject_CreateInstance(*(int *)0x58AB48, arg0);
}
