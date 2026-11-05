/* 0x002c2860 - __internalObjectList_EnsureRegistered: runs the class's one-time static
 * initialisation by handing its registrar, __internalObjectList_Register, to
 * igMetaObject_RunStaticInit (the 12-byte thunk pattern shared by every
 * class; docs/engine/engine-boot.md, docs/engine/reflection-registration.md). */
extern char __internalObjectList_Register[];
void __internalObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(__internalObjectList_Register);
}
