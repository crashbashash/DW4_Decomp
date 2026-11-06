extern "C" {
void *beFontGeomAttrPair_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00362690(void);
}
void FUN_00362690(void)
{
    igMetaObject_RunStaticInit(beFontGeomAttrPair_Register);
}
