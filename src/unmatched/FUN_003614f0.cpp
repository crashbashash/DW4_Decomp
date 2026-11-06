extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00361610();
void FUN_003614f0(int arg0);
}

void FUN_003614f0(int arg0) {
    FUN_00361610();
    igMetaObject_CreateInstance(*(int *)0x589640, arg0);
}
