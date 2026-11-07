extern "C" {
void beNDMWDegiData_RunStaticInit(void);
extern struct G *DAT_0058bd28[4];
void *beNDMWDegiData_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWDegiData_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bd28[0];
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (exceptions on); `if (ready = ...)` folds it away */
        ready = g->f & 4;
        if (ready != false) goto end;
    }
    beNDMWDegiData_RunStaticInit();
end:
    return DAT_0058bd28[0];
}
