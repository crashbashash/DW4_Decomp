extern "C" {
void *beGeneraterItemDataOneList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00360860(void);
}
void FUN_00360860(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemDataOneList_Register);
}
