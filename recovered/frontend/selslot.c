/* recovered/frontend/selslot.c — behavioral reconstruction of the
 * Gap::Bec::beNDMWLoadIntf2SelSlot per-screen helpers.
 *
 * NOT a matching decompilation and not in src/.  A port-facing behavioral
 * reference, checked by scripts/verify_loadintf2.py, which runs the original
 * MIPS instructions of the master update (0x003e4750) AND, for these helpers,
 * the original MIPS of the helper itself through the restricted R5900
 * interpreter, then compares the ordered engine calls (with their meaningful
 * arguments), the 0x003e3e00 vec3 temporary payload, and every non-stack byte
 * written.  The helpers' own callees (the text-order / model helpers
 * 0x003e4030, 0x003e42a0, 0x003e3e00, 0x003e4480, 0x003ebe00, 0x003ec050,
 * 0x003e4280, 0x003e44d0, 0x003ee190, 0x0039b810) are stubbed identically on
 * both sides.
 *
 * The SELSLOT record (docs/engine/load-intf2.md):
 *   +0x14 padManager  +0x18 CommMdlCtrl  +0x1c TextOrder  +0x20 manager
 *   +0x24..+0x30 inherited per-player state
 *   +0x34 isOpen  +0x35 isSelect  +0x36 isCansel  +0x37 isEnd
 *   +0x38 mode    +0x3c markCur   +0x40 selPoint  +0x44 kind
 *   +0x48 isMarksOn  +0x4c..+0x58 st0..st3
 */
#include "selslot.h"
#include "textorder.h"
#include "completion.h"

#define P32(a)     api->peek(api->user, (a), 4)
#define P8(a)      api->peek(api->user, (a), 1)
#define W32(a, v)  api->poke(api->user, (a), 4, (v))
#define W8(a, v)   api->poke(api->user, (a), 1, (v))
#define CALL(addr, ...) api->call(api->user, (addr), (const int32_t[8]){__VA_ARGS__})

/* The "made" flag of the model at mark-table index `k`: the record is
 * SELSLOT+0x20 -> +0x34 -> +0x2c -> +0x10 -> [k]; its +8 byte is the flag.
 * A null record indexes address 0+8, mirroring the retail load. */
static int32_t made(const Dw4LoadIntf2Api *api, int32_t self, int32_t k)
{
    int32_t a = P32(P32(P32(P32(self + 0x20) + 0x34) + 0x2c) + 0x10);
    return P8(P32(a + k * 4) + 8);
}

/* Publish one cursor/mark entry when its model is made, or close it when not.
 * `idx` is the per-player bar index, `mark` the mark token, `anim` the open
 * animation token, `made` the model flag.  Matches the repeated retail shape
 * `if (made) { if (!Fun4480(...)) Fun3e3e00(...,&vec,0); else Fun4030(...); }
 * else if (Fun4480(...)==1) Fun42a0(...,SQ_CLOSE,0);`  A `open_first` form
 * (used when the entry is the selected one) always opens. */
static void pub_mark_made(const Dw4LoadIntf2Api *api, int32_t owner, int32_t idx,
                          int32_t mark, int32_t anim)
{
    if (CALL(0x3e4480, owner, idx, mark) == 0) {
        int32_t v = P32(owner + 0x1c);
        W32(LI2_TMP(0x20) + 0, v);
        W32(LI2_TMP(0x20) + 4, P32(owner + 0x20));
        W32(LI2_TMP(0x20) + 8, P32(owner + 0x24));
        CALL(0x3e3e00, owner, idx, mark, anim, LI2_TMP(0x20), 0);
    } else {
        CALL(0x3e4030, owner, idx, mark, anim, 0);
    }
}

static void pub_mark_close(const Dw4LoadIntf2Api *api, int32_t owner, int32_t idx,
                           int32_t mark)
{
    if (CALL(0x3e4480, owner, idx, mark) == 1)
        CALL(0x3e42a0, owner, idx, mark, SS_T_CLOSE, 0);
}

/* 0x003e0b80 — clear the SELSLOT run state. */
void ss_clear(const Dw4LoadIntf2Api *api, int32_t self)
{
    W8(self + 0x34, 0);
    W8(self + 0x36, 0);
    W8(self + 0x38, 0);
    W8(self + 0x35, 0);
    W8(self + 0x38, 0);
    W32(self + 0x4c, 0);
    W32(self + 0x58, 0);
    W32(self + 0x54, 0);
    W32(self + 0x50, 0);
}

/* 0x003e0bb0 — initialise the SELSLOT state from the manager's mode. */
void ss_init(const Dw4LoadIntf2Api *api, int32_t self)
{
    int32_t m = P32(self + 0x20);
    int32_t mode;
    ss_clear(api, self);
    W32(self + 0x3c, 0);
    mode = P32(m + 0x38);
    if (mode == 2) {
        W32(self + 0x2c, 9);
        W32(self + 0x24, 2);
    } else if (mode == 1) {
        W32(self + 0x2c, 2);
        W32(self + 0x24, 1);
    } else if (mode == 0) {
        W32(self + 0x2c, 5);
        W32(self + 0x24, 0);
    }
}

/* 0x003e2a80 — reset the cursor state and publish one slot line.
 * `p4` is the caller's fourth argument (incoming a3); the master update
 * passes none, so it is 0. */
void ss_pub_cursor(const Dw4LoadIntf2Api *api, int32_t self, int32_t p4)
{
    int32_t base = p4;
    int32_t st;
    W32(self + 0x4c, 1);
    W32(self + 0x58, 0);
    W32(self + 0x54, 0);
    W32(self + 0x50, 0);
    W8(self + 0x35, 0);
    st = P32(self + 0x24);
    if (st != 2 && st != 1)
        base = (P32(self + 0x44) == 0) ? SS_TBL_SQSELECT01 : SS_TBL_SQSELECT1A;
    CALL(0x3e4030, P32(self + 0x18), P32(self + 0x30), SS_T_SLOTCURSOR,
         P32(base + P32(self + 0x3c) * 8), 0);
}

/* 0x003e2b10 — publish/finish the slot marks.  Returns SELSLOT+0x38
 * (0 while running, 1 when the screen's marks are complete). */
int32_t ss_marks(const Dw4LoadIntf2Api *api, int32_t self)
{
    int32_t ret;
    if (P32(self + 0x4c) == 2) {
        ret = 1;
        if (P8(self + 0x38) != 1) {
            int32_t st = P32(self + 0x24);
            if (st != 2 && st != 1) {
                int32_t owner = P32(self + 0x18);
                int32_t idx = P32(self + 0x30);
                int32_t q = P32(self + 0x50);
                if (q == 1) {
                    if (cm_close_empty(api, owner) == 1) {
                        W8(self + 0x38, 1);
                        W32(self + 0x50, q + 1);
                        W32(self + 0x58, 0);
                        W32(self + 0x54, 0);
                    }
                } else if (q == 0) {
                    int32_t to = P32(self + 0x1c);
                    int32_t i;
                    CALL(0x3e42a0, owner, idx, SS_T_SLOTBASE, SS_T_CLOSE, 1);
                    CALL(0x3e42a0, owner, idx, SS_T_SLOTCURSOR, SS_T_CLOSE, 1);
                    CALL(0x3e42a0, owner, idx, SS_T_MEMICONWIN, SS_T_CLOSE, 1);
                    to_pub(api, to, (idx << 0x10) | 0x100c);
                    to_pub(api, to, (idx << 0x10) | 0x1100);
                    to_pub(api, to, (idx << 0x10) | 0x102e);
                    if (P32(self + 0x44) == 0) {
                        for (i = 0; i < 2; i++) {
                            if (i == 1) {
                                if (CALL(0x3e4480, owner, idx * 2 + 1, SS_T_SLOTMARK02) == 1)
                                    CALL(0x3e42a0, owner, idx * 2 + 1, SS_T_SLOTMARK02, SS_T_CLOSE, 0);
                            } else if (i == 0) {
                                if (CALL(0x3e4480, owner, idx << 1, SS_T_SLOTMARK02) == 1)
                                    CALL(0x3e42a0, owner, idx << 1, SS_T_SLOTMARK02, SS_T_CLOSE, 0);
                            }
                        }
                    } else {
                        for (i = 0; i < 5; i++) {
                            if (i == 4) {
                                if (CALL(0x3e4480, owner, idx << 1, SS_T_SLOTMARK02) == 1)
                                    CALL(0x3e42a0, owner, idx << 1, SS_T_SLOTMARK02, SS_T_CLOSE, 0);
                            } else if (i == 3) {
                                if (CALL(0x3e4480, owner, idx * 5 + 3, SS_T_SLOTMARK01) == 1)
                                    CALL(0x3e42a0, owner, idx * 5 + 3, SS_T_SLOTMARK01, SS_T_CLOSE, 0);
                            } else if (i == 2) {
                                if (CALL(0x3e4480, owner, idx * 5 + 2, SS_T_SLOTMARK01) == 1)
                                    CALL(0x3e42a0, owner, idx * 5 + 2, SS_T_SLOTMARK01, SS_T_CLOSE, 0);
                            } else if (i == 1) {
                                if (CALL(0x3e4480, owner, idx * 5 + 1, SS_T_SLOTMARK01) == 1)
                                    CALL(0x3e42a0, owner, idx * 5 + 1, SS_T_SLOTMARK01, SS_T_CLOSE, 0);
                            } else if (i == 0) {
                                if (CALL(0x3e4480, owner, idx * 5, SS_T_SLOTMARK01) == 1)
                                    CALL(0x3e42a0, owner, idx * 5, SS_T_SLOTMARK01, SS_T_CLOSE, 0);
                            }
                        }
                    }
                    W32(self + 0x50, q + 1);
                    W32(self + 0x58, 0);
                    W32(self + 0x54, 0);
                }
            }
            ret = P8(self + 0x38);
        }
    } else {
        ret = 0;
    }
    return ret;
}

/* 0x003e0c40 — open/refresh the slot base and marks.  `mark` defaults to the
 * current mark when -1.  Returns SELSLOT+0x34 (isOpen). */
int32_t ss_open(const Dw4LoadIntf2Api *api, int32_t self, int32_t mark)
{
    int32_t ret;
    if (P32(self + 0x4c) == 0) {
        int32_t mgr = P32(self + 0x20);
        int32_t st = P32(self + 0x24);
        if (st != 2 && st != 1) {
            int32_t q = P32(self + 0x50);
            int32_t owner, idx, to, i;
            if (q == 2) {
                if (cm_open_empty(api, P32(self + 0x18)) == 1) {
                    W8(self + 0x34, 1);
                    W32(self + 0x4c, P32(self + 0x4c) + 1);
                    W32(self + 0x58, 0);
                    W32(self + 0x54, 0);
                    W32(self + 0x50, 0);
                }
            } else if (q == 1) {
                if (cm_open_empty(api, P32(self + 0x18)) == 1) {
                    owner = P32(self + 0x18);
                    idx = P32(self + 0x30);
                    to = P32(self + 0x1c);
                    if (P32(self + 0x44) == 0) {
                        const int32_t tbl = SS_TBL_SQSELECT01;
                        int32_t cur = P32(self + 0x3c);
                        W32(LI2_TMP(0x21) + 0, P32(owner + 0x1c));
                        W32(LI2_TMP(0x21) + 4, P32(owner + 0x20));
                        W32(LI2_TMP(0x21) + 8, P32(owner + 0x24));
                        CALL(0x3e3e00, owner, idx, SS_T_SLOTCURSOR,
                             P32(tbl + cur * 8), LI2_TMP(0x21), 1);
                        for (i = 0; i < 2; i++) {
                            int32_t mk = P32(tbl + i * 8 + 4);
                            if (made(api, self, mk) == 1) {
                                if (i == 1)
                                    pub_mark_made(api, owner, idx * 2 + 1, SS_T_SLOTMARK02, SS_T_OPEN02);
                                else if (i == 0)
                                    pub_mark_made(api, owner, idx << 1, SS_T_SLOTMARK02, SS_T_OPEN01);
                            }
                        }
                        to_set(api, to, (idx << 0x10) | 0x100c, 0);
                        if (cur == 1)
                            to_set(api, to, (idx << 0x10) | 0x1101, 0);
                        else if (cur == 0)
                            to_set(api, to, (idx << 0x10) | 0x1100, 0);
                        if (made(api, self, P32(tbl + 4 + cur * 8)) == 1) {
                            W32(self + 0x48, 1);
                            to_pub(api, to, (idx << 0x10) | 0x102e);
                        } else {
                            W32(self + 0x48, 0);
                            to_set(api, to, (idx << 0x10) | 0x102e, 0);
                        }
                        W32(self + 0x50, q + 1);
                        W32(self + 0x58, 0);
                        W32(self + 0x54, 0);
                    } else {
                        const int32_t tbl = SS_TBL_SQSELECT1A;
                        int32_t cur = P32(self + 0x3c);
                        W32(LI2_TMP(0x21) + 0, P32(owner + 0x1c));
                        W32(LI2_TMP(0x21) + 4, P32(owner + 0x20));
                        W32(LI2_TMP(0x21) + 8, P32(owner + 0x24));
                        CALL(0x3e3e00, owner, idx, SS_T_SLOTCURSOR,
                             P32(tbl + cur * 8), LI2_TMP(0x21), 1);
                        for (i = 0; i < 5; i++) {
                            int32_t mk = P32(tbl + i * 8 + 4);
                            if (made(api, self, mk) == 1) {
                                if (i == 4)
                                    pub_mark_made(api, owner, idx << 1, SS_T_SLOTMARK02, SS_T_OPEN02);
                                else if (i == 3)
                                    pub_mark_made(api, owner, idx * 5 + 3, SS_T_SLOTMARK01, SS_T_OPEN1D);
                                else if (i == 2)
                                    pub_mark_made(api, owner, idx * 5 + 2, SS_T_SLOTMARK01, SS_T_OPEN1C);
                                else if (i == 1)
                                    pub_mark_made(api, owner, idx * 5 + 1, SS_T_SLOTMARK01, SS_T_OPEN1B);
                                else if (i == 0)
                                    pub_mark_made(api, owner, idx * 5, SS_T_SLOTMARK01, SS_T_OPEN1A);
                            }
                        }
                        to_set(api, to, (idx << 0x10) | 0x100c, 0);
                        if (cur == 4)
                            to_set(api, to, (idx << 0x10) | 0x1101, 0);
                        else if (cur == 3)
                            to_set(api, to, (idx << 0x10) | 0x1105, 0);
                        else if (cur == 2)
                            to_set(api, to, (idx << 0x10) | 0x1104, 0);
                        else if (cur == 1)
                            to_set(api, to, (idx << 0x10) | 0x1103, 0);
                        else if (cur == 0)
                            to_set(api, to, (idx << 0x10) | 0x1102, 0);
                        if (made(api, self, P32(tbl + 4 + cur * 8)) == 1) {
                            W32(self + 0x48, 1);
                            to_pub(api, to, (idx << 0x10) | 0x102e);
                        } else {
                            W32(self + 0x48, 0);
                            to_set(api, to, (idx << 0x10) | 0x102e, 0);
                        }
                        W32(self + 0x50, q + 1);
                        W32(self + 0x58, 0);
                        W32(self + 0x54, 0);
                    }
                }
            } else if (q == 0) {
                if (mark != -1)
                    W32(self + 0x3c, mark);
                owner = P32(self + 0x18);
                idx = P32(self + 0x30);
                if (P8(P32(mgr + 0x34) + 0xf) == 0) {
                    W32(LI2_TMP(0x22) + 0, P32(owner + 0x1c));
                    W32(LI2_TMP(0x22) + 4, P32(owner + 0x20));
                    W32(LI2_TMP(0x22) + 8, P32(owner + 0x24));
                    CALL(0x3e3e00, owner, idx, SS_T_SLOTBASE, SS_T_OPENPS01,
                         LI2_TMP(0x22), 1);
                    W32(self + 0x44, 0);
                } else {
                    W32(LI2_TMP(0x22) + 0, P32(owner + 0x1c));
                    W32(LI2_TMP(0x22) + 4, P32(owner + 0x20));
                    W32(LI2_TMP(0x22) + 8, P32(owner + 0x24));
                    CALL(0x3e3e00, owner, idx, SS_T_SLOTBASE, SS_T_OPENPS02,
                         LI2_TMP(0x22), 1);
                    W32(self + 0x44, 1);
                }
                W32(LI2_TMP(0x23) + 0, P32(owner + 0x1c));
                W32(LI2_TMP(0x23) + 4, P32(owner + 0x20));
                W32(LI2_TMP(0x23) + 8, P32(owner + 0x24));
                CALL(0x3e3e00, owner, idx, SS_T_MEMICONWIN, SS_T_OPEN,
                     LI2_TMP(0x23), 1);
                W8(self + 0x37, 0);
                W32(self + 0x50, q + 1);
                W32(self + 0x58, 0);
                W32(self + 0x54, 0);
            }
        }
        ret = P8(self + 0x34);
    } else {
        ret = 0;
    }
    return ret;
}

/* 0x003e3070 — highlight the selected slot's mark.  `sel` is the selected
 * mark index (0xffffffff = none).  Publishes the marks again, suppressing the
 * selected one, and reconciles the +0x48 open/close flag. */
void ss_select(const Dw4LoadIntf2Api *api, int32_t self, int32_t sel)
{
    int32_t st = P32(self + 0x24);
    int32_t owner, idx, i, tbl;
    if (st == 2 || st == 1)
        return;
    owner = P32(self + 0x18);
    idx = P32(self + 0x30);
    if (P32(self + 0x44) == 0) {
        tbl = SS_TBL_SQSELECT01;
        for (i = 0; i < 2; i++) {
            int32_t mk = P32(tbl + i * 8 + 4);
            int32_t m = made(api, self, mk);
            if (sel == i)
                m = 0;                    /* the selected entry is not opened */
            if (m == 1) {
                if (i == 1)
                    pub_mark_made(api, owner, idx * 2 + 1, SS_T_SLOTMARK02, SS_T_OPEN02);
                else if (i == 0)
                    pub_mark_made(api, owner, idx << 1, SS_T_SLOTMARK02, SS_T_OPEN01);
            } else if (i == 1) {
                pub_mark_close(api, owner, idx * 2 + 1, SS_T_SLOTMARK02);
            } else if (i == 0) {
                pub_mark_close(api, owner, idx << 1, SS_T_SLOTMARK02);
            }
        }
        if (P32(self + 0x48) == 0) {
            if (made(api, self, P32(tbl + 4 + P32(self + 0x3c) * 8)) == 1) {
                W32(self + 0x48, 1);
                to_pub(api, P32(self + 0x1c), (idx << 0x10) | 0x102e);
            }
        } else if (made(api, self, P32(tbl + 4 + P32(self + 0x3c) * 8)) != 1) {
            W32(self + 0x48, 0);
            to_set(api, P32(self + 0x1c), (idx << 0x10) | 0x102e, 0);
        }
    } else {
        tbl = SS_TBL_SQSELECT1A;
        for (i = 0; i < 5; i++) {
            int32_t mk = P32(tbl + i * 8 + 4);
            int32_t m = made(api, self, mk);
            if (sel == i)
                m = 0;                    /* the selected entry is not opened */
            if (m == 1) {
                if (i == 4)
                    pub_mark_made(api, owner, idx << 1, SS_T_SLOTMARK02, SS_T_OPEN02);
                else if (i == 3)
                    pub_mark_made(api, owner, idx * 5 + 3, SS_T_SLOTMARK01, SS_T_OPEN1D);
                else if (i == 2)
                    pub_mark_made(api, owner, idx * 5 + 2, SS_T_SLOTMARK01, SS_T_OPEN1C);
                else if (i == 1)
                    pub_mark_made(api, owner, idx * 5 + 1, SS_T_SLOTMARK01, SS_T_OPEN1B);
                else if (i == 0)
                    pub_mark_made(api, owner, idx * 5, SS_T_SLOTMARK01, SS_T_OPEN1A);
            } else if (i == 4) {
                pub_mark_close(api, owner, idx << 1, SS_T_SLOTMARK02);
            } else if (i == 3) {
                pub_mark_close(api, owner, idx * 5 + 3, SS_T_SLOTMARK01);
            } else if (i == 2) {
                pub_mark_close(api, owner, idx * 5 + 2, SS_T_SLOTMARK01);
            } else if (i == 1) {
                pub_mark_close(api, owner, idx * 5 + 1, SS_T_SLOTMARK01);
            } else if (i == 0) {
                pub_mark_close(api, owner, idx * 5, SS_T_SLOTMARK01);
            }
        }
        if (P32(self + 0x48) == 0) {
            if (made(api, self, P32(tbl + 4 + P32(self + 0x3c) * 8)) == 1) {
                W32(self + 0x48, 1);
                to_pub(api, P32(self + 0x1c), (idx << 0x10) | 0x102e);
            }
        } else if (made(api, self, P32(tbl + 4 + P32(self + 0x3c) * 8)) != 1) {
            W32(self + 0x48, 0);
            to_set(api, P32(self + 0x1c), (idx << 0x10) | 0x102e, 0);
        }
    }
}

/* 0x003e1760 — per-frame slot update: sample the pad, move the cursor,
 * confirm/cancel, publish the cursor and marks.  `ctrl` enables the pad
 * sample; `chk` requests the "open finished" answer.  Returns SELSLOT+0x35
 * (isSelect/committed). */
int32_t ss_update(const Dw4LoadIntf2Api *api, int32_t self, int32_t ctrl, int32_t chk)
{
    int32_t uVar13 = 0, iVar10, uVar1, uVar11;
    int32_t b7 = 0, b4 = 0, b5 = 0, b6 = 0;
    int32_t owner, idx, tbl;

    if (chk == 1) {
        if (P32(self + 0x4c) != 1)
            return 0;
        if (P8(self + 0x35) == 1)
            return 1;
    }
    iVar10 = P32(self + 0x20);
    if (ctrl == 1) {
        int32_t p = CALL(0x39b810, P32(self + 0x14), P32(self + 0x30));
        uVar13 = P32(p + 0x48);
        uVar1 = P32(p + 0x4c);
        uVar11 = P32(p + 0x1c) | P32(p + 0x20);
        b7 = 1;
        if (((uVar11 & 1) == 0) && (((uVar13 | uVar1) & 0x10) == 0))
            b7 = 0;
        b4 = ((uVar11 & 4) != 0) || (((uVar13 | uVar1) & 0x40) != 0);
        b5 = ((uVar11 & 8) != 0) || (((uVar13 | uVar1) & 0x80) != 0);
        b6 = ((uVar11 & 2) != 0) || (((uVar13 | uVar1) & 0x20) != 0);
    }
    if (P32(self + 0x24) == 2 || P32(self + 0x24) == 1)
        goto done;

    owner = P32(self + 0x18);
    idx = P32(self + 0x30);
    if (P32(self + 0x44) == 0) {
        int32_t i;
        tbl = SS_TBL_SQSELECT01;
        for (i = 0; i < 2; i++) {
            int32_t mk = P32(tbl + i * 8 + 4);
            if (made(api, self, mk) == 1) {
                if (i == 1)
                    pub_mark_made(api, owner, idx * 2 + 1, SS_T_SLOTMARK02, SS_T_OPEN02);
                else if (i == 0)
                    pub_mark_made(api, owner, idx << 1, SS_T_SLOTMARK02, SS_T_OPEN01);
            } else if (i == 1) {
                pub_mark_close(api, owner, idx * 2 + 1, SS_T_SLOTMARK02);
            } else if (i == 0) {
                pub_mark_close(api, owner, idx << 1, SS_T_SLOTMARK02);
            }
        }
        if (P32(self + 0x48) == 0) {
            if (made(api, self, P32(tbl + 4 + P32(self + 0x3c) * 8)) == 1) {
                W32(self + 0x48, 1);
                to_pub(api, P32(self + 0x1c), (idx << 0x10) | 0x102e);
            }
        } else if (made(api, self, P32(tbl + 4 + P32(self + 0x3c) * 8)) != 1) {
            W32(self + 0x48, 0);
            to_set(api, P32(self + 0x1c), (idx << 0x10) | 0x102e, 0);
        }
        if (P8(P32(iVar10 + 0x34) + 0xf) == 1) {
            W8(self + 0x37, 1);
            W8(self + 0x35, 1);
            W32(self + 0x4c, P32(self + 0x4c) + 1);
            W32(self + 0x58, 0);
            W32(self + 0x54, 0);
            W32(self + 0x50, 0);
            goto done;
        }
    } else {
        int32_t i;
        tbl = SS_TBL_SQSELECT1A;
        for (i = 0; i < 5; i++) {
            int32_t mk = P32(tbl + i * 8 + 4);
            if (made(api, self, mk) == 1) {
                if (i == 4)
                    pub_mark_made(api, owner, idx << 1, SS_T_SLOTMARK02, SS_T_OPEN02);
                else if (i == 3)
                    pub_mark_made(api, owner, idx * 5 + 3, SS_T_SLOTMARK01, SS_T_OPEN1D);
                else if (i == 2)
                    pub_mark_made(api, owner, idx * 5 + 2, SS_T_SLOTMARK01, SS_T_OPEN1C);
                else if (i == 1)
                    pub_mark_made(api, owner, idx * 5 + 1, SS_T_SLOTMARK01, SS_T_OPEN1B);
                else if (i == 0)
                    pub_mark_made(api, owner, idx * 5, SS_T_SLOTMARK01, SS_T_OPEN1A);
            } else if (i == 4) {
                pub_mark_close(api, owner, idx << 1, SS_T_SLOTMARK02);
            } else if (i == 3) {
                pub_mark_close(api, owner, idx * 5 + 3, SS_T_SLOTMARK01);
            } else if (i == 2) {
                pub_mark_close(api, owner, idx * 5 + 2, SS_T_SLOTMARK01);
            } else if (i == 1) {
                pub_mark_close(api, owner, idx * 5 + 1, SS_T_SLOTMARK01);
            } else if (i == 0) {
                pub_mark_close(api, owner, idx * 5, SS_T_SLOTMARK01);
            }
        }
        if (P8(P32(iVar10 + 0x34) + 0xf) == 0) {
            W8(self + 0x37, 1);
            W8(self + 0x35, 1);
            W32(self + 0x4c, P32(self + 0x4c) + 1);
            W32(self + 0x58, 0);
            W32(self + 0x54, 0);
            W32(self + 0x50, 0);
            goto done;
        }
        if (P32(self + 0x48) == 0) {
            if (made(api, self, P32(tbl + 4 + P32(self + 0x3c) * 8)) == 1) {
                W32(self + 0x48, 1);
                to_pub(api, P32(self + 0x1c), (idx << 0x10) | 0x102e);
            }
        } else if (made(api, self, P32(tbl + 4 + P32(self + 0x3c) * 8)) != 1) {
            W32(self + 0x48, 0);
            to_set(api, P32(self + 0x1c), (idx << 0x10) | 0x102e, 0);
        }
    }

    {
        int32_t q = P32(self + 0x50);
        if (q == 2) {
            if (cm_open_empty(api, owner) == 1) {
                CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR,
                     P32(tbl + P32(self + 0x3c) * 8), 0);
                W8(self + 0x35, 1);
                W32(self + 0x4c, P32(self + 0x4c) + 1);
                W32(self + 0x58, 0);
                W32(self + 0x54, 0);
                W32(self + 0x50, 0);
            }
        } else if (q == 1) {
            if (cm_open_empty(api, owner) == 1) {
                int32_t to = P32(self + 0x1c);
                int32_t cur = P32(self + 0x3c);
                CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR, P32(tbl + cur * 8), 0);
                if (P32(self + 0x44) == 0) {
                    if (cur == 1)
                        to_set(api, to, (idx << 0x10) | 0x1101, 0);
                    else if (cur == 0)
                        to_set(api, to, (idx << 0x10) | 0x1100, 0);
                } else {
                    if (cur == 4)
                        to_set(api, to, (idx << 0x10) | 0x1101, 0);
                    else if (cur == 3)
                        to_set(api, to, (idx << 0x10) | 0x1105, 0);
                    else if (cur == 2)
                        to_set(api, to, (idx << 0x10) | 0x1104, 0);
                    else if (cur == 1)
                        to_set(api, to, (idx << 0x10) | 0x1103, 0);
                    else if (cur == 0)
                        to_set(api, to, (idx << 0x10) | 0x1102, 0);
                }
                if (P32(self + 0x48) == 0) {
                    if (made(api, self, P32(tbl + cur * 8 + 4)) == 1) {
                        W32(self + 0x48, 1);
                        to_pub(api, to, (idx << 0x10) | 0x102e);
                    }
                } else if (made(api, self, P32(tbl + cur * 8 + 4)) != 1) {
                    W32(self + 0x48, 0);
                    to_set(api, to, (idx << 0x10) | 0x102e, 0);
                }
                W32(self + 0x50, 0);
                W32(self + 0x58, 0);
                W32(self + 0x54, 0);
            }
        } else if (q == 0) {
            if (P32(self + 0x44) == 0) {
                if (b7) {
                    if (P32(self + 0x3c) != 0) {
                        W32(self + 0x3c, 0);
                        CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR, SS_T_MOVE, 1);
                        W32(self + 0x50, P32(self + 0x50) + 1);
                        W32(self + 0x58, 0);
                        W32(self + 0x54, 0);
                    }
                } else if (b4) {
                    if (P32(self + 0x3c) != 1) {
                        W32(self + 0x3c, 1);
                        CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR, SS_T_MOVE, 1);
                        W32(self + 0x50, P32(self + 0x50) + 1);
                        W32(self + 0x58, 0);
                        W32(self + 0x54, 0);
                    }
                } else if ((uVar13 & 0x4000) == 0) {
                    if ((uVar13 & 0x2000) != 0) {
                        W8(self + 0x36, 1);
                        CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR, SS_T_CANCEL, 1);
                        W32(self + 0x50, 2);
                        W32(self + 0x58, 0);
                        W32(self + 0x54, 0);
                    }
                } else if (made(api, self, P32(tbl + P32(self + 0x3c) * 8 + 4)) == 1) {
                    ds_select(api, iVar10, idx);
                    W32(self + 0x40, P32(tbl + P32(self + 0x3c) * 8 + 4));
                    CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR, SS_T_ON, 1);
                    W32(self + 0x50, 2);
                    W32(self + 0x58, 0);
                    W32(self + 0x54, 0);
                }
            } else if ((uVar13 & 0x4000) == 0) {
                if ((uVar13 & 0x2000) == 0) {
                    if (b7) {
                        if (P32(self + 0x3c) != 0) {
                            W32(self + 0x3c, 0);
                            CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR, SS_T_MOVE, 1);
                            W32(self + 0x50, P32(self + 0x50) + 1);
                            W32(self + 0x58, 0);
                            W32(self + 0x54, 0);
                        }
                    } else if (b4) {
                        int32_t n = P32(self + 0x2c) - 1;
                        if (P32(self + 0x3c) != n) {
                            W32(self + 0x3c, n);
                            CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR, SS_T_MOVE, 1);
                            W32(self + 0x50, P32(self + 0x50) + 1);
                            W32(self + 0x58, 0);
                            W32(self + 0x54, 0);
                        }
                    } else {
                        int32_t cur = P32(self + 0x3c);
                        int32_t mx = P32(self + 0x2c) - 1;
                        if (cur != mx) {
                            if (b6) {
                                W32(self + 0x3c, cur + 1);
                                if (P32(self + 0x3c) < mx) {
                                    CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR, SS_T_MOVE, 1);
                                    W32(self + 0x50, P32(self + 0x50) + 1);
                                    W32(self + 0x58, 0);
                                    W32(self + 0x54, 0);
                                } else {
                                    W32(self + 0x3c, mx - 1);
                                }
                            } else if (b5) {
                                W32(self + 0x3c, cur - 1);
                                if (P32(self + 0x3c) < 0) {
                                    W32(self + 0x3c, 0);
                                } else {
                                    CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR, SS_T_MOVE, 1);
                                    W32(self + 0x50, P32(self + 0x50) + 1);
                                    W32(self + 0x58, 0);
                                    W32(self + 0x54, 0);
                                }
                            }
                        }
                    }
                } else {
                    W8(self + 0x36, 1);
                    CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR, SS_T_CANCEL, 1);
                    W32(self + 0x50, 2);
                    W32(self + 0x58, 0);
                    W32(self + 0x54, 0);
                }
            } else if (made(api, self, P32(tbl + P32(self + 0x3c) * 8 + 4)) == 1) {
                ds_select(api, iVar10, idx);
                W32(self + 0x40, P32(tbl + P32(self + 0x3c) * 8 + 4));
                CALL(0x3e4030, owner, idx, SS_T_SLOTCURSOR, SS_T_ON, 1);
                W32(self + 0x50, 2);
                W32(self + 0x58, 0);
                W32(self + 0x54, 0);
            }
        }
    }
done:
    return P8(self + 0x35);
}
