extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00365680();
void FUN_00365510(int arg0);
}

void FUN_00365510(int arg0) {
    FUN_00365680();
    igMetaObject_CreateInstance(*(int *)0x5898B8, arg0);
}
