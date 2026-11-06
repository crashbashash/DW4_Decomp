extern "C" {
void *beFontGeomAttrPairList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00362440(void);
}
void FUN_00362440(void)
{
    igMetaObject_RunStaticInit(beFontGeomAttrPairList_Register);
}
