void *igMouseCursor_Register(void);
void igMouseCursor_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igMouseCursor_Register);
}
