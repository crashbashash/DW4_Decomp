/* Runs the class's one-time static initialisation by handing its registrar, igMetaObject_Register,
 * to igMetaObject_RunStaticInit (the 12-byte thunk pattern shared by every class.md). */
extern char igMetaObject_Register[];
void igMetaObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMetaObject_Register);
}
