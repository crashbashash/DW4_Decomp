extern "C" {
void *beNDMWShinkaObjectList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c98f0(void);
}
void FUN_003c98f0(void)
{
    igMetaObject_RunStaticInit(beNDMWShinkaObjectList_Register);
}
