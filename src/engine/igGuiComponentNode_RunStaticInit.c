void *igGuiComponentNode_Register(void);
void igGuiComponentNode_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiComponentNode_Register);
}
