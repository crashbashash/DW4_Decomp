void *igGuiComponentController_Register(void);
void igGuiComponentController_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentController_Register);
}
