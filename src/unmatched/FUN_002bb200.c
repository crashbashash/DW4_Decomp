void *igRegistry_Register(void);
void FUN_002bb200(void)
{
    igMetaObject_RunStaticInit(igRegistry_Register);
}
