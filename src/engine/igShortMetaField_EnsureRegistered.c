void *igShortMetaField_Register(void);
void igShortMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igShortMetaField_Register);
}
