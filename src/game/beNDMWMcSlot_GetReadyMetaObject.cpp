/* Run the class's static initialiser (FUN_003c60b0) unless its meta object record is already
 * marked ready (flag 4 of the word at +36), then return the record. Same shape as the sibling
 * *_GetReadyMetaObject units. */
extern "C" {
void FUN_003c60b0(void);
extern struct G *DAT_0058bcc8[4];
void *beNDMWMcSlot_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMcSlot_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bcc8[0];
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (3.0 -O3, exceptions on); a member-function spelling matched only under the combat -O3,p override */
        ready = g->f & 4;
        if (ready != false) goto end;
        asm { nop }
    }
    FUN_003c60b0();
end:
    return DAT_0058bcc8[0];
}
