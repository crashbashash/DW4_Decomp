extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b7630();
void FUN_003b7520(int arg0);
}

void FUN_003b7520(int arg0) {
    FUN_003b7630();
    igMetaObject_CreateInstance(*(int *)0x58AD28, arg0);
}
