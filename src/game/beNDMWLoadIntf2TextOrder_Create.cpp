extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c7830();
void beNDMWLoadIntf2TextOrder_Create(int arg0);
}

void beNDMWLoadIntf2TextOrder_Create(int arg0) {
    FUN_003c7830();
    igMetaObject_CreateInstance(*(int *)0x58BE90, arg0);
}
