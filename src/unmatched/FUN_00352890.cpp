extern "C" {
void *beModelCtrlMoveObjectList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00352890(void);
}
void FUN_00352890(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMoveObjectList_Register);
}
