extern "C" {
void *bePlaySE_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00344890(void);
}
void FUN_00344890(void)
{
    igMetaObject_RunStaticInit(bePlaySE_Register);
}
