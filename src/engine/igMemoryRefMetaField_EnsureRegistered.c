void *igMemoryRefMetaField_Register(void);
void igMemoryRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMemoryRefMetaField_Register);
}
