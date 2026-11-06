void *igGuiComponentAspect_Register(void);
void igGuiComponentAspect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentAspect_Register);
}
