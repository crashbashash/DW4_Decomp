extern char igUnsignedIntMetaField_Register[];
void igUnsignedIntMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedIntMetaField_Register);
}
