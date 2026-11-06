extern "C" {
void *beSaveUtilInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00346950(void);
}
void FUN_00346950(void)
{
    igMetaObject_RunStaticInit(beSaveUtilInfoRam_Register);
}
