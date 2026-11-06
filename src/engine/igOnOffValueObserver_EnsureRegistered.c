void *igOnOffValueObserver_Register(void);
void igOnOffValueObserver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igOnOffValueObserver_Register);
}
