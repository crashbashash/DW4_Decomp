extern "C" {
void *beMeterCtrlInfoList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00356ff0(void);
}
void FUN_00356ff0(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlInfoList_Register);
}
