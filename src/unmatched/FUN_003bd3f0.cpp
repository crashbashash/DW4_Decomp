extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bd540();
void FUN_003bd3f0(int arg0);
}

void FUN_003bd3f0(int arg0) {
    FUN_003bd540();
    igMetaObject_CreateInstance(*(int *)0x58B1D8, arg0);
}
