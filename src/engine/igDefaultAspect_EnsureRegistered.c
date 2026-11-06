void *igDefaultAspect_Register(void);
void igDefaultAspect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDefaultAspect_Register);
}
