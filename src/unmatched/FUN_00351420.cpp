extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003515b0();
void FUN_00351420(int arg0);
}

void FUN_00351420(int arg0) {
    FUN_003515b0();
    igMetaObject_CreateInstance(*(int *)0x588A20, arg0);
}
