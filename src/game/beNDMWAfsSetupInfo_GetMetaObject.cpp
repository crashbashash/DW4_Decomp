extern "C" {
void beNDMWAfsSetupInfo_ResolveMetaObject(void);
void beNDMWAfsSetupInfo_GetMetaObject(void);
}
void beNDMWAfsSetupInfo_GetMetaObject(void)
{
    beNDMWAfsSetupInfo_ResolveMetaObject();
}
