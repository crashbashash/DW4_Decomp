extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00368bc0();
void FUN_003689f0(int arg0);
}

void FUN_003689f0(int arg0) {
    FUN_00368bc0();
    igMetaObject_CreateInstance(*(int *)0x589B90, arg0);
}
