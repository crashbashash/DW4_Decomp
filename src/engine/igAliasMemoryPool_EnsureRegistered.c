void *igAliasMemoryPool_Register(void);
void igAliasMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAliasMemoryPool_Register);
}
