void *igEventDispatcher_Register(void);
void igEventDispatcher_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventDispatcher_Register);
}
