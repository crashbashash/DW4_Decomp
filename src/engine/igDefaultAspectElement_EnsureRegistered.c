void *igDefaultAspectElement_Register(void);
void igDefaultAspectElement_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDefaultAspectElement_Register);
}
