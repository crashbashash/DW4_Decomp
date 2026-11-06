extern "C" {
void *beCriSfpData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00366620(void);
}
void FUN_00366620(void)
{
    igMetaObject_RunStaticInit(beCriSfpData_Register);
}
