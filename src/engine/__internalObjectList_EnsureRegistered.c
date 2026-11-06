extern char __internalObjectList_Register[];
void __internalObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(__internalObjectList_Register);
}
