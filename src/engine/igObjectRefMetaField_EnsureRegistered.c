extern char igObjectRefMetaField_Register[];
void igObjectRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igObjectRefMetaField_Register);
}
