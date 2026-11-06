extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003675b0();
void FUN_00367490(int arg0);
}

void FUN_00367490(int arg0) {
    FUN_003675b0();
    igMetaObject_CreateInstance(*(int *)0x589AB0, arg0);
}
