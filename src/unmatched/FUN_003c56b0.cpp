extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c5780();
void FUN_003c56b0(int arg0);
}

void FUN_003c56b0(int arg0) {
    FUN_003c5780();
    igMetaObject_CreateInstance(*(int *)0x58BC18, arg0);
}
