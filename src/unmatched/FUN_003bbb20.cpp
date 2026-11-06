extern "C" {
void *beNDMWStageCtlInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bbb20(void);
}
void FUN_003bbb20(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtlInfoRam_Register);
}
