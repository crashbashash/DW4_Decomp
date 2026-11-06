extern "C" {
void *beMeterCtrlNode_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00356de0(void);
}
void FUN_00356de0(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlNode_Register);
}
