extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bf700();
void FUN_003bf560(int arg0);
}

void FUN_003bf560(int arg0) {
    FUN_003bf700();
    igMetaObject_CreateInstance(*(int *)0x58B378, arg0);
}
