extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b3a10();
void FUN_003b3900(int arg0);
}

void FUN_003b3900(int arg0) {
    FUN_003b3a10();
    igMetaObject_CreateInstance(*(int *)0x58AB60, arg0);
}
