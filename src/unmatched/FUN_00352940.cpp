extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00352a10();
void FUN_00352940(int arg0);
}

void FUN_00352940(int arg0) {
    FUN_00352a10();
    igMetaObject_CreateInstance(*(int *)0x588B48, arg0);
}
