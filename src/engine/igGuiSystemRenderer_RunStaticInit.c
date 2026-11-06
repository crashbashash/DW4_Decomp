void *igGuiSystemRenderer_Register(void);
void igGuiSystemRenderer_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystemRenderer_Register);
}
