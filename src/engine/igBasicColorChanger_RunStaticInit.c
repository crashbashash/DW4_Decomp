void *igBasicColorChanger_Register(void);
void igBasicColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBasicColorChanger_Register);
}
