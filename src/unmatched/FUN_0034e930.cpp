extern "C" {
void *beNodeAnim_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034e930(void);
}
void FUN_0034e930(void)
{
    igMetaObject_RunStaticInit(beNodeAnim_Register);
}
