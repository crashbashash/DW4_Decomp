extern "C" {
void *beNumVerDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034d9d0(void);
}
void FUN_0034d9d0(void)
{
    igMetaObject_RunStaticInit(beNumVerDataList_Register);
}
