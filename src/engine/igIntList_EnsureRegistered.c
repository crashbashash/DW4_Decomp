extern char igIntList_Register[];
void igIntList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIntList_Register);
}
