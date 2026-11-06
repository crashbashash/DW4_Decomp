void *igRendererOrderedList_Register(void);
void igRendererOrderedList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRendererOrderedList_Register);
}
