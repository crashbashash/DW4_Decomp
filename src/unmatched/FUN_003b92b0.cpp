extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b93e0();
void FUN_003b92b0(int arg0);
}

void FUN_003b92b0(int arg0) {
    FUN_003b93e0();
    igMetaObject_CreateInstance(*(int *)0x58AE68, arg0);
}
