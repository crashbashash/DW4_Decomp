void *igWindowSizeObserver_Register(void);
void igWindowSizeObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igWindowSizeObserver_Register);
}
