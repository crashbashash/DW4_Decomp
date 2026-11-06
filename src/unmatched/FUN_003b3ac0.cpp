extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b3bd0();
void FUN_003b3ac0(int arg0);
}

void FUN_003b3ac0(int arg0) {
    FUN_003b3bd0();
    igMetaObject_CreateInstance(*(int *)0x58AB68, arg0);
}
