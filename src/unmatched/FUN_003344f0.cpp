extern "C" {
void *igAdx_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003344f0(void);
}
void FUN_003344f0(void)
{
    igMetaObject_RunStaticInit(igAdx_Register);
}
