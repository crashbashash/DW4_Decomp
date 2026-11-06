extern "C" {
void *beSvConnectCheck_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00348530(void);
}
void FUN_00348530(void)
{
    igMetaObject_RunStaticInit(beSvConnectCheck_Register);
}
