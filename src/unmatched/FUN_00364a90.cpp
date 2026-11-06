extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00364bf0();
void FUN_00364a90(int arg0);
}

void FUN_00364a90(int arg0) {
    FUN_00364bf0();
    igMetaObject_CreateInstance(*(int *)0x589878, arg0);
}
