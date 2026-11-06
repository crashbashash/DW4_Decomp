extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003629b0();
void FUN_003627f0(int arg0);
}

void FUN_003627f0(int arg0) {
    FUN_003629b0();
    igMetaObject_CreateInstance(*(int *)0x5896F8, arg0);
}
