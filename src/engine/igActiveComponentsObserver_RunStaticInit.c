void *igActiveComponentsObserver_Register(void);
void igActiveComponentsObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igActiveComponentsObserver_Register);
}
