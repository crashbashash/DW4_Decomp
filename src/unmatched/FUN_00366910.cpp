extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00366b20();
void FUN_00366910(int arg0);
}

void FUN_00366910(int arg0) {
    FUN_00366b20();
    igMetaObject_CreateInstance(*(int *)0x5899C8, arg0);
}
