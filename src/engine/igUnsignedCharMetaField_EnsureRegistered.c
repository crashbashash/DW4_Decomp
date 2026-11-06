extern char igUnsignedCharMetaField_Register[];
void igUnsignedCharMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedCharMetaField_Register);
}
