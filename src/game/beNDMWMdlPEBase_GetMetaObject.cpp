extern "C" {
void beNDMWMdlPEBase_ResolveMetaObject(void);
void beNDMWMdlPEBase_GetMetaObject(void);
}
void beNDMWMdlPEBase_GetMetaObject(void)
{
    beNDMWMdlPEBase_ResolveMetaObject();
}
