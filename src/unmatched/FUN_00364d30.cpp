extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00364ea0();
void FUN_00364d30(int arg0);
}

void FUN_00364d30(int arg0) {
    FUN_00364ea0();
    igMetaObject_CreateInstance(*(int *)0x589888, arg0);
}
