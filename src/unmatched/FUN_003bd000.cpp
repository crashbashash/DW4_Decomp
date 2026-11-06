extern "C" {
void *beNDMWSaveCtrlInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bd000(void);
}
void FUN_003bd000(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveCtrlInfo_Register);
}
