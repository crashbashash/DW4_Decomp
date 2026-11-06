extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00349a40();
void FUN_00349870(int arg0);
}

void FUN_00349870(int arg0) {
    FUN_00349a40();
    igMetaObject_CreateInstance(*(int *)0x588270, arg0);
}
