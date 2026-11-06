extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c1a00();
void FUN_003c1910(int arg0);
}

void FUN_003c1910(int arg0) {
    FUN_003c1a00();
    igMetaObject_CreateInstance(*(int *)0x58B510, arg0);
}
