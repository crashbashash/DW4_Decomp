extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00350fb0();
void FUN_00350020(int arg0);
}

void FUN_00350020(int arg0) {
    FUN_00350fb0();
    igMetaObject_CreateInstance(*(int *)0x588888, arg0);
}
