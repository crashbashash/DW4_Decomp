extern "C" {
void *beNumberCtrlInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034d740(void);
}
void FUN_0034d740(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoRam_Register);
}
