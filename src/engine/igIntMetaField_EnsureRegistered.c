extern char igIntMetaField_Register[];
void igIntMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIntMetaField_Register);
}
