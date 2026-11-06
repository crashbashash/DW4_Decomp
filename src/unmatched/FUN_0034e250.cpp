extern "C" {
void *beNumberCtrlInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034e250(void);
}
void FUN_0034e250(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfo_Register);
}
