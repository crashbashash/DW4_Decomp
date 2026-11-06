extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00351910();
void FUN_00351780(int arg0);
}

void FUN_00351780(int arg0) {
    FUN_00351910();
    igMetaObject_CreateInstance(*(int *)0x588A58, arg0);
}
