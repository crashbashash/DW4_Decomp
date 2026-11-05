/* 0x002b7500 - igUnsignedCharMetaField_EnsureRegistered: runs the class's one-time static
 * initialisation by handing its registrar, igUnsignedCharMetaField_Register, to
 * igMetaObject_RunStaticInit (the 12-byte thunk pattern shared by every
 * class; docs/engine/engine-boot.md, docs/engine/reflection-registration.md). */
extern char igUnsignedCharMetaField_Register[];
void igUnsignedCharMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedCharMetaField_Register);
}
