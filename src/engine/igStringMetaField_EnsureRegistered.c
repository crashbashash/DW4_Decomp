/* 0x002b9940 - igStringMetaField_EnsureRegistered: runs the class's one-time static
 * initialisation by handing its registrar, igStringMetaField_Register, to
 * igMetaObject_RunStaticInit (the 12-byte thunk pattern shared by every
 * class; docs/engine/engine-boot.md, docs/engine/reflection-registration.md). */
extern char igStringMetaField_Register[];
void igStringMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStringMetaField_Register);
}
