/* Runs the class's one-time static initialisation by handing its registrar,
 * igUnsignedCharMetaField_Register, to igMetaObject_RunStaticInit (the 12-byte thunk pattern
 * shared by every class.md). */
extern char igUnsignedCharMetaField_Register[];
void igUnsignedCharMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedCharMetaField_Register);
}
