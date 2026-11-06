extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00366290();
void FUN_003660d0(int arg0);
}

void FUN_003660d0(int arg0) {
    FUN_00366290();
    igMetaObject_CreateInstance(*(int *)0x589958, arg0);
}
