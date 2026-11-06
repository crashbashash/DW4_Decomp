extern "C" {
void *beNDMWStageCtlInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bbc90(void);
}
void FUN_003bbc90(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtlInfo_Register);
}
