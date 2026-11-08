extern "C" {
void FUN_003bd9c0(void);
extern struct WazaInfoRamMeta *DAT_0058b1f0[4];
void *beNDMWPanelWazaInfoRam_ResolveMetaObject(void);
}
struct WazaInfoRamMeta {
    int pad[9];
    int flags;
    bool ready() const { return (flags & 4) != 0; }
};
void *beNDMWPanelWazaInfoRam_ResolveMetaObject(void) {
    WazaInfoRamMeta *meta = DAT_0058b1f0[0];
    if (meta) {
        bool t;
        if ((t = meta->ready()) != false) goto end;
    }
    FUN_003bd9c0();
end:
    return DAT_0058b1f0[0];
}
