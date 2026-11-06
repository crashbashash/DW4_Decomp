extern "C" {
void *beCopyTransform_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00367f40(void);
}
void FUN_00367f40(void)
{
    igMetaObject_RunStaticInit(beCopyTransform_Register);
}
