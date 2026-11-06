extern "C" {
void *beNumberCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034e520(void);
}
void FUN_0034e520(void)
{
    igMetaObject_RunStaticInit(beNumberCtrl_Register);
}
