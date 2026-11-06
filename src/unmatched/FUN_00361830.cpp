extern "C" {
void *beFontImageList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00361830(void);
}
void FUN_00361830(void)
{
    igMetaObject_RunStaticInit(beFontImageList_Register);
}
