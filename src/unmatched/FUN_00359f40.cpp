extern "C" {
void *beMatCtrlSearchList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00359f40(void);
}
void FUN_00359f40(void)
{
    igMetaObject_RunStaticInit(beMatCtrlSearchList_Register);
}
