void *igGuiComponent_Register(void);
void igGuiComponent_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponent_Register);
}
