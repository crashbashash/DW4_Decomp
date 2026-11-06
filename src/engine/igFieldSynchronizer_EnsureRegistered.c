void *igFieldSynchronizer_Register(void);
void igFieldSynchronizer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldSynchronizer_Register);
}
