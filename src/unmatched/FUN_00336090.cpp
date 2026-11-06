extern "C" {
void *igTextureBindAttrList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00336090(void);
}
void FUN_00336090(void)
{
    igMetaObject_RunStaticInit(igTextureBindAttrList_Register);
}
