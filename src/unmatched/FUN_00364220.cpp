extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00364390();
void FUN_00364220(int arg0);
}

void FUN_00364220(int arg0) {
    FUN_00364390();
    igMetaObject_CreateInstance(*(int *)0x589848, arg0);
}
