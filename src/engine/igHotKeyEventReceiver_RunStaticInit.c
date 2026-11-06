void *igHotKeyEventReceiver_Register(void);
void igHotKeyEventReceiver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igHotKeyEventReceiver_Register);
}
