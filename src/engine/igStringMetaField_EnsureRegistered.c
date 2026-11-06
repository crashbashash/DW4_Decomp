extern char igStringMetaField_Register[];
void igStringMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStringMetaField_Register);
}
