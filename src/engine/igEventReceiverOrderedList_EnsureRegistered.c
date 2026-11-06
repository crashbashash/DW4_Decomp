void *igEventReceiverOrderedList_Register(void);
void igEventReceiverOrderedList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventReceiverOrderedList_Register);
}
