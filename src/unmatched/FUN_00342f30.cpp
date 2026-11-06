extern "C" {
void *beSystem_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00342f30(void);
}
void FUN_00342f30(void)
{
    igMetaObject_RunStaticInit(beSystem_Register);
}
