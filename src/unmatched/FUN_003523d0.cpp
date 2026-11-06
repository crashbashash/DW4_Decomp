extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003525e0();
void FUN_003523d0(int arg0);
}

void FUN_003523d0(int arg0) {
    FUN_003525e0();
    igMetaObject_CreateInstance(*(int *)0x588B00, arg0);
}
