extern "C" {
void *beDemoManagerWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00363930(void);
}
void FUN_00363930(void)
{
    igMetaObject_RunStaticInit(beDemoManagerWork_Register);
}
