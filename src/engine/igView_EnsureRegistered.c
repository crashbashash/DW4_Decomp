void *igView_Register(void);
void igView_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igView_Register);
}
