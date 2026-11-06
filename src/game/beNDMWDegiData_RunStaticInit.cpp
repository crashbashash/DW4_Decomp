extern "C" {
void *beNDMWDegiData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void beNDMWDegiData_RunStaticInit(void);
}
void beNDMWDegiData_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(beNDMWDegiData_Register);
}
