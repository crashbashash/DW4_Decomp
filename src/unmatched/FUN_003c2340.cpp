extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c2490();
void FUN_003c2340(int arg0);
}

void FUN_003c2340(int arg0) {
    FUN_003c2490();
    igMetaObject_CreateInstance(*(int *)0x58B570, arg0);
}
