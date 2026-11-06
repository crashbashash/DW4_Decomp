void *igTextElement_Register(void);
void igTextElement_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextElement_Register);
}
