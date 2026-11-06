extern "C" {
void *igFileName_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00334c70(void);
}
void FUN_00334c70(void)
{
    igMetaObject_RunStaticInit(igFileName_Register);
}
