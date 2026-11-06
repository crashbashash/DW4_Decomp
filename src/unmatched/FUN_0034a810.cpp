extern "C" {
void *beSvSlotGC_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034a810(void);
}
void FUN_0034a810(void)
{
    igMetaObject_RunStaticInit(beSvSlotGC_Register);
}
