extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00363480();
void FUN_00363210(int arg0);
}

void FUN_00363210(int arg0) {
    FUN_00363480();
    igMetaObject_CreateInstance(*(int *)0x589790, arg0);
}
