void *igAction_Register(void);
void igAction_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igAction_Register);
}
