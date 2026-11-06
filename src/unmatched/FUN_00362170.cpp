extern "C" {
void *beFont_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00362170(void);
}
void FUN_00362170(void)
{
    igMetaObject_RunStaticInit(beFont_Register);
}
