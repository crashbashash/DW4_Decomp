extern "C" {
void *beCriHandle_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00366b20(void);
}
void FUN_00366b20(void)
{
    igMetaObject_RunStaticInit(beCriHandle_Register);
}
