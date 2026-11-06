extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00364930();
void FUN_003647c0(int arg0);
}

void FUN_003647c0(int arg0) {
    FUN_00364930();
    igMetaObject_CreateInstance(*(int *)0x589868, arg0);
}
