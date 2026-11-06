extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c5380();
void FUN_003c51c0(int arg0);
}

void FUN_003c51c0(int arg0) {
    FUN_003c5380();
    igMetaObject_CreateInstance(*(int *)0x58BB80, arg0);
}
