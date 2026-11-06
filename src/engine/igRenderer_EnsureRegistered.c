void *igRenderer_Register(void);
void igRenderer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRenderer_Register);
}
