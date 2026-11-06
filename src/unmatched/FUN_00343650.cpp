extern "C" {
void *beSwitchCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00343650(void);
}
void FUN_00343650(void)
{
    igMetaObject_RunStaticInit(beSwitchCtrl_Register);
}
