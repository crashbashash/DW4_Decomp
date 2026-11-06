void *igEventReceiver_Register(void);
void igEventReceiver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventReceiver_Register);
}
