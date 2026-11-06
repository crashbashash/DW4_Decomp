extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c1070();
void FUN_003c0f30(int arg0);
}

void FUN_003c0f30(int arg0) {
    FUN_003c1070();
    igMetaObject_CreateInstance(*(int *)0x58B4A0, arg0);
}
