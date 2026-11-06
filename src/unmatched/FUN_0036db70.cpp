extern "C" {
void *beAction2Data_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036db70(void);
}
void FUN_0036db70(void)
{
    igMetaObject_RunStaticInit(beAction2Data_Register);
}
