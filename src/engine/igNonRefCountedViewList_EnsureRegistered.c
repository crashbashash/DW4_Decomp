void *igNonRefCountedViewList_Register(void);
void igNonRefCountedViewList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedViewList_Register);
}
