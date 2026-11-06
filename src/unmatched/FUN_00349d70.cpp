extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00349e90();
void FUN_00349d70(int arg0);
}

void FUN_00349d70(int arg0) {
    FUN_00349e90();
    igMetaObject_CreateInstance(*(int *)0x588280, arg0);
}
