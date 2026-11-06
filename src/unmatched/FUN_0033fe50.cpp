extern "C" {
void *igAppearanceListList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0033fe50(void);
}
void FUN_0033fe50(void)
{
    igMetaObject_RunStaticInit(igAppearanceListList_Register);
}
