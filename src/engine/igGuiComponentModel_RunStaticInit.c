void *igGuiComponentModel_Register(void);
void igGuiComponentModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiComponentModel_Register);
}
