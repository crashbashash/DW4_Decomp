extern "C" {
void *beSwitchCtrlInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003432e0(void);
}
void FUN_003432e0(void)
{
    igMetaObject_RunStaticInit(beSwitchCtrlInfo_Register);
}
