extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c1860();
void FUN_003c1720(int arg0);
}

void FUN_003c1720(int arg0) {
    FUN_003c1860();
    igMetaObject_CreateInstance(*(int *)0x58B508, arg0);
}
