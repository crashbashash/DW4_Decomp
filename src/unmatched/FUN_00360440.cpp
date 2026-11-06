extern "C" {
void *beGeneraterItemDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00360440(void);
}
void FUN_00360440(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemDataList_Register);
}
