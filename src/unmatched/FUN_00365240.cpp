extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003653b0();
void FUN_00365240(int arg0);
}

void FUN_00365240(int arg0) {
    FUN_003653b0();
    igMetaObject_CreateInstance(*(int *)0x5898A8, arg0);
}
