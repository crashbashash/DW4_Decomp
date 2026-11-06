void *igClearRenderer_Register(void);
void igClearRenderer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igClearRenderer_Register);
}
