void *igEnumMetaField_Register(void);
void igEnumMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEnumMetaField_Register);
}
