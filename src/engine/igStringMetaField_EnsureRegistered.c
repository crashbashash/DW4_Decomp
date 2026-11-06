/* Runs the class's one-time static initialisation by handing its registrar,
 * igStringMetaField_Register, to igMetaObject_RunStaticInit (the 12-byte thunk pattern shared by
 * every class.md). */
extern char igStringMetaField_Register[];
void igStringMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStringMetaField_Register);
}
