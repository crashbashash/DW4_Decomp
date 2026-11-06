void *igFieldChangeView_Register(void);
void igFieldChangeView_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldChangeView_Register);
}
