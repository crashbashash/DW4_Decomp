/* 0x002be760 - igMetaObject_EnsureRegistered: runs the class's one-time static
 * initialisation by handing its registrar, igMetaObject_Register, to
 * igMetaObject_RunStaticInit (the 12-byte thunk pattern shared by every
 * class; docs/engine/engine-boot.md, docs/engine/reflection-registration.md). */
extern char igMetaObject_Register[];
void igMetaObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMetaObject_Register);
}
