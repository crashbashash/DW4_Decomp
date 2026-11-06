extern "C" {
void *beSaveUtilInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00346b70(void);
}
void FUN_00346b70(void)
{
    igMetaObject_RunStaticInit(beSaveUtilInfo_Register);
}
