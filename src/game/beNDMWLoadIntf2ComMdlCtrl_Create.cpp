extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c7090();
void beNDMWLoadIntf2ComMdlCtrl_Create(int arg0);
}

void beNDMWLoadIntf2ComMdlCtrl_Create(int arg0) {
    FUN_003c7090();
    igMetaObject_CreateInstance(*(int *)0x58BE38, arg0);
}
