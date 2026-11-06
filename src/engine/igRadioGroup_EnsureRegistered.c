void *igRadioGroup_Register(void);
void igRadioGroup_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRadioGroup_Register);
}
