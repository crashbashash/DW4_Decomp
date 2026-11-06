void *igDefaultAspectElementList_Register(void);
void igDefaultAspectElementList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDefaultAspectElementList_Register);
}
