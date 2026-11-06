extern "C" {
void *beMeterCtrlInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00357170(void);
}
void FUN_00357170(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlInfo_Register);
}
