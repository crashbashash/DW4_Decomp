extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b5800();
void FUN_003b56f0(int arg0);
}

void FUN_003b56f0(int arg0) {
    FUN_003b5800();
    igMetaObject_CreateInstance(*(int *)0x58ABF0, arg0);
}
