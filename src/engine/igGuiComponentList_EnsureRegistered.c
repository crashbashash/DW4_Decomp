void *igGuiComponentList_Register(void);
void igGuiComponentList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentList_Register);
}
