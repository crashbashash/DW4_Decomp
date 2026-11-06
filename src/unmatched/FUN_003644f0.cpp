extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00364660();
void FUN_003644f0(int arg0);
}

void FUN_003644f0(int arg0) {
    FUN_00364660();
    igMetaObject_CreateInstance(*(int *)0x589858, arg0);
}
