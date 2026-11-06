extern "C" {
void *beTimer_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00341500(void);
}
void FUN_00341500(void)
{
    igMetaObject_RunStaticInit(beTimer_Register);
}
