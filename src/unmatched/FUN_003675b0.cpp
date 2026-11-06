extern "C" {
void *beCriSndf_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003675b0(void);
}
void FUN_003675b0(void)
{
    igMetaObject_RunStaticInit(beCriSndf_Register);
}
