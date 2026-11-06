void *igGuiSystemModel_Register(void);
void igGuiSystemModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystemModel_Register);
}
