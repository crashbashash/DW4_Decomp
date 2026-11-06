extern "C" {
void *beSvSlotXbox_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034a9a0(void);
}
void FUN_0034a9a0(void)
{
    igMetaObject_RunStaticInit(beSvSlotXbox_Register);
}
