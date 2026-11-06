extern "C" {
void *beCri_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00367b20(void);
}
void FUN_00367b20(void)
{
    igMetaObject_RunStaticInit(beCri_Register);
}
