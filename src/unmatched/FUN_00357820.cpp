extern "C" {
void *beMeterCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00357820(void);
}
void FUN_00357820(void)
{
    igMetaObject_RunStaticInit(beMeterCtrl_Register);
}
