extern "C" {
void beNDMWPanelObject_ResolveMetaObject(void);
void beNDMWPanelObject_GetMetaObject(void);
}
void beNDMWPanelObject_GetMetaObject(void)
{
    beNDMWPanelObject_ResolveMetaObject();
}
