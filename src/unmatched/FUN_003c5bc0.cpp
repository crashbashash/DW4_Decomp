extern "C" {
void *beNDMWMcSlotXbox_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c5bc0(void);
}
void FUN_003c5bc0(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotXbox_Register);
}
