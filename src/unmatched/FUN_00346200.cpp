extern "C" {
void *beSeDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00346200(void);
}
void FUN_00346200(void)
{
    igMetaObject_RunStaticInit(beSeDataList_Register);
}
