extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c1270();
void FUN_003c1120(int arg0);
}

void FUN_003c1120(int arg0) {
    FUN_003c1270();
    igMetaObject_CreateInstance(*(int *)0x58B4A8, arg0);
}
