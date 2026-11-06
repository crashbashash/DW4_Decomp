extern "C" {
void *beNDMWSaveIntf_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bcdd0(void);
}
void FUN_003bcdd0(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntf_Register);
}
