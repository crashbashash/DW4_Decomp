extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003688d0();
void FUN_00368710(int arg0);
}

void FUN_00368710(int arg0) {
    FUN_003688d0();
    igMetaObject_CreateInstance(*(int *)0x589B80, arg0);
}
