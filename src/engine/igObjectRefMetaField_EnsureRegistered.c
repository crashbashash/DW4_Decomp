/* Runs the class's one-time static initialisation by handing its registrar,
 * igObjectRefMetaField_Register, to igMetaObject_RunStaticInit (the 12-byte thunk pattern shared
 * by every class.md). */
extern char igObjectRefMetaField_Register[];
void igObjectRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igObjectRefMetaField_Register);
}
