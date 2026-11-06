extern "C" {
void *beGroupKeep_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035f050(void);
}
void FUN_0035f050(void)
{
    igMetaObject_RunStaticInit(beGroupKeep_Register);
}
