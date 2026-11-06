extern "C" {
void *beOptInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034d160(void);
}
void FUN_0034d160(void)
{
    igMetaObject_RunStaticInit(beOptInfo_Register);
}
