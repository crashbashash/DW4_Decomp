extern "C" {
void *beUnicodeObj_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00361610(void);
}
void FUN_00361610(void)
{
    igMetaObject_RunStaticInit(beUnicodeObj_Register);
}
