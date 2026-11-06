extern "C" {
void *beWaterMoveData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00340990(void);
}
void FUN_00340990(void)
{
    igMetaObject_RunStaticInit(beWaterMoveData_Register);
}
