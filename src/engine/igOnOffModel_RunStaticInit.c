void *igOnOffModel_Register(void);
void igOnOffModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igOnOffModel_Register);
}
