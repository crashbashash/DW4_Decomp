void *igRadioGroupModel_Register(void);
void igRadioGroupModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igRadioGroupModel_Register);
}
