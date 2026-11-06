extern "C" {
void *beGeneraterInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035f870(void);
}
void FUN_0035f870(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfo_Register);
}
