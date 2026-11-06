void *igBoxComponent_Register(void);
void igBoxComponent_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBoxComponent_Register);
}
