extern "C" {
void *bePadManager_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034cb30(void);
}
void FUN_0034cb30(void)
{
    igMetaObject_RunStaticInit(bePadManager_Register);
}
