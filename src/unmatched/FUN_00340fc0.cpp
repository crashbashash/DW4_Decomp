extern "C" {
void *beUnicode_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00340fc0(void);
}
void FUN_00340fc0(void)
{
    igMetaObject_RunStaticInit(beUnicode_Register);
}
