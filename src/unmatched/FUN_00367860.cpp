extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00367b20();
void FUN_00367860(int arg0);
}

void FUN_00367860(int arg0) {
    FUN_00367b20();
    igMetaObject_CreateInstance(*(int *)0x589AD8, arg0);
}
