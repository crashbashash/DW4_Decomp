extern "C" {
void *beBkColor_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00369f80(void);
}
void FUN_00369f80(void)
{
    igMetaObject_RunStaticInit(beBkColor_Register);
}
