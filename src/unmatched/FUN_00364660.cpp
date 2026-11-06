extern "C" {
void *beDataObjObjectList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00364660(void);
}
void FUN_00364660(void)
{
    igMetaObject_RunStaticInit(beDataObjObjectList_Register);
}
