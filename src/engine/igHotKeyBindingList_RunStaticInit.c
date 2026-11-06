void *igHotKeyBindingList_Register(void);
void igHotKeyBindingList_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igHotKeyBindingList_Register);
}
