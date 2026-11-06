extern char igDataList_Register[];
void igDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDataList_Register);
}
