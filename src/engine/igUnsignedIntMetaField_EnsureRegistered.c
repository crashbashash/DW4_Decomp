/* 0x002b6f10 igUnsignedIntMetaField_EnsureRegistered: run the static-init callbacks of
 * igUnsignedIntMetaField_Register (0x002b6f20) once, through igMetaObject_RunStaticInit.
 * Same shape as igStringMetaField_EnsureRegistered. */
extern char igUnsignedIntMetaField_Register[];
void igUnsignedIntMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedIntMetaField_Register);
}
