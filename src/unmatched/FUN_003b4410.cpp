extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b4520();
void FUN_003b4410(int arg0);
}

void FUN_003b4410(int arg0) {
    FUN_003b4520();
    igMetaObject_CreateInstance(*(int *)0x58AB90, arg0);
}
