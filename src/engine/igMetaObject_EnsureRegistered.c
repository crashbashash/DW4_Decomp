extern char igMetaObject_Register[];
void igMetaObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMetaObject_Register);
}
