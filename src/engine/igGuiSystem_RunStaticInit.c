void *igGuiSystem_Register(void);
void igGuiSystem_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystem_Register);
}
