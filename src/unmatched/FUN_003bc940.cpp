extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bca60();
void FUN_003bc940(int arg0);
}

void FUN_003bc940(int arg0) {
    FUN_003bca60();
    igMetaObject_CreateInstance(*(int *)0x58B0D0, arg0);
}
