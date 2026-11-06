extern char igObjectList_Register[];
void igObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igObjectList_Register);
}
