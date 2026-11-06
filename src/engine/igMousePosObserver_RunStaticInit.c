void *igMousePosObserver_Register(void);
void igMousePosObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igMousePosObserver_Register);
}
