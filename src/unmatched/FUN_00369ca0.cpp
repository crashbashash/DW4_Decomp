extern "C" {
void *beBkColorInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00369ca0(void);
}
void FUN_00369ca0(void)
{
    igMetaObject_RunStaticInit(beBkColorInfo_Register);
}
