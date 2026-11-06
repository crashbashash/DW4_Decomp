void *igFont_Register(void);
void igFont_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFont_Register);
}
