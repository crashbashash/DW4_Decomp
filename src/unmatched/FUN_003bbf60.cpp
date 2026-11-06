extern "C" {
void *beNDMWStageCtl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bbf60(void);
}
void FUN_003bbf60(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtl_Register);
}
