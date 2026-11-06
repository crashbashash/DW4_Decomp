void *igRawRefMetaField_Register(void);
void igRawRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRawRefMetaField_Register);
}
