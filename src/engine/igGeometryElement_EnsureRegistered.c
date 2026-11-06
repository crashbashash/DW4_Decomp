void *igGeometryElement_Register(void);
void igGeometryElement_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGeometryElement_Register);
}
