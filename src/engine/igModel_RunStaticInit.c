void *igModel_Register(void);
void igModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igModel_Register);
}
