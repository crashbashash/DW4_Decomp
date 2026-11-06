extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00365120();
void FUN_00365000(int arg0);
}

void FUN_00365000(int arg0) {
    FUN_00365120();
    igMetaObject_CreateInstance(*(int *)0x589898, arg0);
}
