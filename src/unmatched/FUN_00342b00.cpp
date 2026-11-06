extern "C" {
void *beTargetObj_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00342b00(void);
}
void FUN_00342b00(void)
{
    igMetaObject_RunStaticInit(beTargetObj_Register);
}
