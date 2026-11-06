extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00362690();
void FUN_003624f0(int arg0);
}

void FUN_003624f0(int arg0) {
    FUN_00362690();
    igMetaObject_CreateInstance(*(int *)0x5896D8, arg0);
}
