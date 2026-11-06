extern "C" {
void beNDMWSaveCtrl_ResolveMetaObject(void);
void beNDMWSaveCtrl_GetMetaObject(void);
}
void beNDMWSaveCtrl_GetMetaObject(void)
{
    beNDMWSaveCtrl_ResolveMetaObject();
}
