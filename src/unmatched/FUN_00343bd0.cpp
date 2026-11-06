extern "C" {
void *beBinDataObject_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00343bd0(void);
}
void FUN_00343bd0(void)
{
    igMetaObject_RunStaticInit(beBinDataObject_Register);
}
