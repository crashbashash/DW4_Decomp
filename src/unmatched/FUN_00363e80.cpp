extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00363fa0();
void FUN_00363e80(int arg0);
}

void FUN_00363e80(int arg0) {
    FUN_00363fa0();
    igMetaObject_CreateInstance(*(int *)0x589838, arg0);
}
