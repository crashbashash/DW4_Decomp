extern "C" {
void FUN_003c7090(void);
extern struct G *DAT_0058be38[4];
void *beNDMWLoadIntf2ComMdlCtrl_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadIntf2ComMdlCtrl_GetReadyMetaObject(void) {
    struct G *g = DAT_0058be38[0];
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (exceptions on); `if (ready = ...)` folds it away */
        ready = g->f & 4;
        if (ready != false) goto end;
    }
    FUN_003c7090();
end:
    return DAT_0058be38[0];
}
