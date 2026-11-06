void *igRadioGroupSelectedObserver_Register(void);
void igRadioGroupSelectedObserver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRadioGroupSelectedObserver_Register);
}
