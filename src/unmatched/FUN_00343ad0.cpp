extern "C" {
void *beStaticInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00343ad0(void);
}
void FUN_00343ad0(void)
{
    igMetaObject_RunStaticInit(beStaticInfo_Register);
}
