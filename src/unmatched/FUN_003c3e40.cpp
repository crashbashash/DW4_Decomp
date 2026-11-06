extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c3f10();
void FUN_003c3e40(int arg0);
}

void FUN_003c3e40(int arg0) {
    FUN_003c3f10();
    igMetaObject_CreateInstance(*(int *)0x58B978, arg0);
}
