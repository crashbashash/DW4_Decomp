void *igHotKeyBinding_Register(void);
void igHotKeyBinding_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igHotKeyBinding_Register);
}
