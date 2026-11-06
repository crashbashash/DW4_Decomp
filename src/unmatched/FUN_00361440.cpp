extern "C" {
void *beUnicodeObjList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00361440(void);
}
void FUN_00361440(void)
{
    igMetaObject_RunStaticInit(beUnicodeObjList_Register);
}
