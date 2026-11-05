/* 0x002c2f30 - igIntMetaField_EnsureRegistered: runs the class's one-time static
 * initialisation by handing its registrar, igIntMetaField_Register, to
 * igMetaObject_RunStaticInit (the 12-byte thunk pattern shared by every
 * class; docs/engine/engine-boot.md, docs/engine/reflection-registration.md). */
extern char igIntMetaField_Register[];
void igIntMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIntMetaField_Register);
}
