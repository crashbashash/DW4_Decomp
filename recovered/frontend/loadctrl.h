/* recovered/frontend/loadctrl.h — behavioral interface for the Game Start
 * load controller (Gap::Bec::beNDMWLoadCtrl2).
 *
 * Host records, not packed PS2 objects. Field offsets and widths come from
 * data/reflection.json and the retail lw/sb/lbu instructions at 0x003f1a80
 * (update, vfunc_31) and 0x003f2490 (message handler, vfunc_34).
 *
 * The recovery is written over one flat, word-addressed "world" (peek/poke/
 * call) so it mirrors the retail instruction stream exactly; the verifier runs
 * the same world under a restricted R5900 interpreter and compares the two.
 * The structs below document the object layouts the addresses refer to.
 *
 * Naming note: the retail second argument ("frame") is the per-frame context
 * the manager framework passes to a base-info manager method. Only the two
 * fields this controller reads are used: +0x18 and +0x28, the *named work
 * registry* — the object FUN_003022c0() searches by name to yield the "CTRL"
 * (beNDMWLoadCtrl2CtrlData) and "COMMONINTF" (beNDMWLoadCtrl2CommonIntf)
 * children. Its C++ owner is not pinned; it is left structural, not guessed.
 */
#ifndef DW4_RECOVERED_LOADCTRL_H
#define DW4_RECOVERED_LOADCTRL_H
#include <stdint.h>

/* Documented layouts (addresses in the world): */
/* Gap::Bec::beNDMWLoadCtrl2 (this): +0x0c insight, +0x14 messenger,
 *   +0x24 cameraMode, +0x28 lightMode. */
/* "frame": +0x18 (manager-only), +0x28 work registry. */
/* Gap::Bec::beNDMWLoadCtrl2CtrlData ("CTRL"): +0x10 isTitle, +0x14 st0,
 *   +0x18 st1, +0x1c st2, +0x20 st3. */
/* Gap::Bec::beNDMWLoadCtrl2CommonIntf ("COMMONINTF"): +0x28 flagWork list,
 *   +0x30 intfStat, +0x34 mcUtilCtrl, +0x3c difficultMode. */
typedef struct {
    void *user;
    int32_t (*peek)(void *user, int32_t addr, int width);          /* sign-extended */
    void    (*poke)(void *user, int32_t addr, int width, int32_t v);
    /* a[0..4] are the EE argument registers a0..a3 then t0; missing ones zero. */
    int32_t (*call)(void *user, int32_t addr, const int32_t a[5]);
} Dw4LoadApi;

#define DW4_LOAD_CTRL        0x518130   /* "CTRL"       */
#define DW4_LOAD_COMMONINTF  0x518138   /* "COMMONINTF" */
/* FUN_003022c0()'s name-table base is the *value* at 0x585be0 (retail lw). */
#define DW4_LOAD_TBL         P32(0x585be0)

void dw4_loadctrl_update(int32_t self, int32_t frame, const Dw4LoadApi *api);
int32_t dw4_loadctrl_message(int32_t self, int32_t frame, int32_t info, const Dw4LoadApi *api);

#endif /* DW4_RECOVERED_LOADCTRL_H */
