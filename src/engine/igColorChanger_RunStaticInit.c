void *igColorChanger_Register(void);
void igColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igColorChanger_Register);
}
