extern "C" {
void *beGeneraterItemData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00360620(void);
}
void FUN_00360620(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemData_Register);
}
