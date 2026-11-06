/* recovered/frontend/loadintf2.c — behavioral reconstruction of the Game Start
 * slot/character/name/difficulty/card interface, Gap::Bec::beNDMWLoadIntf2:
 *
 *   0x003e9430  vfunc_34  the family message handler      (8,252 bytes)
 *
 * NOT a matching decompilation and not in src/.  A behavioral
 * reference, checked by scripts/verify_loadintf2.py, which runs the original
 * MIPS instructions through a restricted R5900 interpreter and compares the
 * ordered engine calls (with their meaningful arguments) and every non-stack
 * byte written.  Engine and module callees are stubbed on both sides.
 *
 * Object field offsets are named from data/reflection.json (see the header).
 */
#include "loadintf2.h"
#include "selslot.h"
#include "textorder.h"
#include "completion.h"

#define P32(a)     api->peek(api->user, (a), 4)
#define P16(a)     api->peek(api->user, (a), 2)
#define P8(a)      api->peek(api->user, (a), 1)
#define W32(a, v)  api->poke(api->user, (a), 4, (v))
#define W16(a, v)  api->poke(api->user, (a), 2, (v))
#define W8(a, v)   api->poke(api->user, (a), 1, (v))
/* Missing argument registers are zero-padded by the C99 compound literal. */
#define CALL(addr, ...) api->call(api->user, (addr), (const int32_t[8]){__VA_ARGS__})

#define TBL        P32(0x585be0)     /* registry name-table base */
#define SYSTEM_REF 0x587110          /* global insight ref used by the guards */
#define SYS_NODE   0x587d08
#define SYS_NODE2  0x588518
#define SYS_NODE3  0x589208

/* Add one reference (+4) to a smart-managed object. */
static void addref(const Dw4LoadIntf2Api *api, int32_t obj)
{
    if (obj == 0)
        return;
    W32(obj + 4, P32(obj + 4) + 1);
}

/* Drop one reference; release at zero (the +4 count's low 23 bits). */
static void release(const Dw4LoadIntf2Api *api, int32_t obj)
{
    int32_t r;
    if (obj == 0)
        return;
    r = P32(obj + 4) - 1;
    W32(obj + 4, r);
    if ((r & 0x7fffff) == 0)
        CALL(0x2ff820, obj);
}

/* The "recreate the registry if it went null" block inlined throughout the
 * handler: create a fresh work through the global insight and store it. */
static void ensure_work_null(const Dw4LoadIntf2Api *api, int32_t frame)
{
    int32_t ins, w;
    ins = CALL(0x301000, frame);
    if (P8(LI2_GP_FLAG) == 0)
        ins = CALL(0x2f88e0, P32(SYSTEM_REF));
    w = CALL(0x36ae80, ins);
    addref(api, w);
    release(api, P32(frame + 0x28));
    W32(frame + 0x28, w);
    release(api, w);
}

/* 0x003e4750 — the per-frame master update for the Game Start interface.
 *
 * The function is a dispatch: it ensures the named working set, samples the pad
 * through the pad manager, then switches on the per-player record's state
 * (FUN_003e9260(interface+0x28, frame+8)+0x24) with a nested state machine on
 * the CTRL record's +0x24..+0x30.  Engine calls and the subordinate
 * per-screen/model helpers are stubbed on both sides of the verifier.
 */
#define ENSURE(name) ensure_named(api, v16, (name))
#define SET_ST(k)   (W32(v7 + 0x24, (k)), W32(v7 + 0x30, 0), W32(v7 + 0x2c, 0), W32(v7 + 0x28, 0))
#define SET_SUB(k)  (W32(v7 + 0x28, (k)), W32(v7 + 0x30, 0), W32(v7 + 0x2c, 0))
#define ADV()       (W32(v7 + 0x28, P32(v7 + 0x28) + 1), W32(v7 + 0x30, 0), W32(v7 + 0x2c, 0))
#define CLRX()      (W32(v7 + 0x30, 0), W32(v7 + 0x2c, 0))
#define REC(i)      CALL(0x3e9260, P32(v27 + 0x28), (i))

static int32_t ensure_named(const Dw4LoadIntf2Api *api, int32_t frame, int32_t name)
{
    int32_t reg = frame + 0x28, u;
    if (CALL(0x3e93b0, reg) == 0) {          /* dead: the caller returns if reg is null */
        u = CALL(0x301000, frame);
        u = CALL(0x3e9370, 0x587110, u);
        CALL(0x3e9360, LI2_TMP(0), u);
        CALL(0x3e9330, LI2_TMP(1), LI2_TMP(0));
        CALL(0x3e92b0, reg, LI2_TMP(1));
        CALL(0x33e9c0, LI2_TMP(1), -1);
    }
    u = CALL(0x3e92a0, reg);
    return CALL(0x3e9280, u, TBL, name);
}

void dw4_loadintf2_update(int32_t self, int32_t frame, const Dw4LoadIntf2Api *api)
{
    int32_t v7, v8, v9, v10, v11, v12, v13, v14, v16, v18, v19, v20, v21;
    int32_t v15, v26, v27, v28, v30, v23, c, lv, pp;
    int32_t b1, b2, b3, b4, b5;
    int32_t s1a0, s1f4 = 0, s1f8 = 0, s1fc = 0, s8 = 0, s10 = 0, s14 = 0;

    v16 = frame;
    if (P32(v16 + 0x28) == 0)
        return;

    v27 = ENSURE(LI2_COMMONINTF);
    v7  = ENSURE(LI2_CTRL);
    v8  = ENSURE(LI2_MAKECHR);
    v19 = ENSURE(LI2_COMMDLCTRL);
    v20 = ENSURE(LI2_MESWIN);
    v21 = ENSURE(LI2_SELSLOT);
    v9  = ENSURE(LI2_NAMESEL);
    v10 = ENSURE(LI2_TEXTORDER);
    v11 = ENSURE(LI2_DEGISTATECTRL);
    v12 = ENSURE(LI2_DATASELINTF);
    v13 = ENSURE(LI2_DIFFSELECT);
    v18 = v27;                     /* uVar18 holds COMMONINTF into the dispatch */
    CALL(0x3e44f0, v19);
    CALL(0x3ec450, v20);

    s1a0 = 0; b5 = 0; b1 = 0; b2 = 0; b3 = 0;
    v14 = REC(P32(v16 + 8));
    v28 = self;
    if (P8(v14 + 0x0f) == 1) {
        v14 = CALL(0x39b810, P32(v28 + 0x24), P32(v16 + 8));
        s1a0 = P32(v14 + 0x48);
        v26 = P32(v14 + 0x4c);
        v15 = P32(v14 + 0x1c) | P32(v14 + 0x20);
        b5 = 1;
        if (((v15 & 1) == 0) && (((s1a0 | v26) & 0x10) == 0))
            b5 = 0;
        b1 = ((v15 & 4) != 0) || (((s1a0 | v26) & 0x40) != 0);
        b2 = ((v15 & 8) != 0) || (((s1a0 | v26) & 0x80) != 0);
        b3 = ((v15 & 2) != 0) || (((s1a0 | v26) & 0x20) != 0);
    }
    if (P8(v7 + 0x16) != 0)
        return;
    v14 = REC(P32(v16 + 8));
    v30 = v21;
    switch (P32(v14 + 0x24)) {
    case 1:
        b4 = 0;
        v14 = REC(P32(v16 + 8));
        if (P32(v14 + 0x28) == 1) {
            v14 = REC(P32(v16 + 8));
            v23 = P32(v14 + 8) - 1;
            W32(v14 + 8, v23);
            if (v23 < 1) {
                v14 = REC(P32(v16 + 8));
                W32(v14 + 8, 0);
                b4 = 1;
            }
        } else if (P32(v14 + 0x28) == 0) {
            if (P32(v7 + 0x24) == 2) {
                /* Retail resets the *per-player record* (v0 from FUN_003e9240),
                 * not CTRL: 0x3e4e9c/acu/a0 write +0x24/+0x30/+0x2c and the
                 * delay slot at 0x3e4eac writes +0x28.  CTRL's state is left at
                 * 2, so the case-0 dispatch below re-enters state 2. */
                v14 = CALL(0x3e9240, P32(v27 + 0x28), P32(v16 + 8));
                W32(v14 + 0x24, 0); W32(v14 + 0x30, 0); W32(v14 + 0x2c, 0);
                W32(v14 + 0x28, 0);
            } else {
                CALL(0x3ecba0, v20, (P32(v16 + 8) << 0x10) | 0x51c);
                v14 = CALL(0x3e9240, P32(v27 + 0x28), P32(v16 + 8));
                W32(v14 + 0x28, 1); W32(v14 + 0x30, 0); W32(v14 + 0x2c, 0);
            }
        }
        if (b4)
            return;
        /* fall through */
    case 0:
        v14 = v19;
        switch (P32(v7 + 0x24)) {
        case 0:
            v8 = P32(v7 + 0x28);
            if (v8 == 4) {
                c = cm_open_empty(api, v19);
                if (c == 1) {
                    /* Retail 0x3e51c8 writes the byte before SET_ST(8). */
                    W8(v7 + 0x1d, 0);
                    SET_ST(8);
                }
            } else if (v8 == 3) {
                CALL(0x3e9220, LI2_TMP(0x32), v14 + 0x1c);
                CALL(0x3e3e00, v19, P32(v16 + 8), LI2_T_JCHRSELMESS, LI2_T_SQOPEN, LI2_TMP(0x32), 1);
                CALL(0x3eca70, v20);
                v16 = REC(P32(v16 + 8));
                W8(v16 + 0x0c, 1);
                ADV();
            } else if (v8 == 2) {
                CALL(0x38e5d0, P32(v28 + 0x14), LI2_T_GAMERAM);
                CALL(0x38f250, P32(v28 + 0x14), P32(v16 + 8));
                CALL(0x38e060, P32(v28 + 0x14), LI2_T_GETPLAYER);
                v18 = CALL(0x38f800, P32(v28 + 0x14), 0);
                v8 = CALL(0x3a9280, v18, 0x517350);
                if (P8(v8 + 0x0c) == 1) {
                    v19 = CALL(0x3e9260, P32(v27 + 0x24), P32(v16 + 8));
                    CALL(0x3ee6d0, v19, v18);
                    ADV();
                } else {
                    if (P32(v16 + 8) == 0) {
                        SET_ST(3);
                    } else {
                        v18 = CALL(0x236f80, P32(v28 + 0x0c), P32(0x588518));
                        v16 = CALL(0x39b810, v18, P32(v16 + 8));
                        if (P8(v16 + 8) == 0)
                            SET_ST(1);
                        else
                            SET_ST(2);
                    }
                    W8(v7 + 0x1d, 1);
                }
            } else if (v8 == 1) {
                c = cm_open_empty(api, v19);
                if (c == 1)
                    ADV();
            } else if (v8 == 0) {
                CALL(0x3e9220, LI2_TMP(0x2e), v14 + 0x1c);
                CALL(0x3e3e00, v19, P32(v16 + 8), LI2_T_JCHRSELBASE, LI2_T_SQOPEN, LI2_TMP(0x2e), 1);
                ADV();
            }
            break;
        case 1:
            v8 = REC(P32(v16 + 8));
            if (P8(v8 + 0x0f) == 1) {
                v18 = CALL(0x236f80, P32(v28 + 0x0c), P32(0x588518));
                v16 = CALL(0x39b810, v18, P32(v16 + 8));
                if (P8(v16 + 8) != 0)
                    SET_ST(2);
            }
            break;
        case 2:
            v8 = P32(v7 + 0x28);
            if (v8 == 3) {
                c = cm_close_empty(api, v19);
                if (c == 1) {
                    if (P8(v7 + 0x12) == 1)
                        SET_ST(3);
                    else
                        SET_ST(1);
                }
            } else if (v8 == 2) {
                v8 = REC(P32(v16 + 8));
                b1 = 1;
                if (P8(v8 + 0x0f) == 1) {
                    v18 = CALL(0x236f80, P32(v28 + 0x0c), P32(0x588518));
                    v8 = CALL(0x39b810, v18, P32(v16 + 8));
                    if (P8(v8 + 8) == 0) {
                        b1 = 1;
                    } else {
                        b1 = 0;
                        if ((s1a0 & 0x4000) != 0) {
                            v8 = REC(P32(v16 + 8));
                            b1 = 1;
                            W8(v8 + 0x0c, 1);
                            W8(v7 + 0x12, 1);
                        }
                    }
                }
                if (b1) {
                    if (P8(v7 + 0x12) == 1)
                        CALL(0x3e42a0, v19, P32(v16 + 8), LI2_T_JLINEWIN01, 0x516d40, 1);
                    else
                        CALL(0x3e42a0, v19, P32(v16 + 8), LI2_T_JLINEWIN01, LI2_T_SQCLOSE, 1);
                    to_pub(api, v10, (P32(v16 + 8) << 0x10) | 0x400);
                    ADV();
                }
            } else if (v8 == 1) {
                c = cm_open_empty(api, v19);
                if (c == 1) {
                    to_set(api, v10, (P32(v16 + 8) << 0x10) | 0x400, 0);
                    ADV();
                }
            } else if (v8 == 0) {
                CALL(0x3e9220, LI2_TMP(0x2d), v14 + 0x1c);
                CALL(0x3e3e00, v19, P32(v16 + 8), LI2_T_JLINEWIN01, LI2_T_SQOPEN, LI2_TMP(0x2d), 1);
                ADV();
            }
            break;
        case 3:
            v8 = P32(v7 + 0x28);
            if (v8 == 4) {
                c = cm_close_empty(api, v19);
                if (c == 1) {
                    v16 = REC(P32(v16 + 8));
                    W8(v16 + 0x0c, 0);
                    W8(v7 + 0x12, 0);
                    SET_ST(2);
                    W8(v7 + 0x15, 0);
                }
            } else if (v8 == 3) {
                c = cm_open_empty(api, v19);
                if (c == 1) {
                    to_pub(api, v10, (P32(v16 + 8) << 0x10) | 0x401);
                    if (P32(v7 + 0x18) == 0)
                        SET_ST(4);
                    else
                        SET_ST(6);
                }
            } else if (v8 == 2) {
                if (P32(v7 + 0x2c) == 1) {
                    c = cm_open_empty(api, v19);
                    if (c == 1) {
                        W32(v7 + 0x2c, 0);
                        W32(v7 + 0x30, 0);
                    }
                } else if (P32(v7 + 0x2c) == 0) {
                    if (b5) {
                        v8 = P32(v7 + 0x18) - 1;
                        if (v8 < 0) {
                            v8 = 0;
                        } else {
                            CALL(0x3e4030, v19, P32(v16 + 8), 0x516eb0, 0x516ed0, 1);
                        }
                        W32(v7 + 0x18, v8);
                        W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                        W32(v7 + 0x30, 0);
                    } else if (b1) {
                        v8 = P32(v7 + 0x18) + 1;
                        if (v8 < 2)
                            CALL(0x3e4030, v19, P32(v16 + 8), 0x516eb0, 0x516ef0, 1);
                        else
                            v8 = 1;
                        W32(v7 + 0x18, v8);
                        W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                        W32(v7 + 0x30, 0);
                    } else if ((s1a0 & 0x4000) == 0) {
                        if (((s1a0 & 0x2000) != 0) && (P32(v16 + 8) != 0)) {
                            CALL(0x3e42a0, v19, P32(v16 + 8), 0x516eb0, 0x516d50, 1);
                            CALL(0x3e42a0, v19, P32(v16 + 8), LI2_T_JCHRSELMESS, LI2_T_SQCLOSE, 1);
                            to_pub(api, v10, (P32(v16 + 8) << 0x10) | 0x401);
                            CALL(0x3ecaa0, v20);
                            W32(v7 + 0x28, P32(v7 + 0x28) + 2);
                            W32(v7 + 0x30, 0);
                            W32(v7 + 0x2c, 0);
                        }
                    } else {
                        if (P32(v7 + 0x18) == 0)
                            CALL(0x3e4030, v19, P32(v16 + 8), 0x516eb0, 0x516d40, 1);
                        else
                            CALL(0x3e4030, v19, P32(v16 + 8), 0x516eb0, 0x516e18, 1);
                        ADV();
                    }
                }
            } else if (v8 == 1) {
                if (P32(v7 + 0x2c) == 0) {
                    c = CALL(0x3e4210, v19, P32(v16 + 8), 0x516eb0, LI2_T_SQOPEN);
                    if (c == 0) {
                        to_set(api, v10, (P32(v16 + 8) << 0x10) | 0x401, 0);
                        W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                        W32(v7 + 0x30, 0);
                        if (P32(v16 + 8) == 0)
                            CALL(0x3ecad0, v20, 0x523);
                        else
                            CALL(0x3ecad0, v20, (P32(v16 + 8) << 0x10) | 0x524);
                    }
                }
                c = cm_open_empty(api, v19);
                if (c == 1)
                    ADV();
            } else if (v8 == 0) {
                if (P8(v7 + 0x15) == 0) {
                    CALL(0x3e9220, LI2_TMP(0x33), v14 + 0x1c);
                    CALL(0x3e3e00, v19, P32(v16 + 8), LI2_T_JCHRSELMESS, LI2_T_SQOPEN, LI2_TMP(0x33), 1);
                    CALL(0x3eca70, v20);
                    W8(v7 + 0x15, 1);
                }
                v8 = REC(P32(v16 + 8));
                W8(v8 + 0x0c, 1);
                CALL(0x3e9220, LI2_TMP(0x34), v14 + 0x1c);
                CALL(0x3e3e00, v19, P32(v16 + 8), 0x516eb0, LI2_T_SQOPEN, LI2_TMP(0x34), 1);
                W32(v7 + 0x18, 0);
                ADV();
            }
            break;
        case 4:
            switch (P32(v7 + 0x28)) {
            case 0:
                CALL(0x3e9220, LI2_TMP(0x35), v14 + 0x1c);
                CALL(0x3e3e00, v19, P32(v16 + 8), 0x517380, LI2_T_SQOPEN, LI2_TMP(0x35), 1);
                CALL(0x3e9220, LI2_TMP(0x36), v14 + 0x1c);
                CALL(0x3e3e00, v19, P32(v16 + 8), 0x5173a0, LI2_T_SQOPEN, LI2_TMP(0x36), 1);
                CALL(0x3e9220, LI2_TMP(0x37), v14 + 0x1c);
                CALL(0x3e3e00, v19, P32(v16 + 8), 0x5173b8, LI2_T_SQOPEN, LI2_TMP(0x37), 1);
                W32(v8 + 0x30, 3);
                CALL(0x3ecad0, v20, (P32(v16 + 8) << 0x10) | 0x511);
                CALL(0x38e5f0, P32(v28 + 0x14), 0x516c50, 0x516c60, 0, 0x516c68);
                v18 = CALL(0x38f800, P32(v28 + 0x14), 0);
                v9 = 0;
                pp = 0x4cec70;
                do {
                    lv = CALL(0x12a4a4, P32(pp), P32(0x4cd0e0 + P32(v8 + 0x30) * 4));
                    v11 = v9;
                    if (lv == 0)
                        break;
                    v9 = v9 + 1;
                    pp = pp + 12;
                    v11 = s1f4;
                } while (v9 < 0x10);
                s1f4 = v11;
                v18 = CALL(0x3a9580, v18, s1f4, 0x516c78);
                to_configure_font(api, v10, 0x5173c8, P32(v16 + 8), 0, v18, 1, 0);
                CALL(0x3e9220, LI2_TMP(0x38), v14 + 0x1c);
                CALL(0x3e3e00, v19, P32(v16 + 8), 0x516ca8,
                     P32(0x4cec74 + P32(v8 + 0x30) * 12), LI2_TMP(0x38), 1);
                CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL,
                     P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8), LI2_T_GENERATE);
                CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL,
                     P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8), LI2_T_ISRUN);
                lv = CALL(0x38f0f0, P32(v28 + 0x14));
                c = 0;
                if (lv > 0)
                    c = CALL(0x38f220, P32(v28 + 0x14), 0);
                if (c == 1) {
                    CALL(0x1ae1a0, LI2_TMP(0x1e));
                    CALL(0x1ae1a0, LI2_TMP(0x22));
                    CALL(0x38d860, P32(v28 + 0x14), LI2_T_MODELCTRL,
                         P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8));
                    CALL(0x3e9220, LI2_TMP(0x39), LI2_TMP(0x1e));
                    CALL(0x38f4b0, P32(v28 + 0x14), LI2_TMP(0x39));
                    CALL(0x3e9220, LI2_TMP(0x3a), LI2_TMP(0x22));
                    CALL(0x38f4b0, P32(v28 + 0x14), LI2_TMP(0x3a));
                    CALL(0x38e060, P32(v28 + 0x14), 0x5173d8);
                    CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL,
                         P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8), 0x5173e8);
                    W8(v7 + 0x17, 0);
                } else {
                    W8(v7 + 0x17, 1);
                }
                ADV();
                W8(v7 + 0x14, 0);
                break;
            case 1:
                c = cm_open_empty(api, v19);
                if (c == 1) {
                    CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL, 0x5173b8,
                         P32(v16 + 8), 0x516dd8);
                    ADV();
                }
                break;
            case 2:
                if (P32(v7 + 0x2c) == 1) {
                    c = cm_open_empty(api, v19);
                    if (c == 1) {
                        W32(v7 + 0x2c, 0);
                        W32(v7 + 0x30, 0);
                    }
                } else if (P32(v7 + 0x2c) == 0) {
                    if (b3) {
                        if (P8(v7 + 0x17) == 0) {
                            CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL,
                                 P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8), LI2_T_ISRUN);
                            c = CALL(0x38f220, P32(v28 + 0x14), 0);
                            if (c == 1)
                                CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL,
                                     P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8), 0x5173f0);
                        }
                        v9 = P32(v8 + 0x30) + 1;
                        if (v9 > 3)
                            v9 = 0;
                        W32(v8 + 0x30, v9);
                        CALL(0x38e5f0, P32(v28 + 0x14), 0x516c50, 0x516c60, 0, 0x516c68);
                        v18 = CALL(0x38f800, P32(v28 + 0x14), 0);
                        v9 = 0;
                        pp = 0x4cec70;
                        do {
                            lv = CALL(0x12a4a4, P32(pp), P32(0x4cd0e0 + P32(v8 + 0x30) * 4));
                            v11 = v9;
                            if (lv == 0)
                                break;
                            v9 = v9 + 1;
                            pp = pp + 12;
                            v11 = s1f8;
                        } while (v9 < 0x10);
                        s1f8 = v11;
                        v18 = CALL(0x3a9580, v18, s1f8, 0x516c78);
                        to_configure_font(api, v10, 0x5173c8, P32(v16 + 8), 0, v18, 1, 0);
                        CALL(0x3e4030, v19, P32(v16 + 8), 0x5173a0, 0x517028, 1);
                        CALL(0x3e4030, v19, P32(v16 + 8), 0x5173b8, 0x5173f8, 0);
                        CALL(0x3e4030, v19, P32(v16 + 8), 0x516ca8,
                             P32(0x4cec78 + P32(v8 + 0x30) * 12), 0);
                        W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                        W32(v7 + 0x30, 0);
                    } else if (b2) {
                        if (P8(v7 + 0x17) == 0) {
                            CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL,
                                 P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8), LI2_T_ISRUN);
                            c = CALL(0x38f220, P32(v28 + 0x14), 0);
                            if (c == 1)
                                CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL,
                                     P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8), 0x5173f0);
                        }
                        v9 = P32(v8 + 0x30) - 1;
                        if (v9 < 0)
                            v9 = 3;
                        W32(v8 + 0x30, v9);
                        CALL(0x38e5f0, P32(v28 + 0x14), 0x516c50, 0x516c60, 0, 0x516c68);
                        v18 = CALL(0x38f800, P32(v28 + 0x14), 0);
                        v9 = 0;
                        pp = 0x4cec70;
                        do {
                            lv = CALL(0x12a4a4, P32(pp), P32(0x4cd0e0 + P32(v8 + 0x30) * 4));
                            v11 = v9;
                            if (lv == 0)
                                break;
                            v9 = v9 + 1;
                            pp = pp + 12;
                            v11 = s1fc;
                        } while (v9 < 0x10);
                        s1fc = v11;
                        v18 = CALL(0x3a9580, v18, s1fc, 0x516c78);
                        to_configure_font(api, v10, 0x5173c8, P32(v16 + 8), 0, v18, 1, 0);
                        CALL(0x3e4030, v19, P32(v16 + 8), 0x517380, 0x517028, 1);
                        CALL(0x3e4030, v19, P32(v16 + 8), 0x5173b8, 0x5173f8, 0);
                        CALL(0x3e4030, v19, P32(v16 + 8), 0x516ca8,
                             P32(0x4cec78 + P32(v8 + 0x30) * 12), 0);
                        W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                        W32(v7 + 0x30, 0);
                    } else {
                        CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL,
                             P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8), LI2_T_ISRUN);
                        lv = CALL(0x38f0f0, P32(v28 + 0x14));
                        if (lv < 1) {
                            c = 0;
                            if (P8(v7 + 0x17) == 1)
                                c = 1;
                        } else {
                            c = CALL(0x38f220, P32(v28 + 0x14), 0);
                        }
                        if (c == 1) {
                            if ((s1a0 & 0x4000) == 0) {
                                if ((s1a0 & 0x2000) != 0) {
                                    W8(v7 + 0x14, 1);
                                    ADV();
                                }
                            } else {
                                ADV();
                            }
                        } else {
                            CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL,
                                 P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8), LI2_T_GENERATE);
                            CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL,
                                 P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8), LI2_T_ISRUN);
                            lv = CALL(0x38f0f0, P32(v28 + 0x14));
                            c = 0;
                            if (lv > 0)
                                c = CALL(0x38f220, P32(v28 + 0x14), 0);
                            if (c == 1) {
                                CALL(0x1ae1a0, LI2_TMP(0x23));
                                CALL(0x1ae1a0, LI2_TMP(0x27));
                                CALL(0x38d860, P32(v28 + 0x14), LI2_T_MODELCTRL,
                                     P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8));
                                CALL(0x3e9220, LI2_TMP(0x3b), LI2_TMP(0x23));
                                CALL(0x38f4b0, P32(v28 + 0x14), LI2_TMP(0x3b));
                                CALL(0x3e9220, LI2_TMP(0x3c), LI2_TMP(0x27));
                                CALL(0x38f4b0, P32(v28 + 0x14), LI2_TMP(0x3c));
                                CALL(0x38e060, P32(v28 + 0x14), 0x5173d8);
                                CALL(0x38e5f0, P32(v28 + 0x14), LI2_T_MODELCTRL,
                                     P32(0x4cd0d0 + P32(v8 + 0x30) * 4), P32(v16 + 8), 0x5173e8);
                                W8(v7 + 0x17, 0);
                            } else {
                                W8(v7 + 0x17, 1);
                            }
                        }
                    }
                }
                break;
            case 3:
                if (P8(v7 + 0x14) == 0)
                    CALL(0x3e42a0, v19, P32(v16 + 8), 0x5173b8, 0x516d40, 1);
                else
                    CALL(0x3e42a0, v19, P32(v16 + 8), 0x5173b8, LI2_T_SQCANCEL, 1);
                if (P8(v7 + 0x17) == 0)
                    CALL(0x3e42a0, v19, P32(v16 + 8),
                         P32(0x4cd0d0 + P32(v8 + 0x30) * 4), 0x5173f0, 1);
                to_clear_font(api, v10, 0x5173c8, P32(v16 + 8), 0);
                ADV();
                break;
            case 4:
                c = cm_close_empty(api, v19);
                if (c == 1)
                    ADV();
                break;
            case 5:
                CALL(0x3e42a0, v19, P32(v16 + 8), 0x516ca8, LI2_T_SQCLOSE, 1);
                CALL(0x3e42a0, v19, P32(v16 + 8), 0x517380, LI2_T_SQCLOSE, 1);
                CALL(0x3e42a0, v19, P32(v16 + 8), 0x5173a0, LI2_T_SQCLOSE, 1);
                ADV();
                break;
            case 6:
                c = cm_close_empty(api, v19);
                if (c == 1) {
                    if (P8(v7 + 0x14) == 1) {
                        SET_ST(3);
                    } else {
                        SET_ST(5);
                        CALL(0x3de260, v9, 1);
                    }
                }
                break;
            }
            break;
        case 5:
            switch (P32(v7 + 0x28)) {
            default:
                W32(v9 + 0x24, P32(v8 + 0x30));
                ADV();
                CALL(0x3ecad0, v20, (P32(v16 + 8) << 0x10) | 0x517);
                break;
            case 1:
                v16 = REC(P32(v16 + 8));
                lv = CALL(0x3def80, v9, P8(v16 + 0x0f));
                if (lv == 0) {
                    if (P8(v9 + 0x4e) == 1)
                        ADV();
                } else if (P8(v9 + 0x4d) == 1) {
                    W8(v7 + 0x1c, 1);
                    SET_ST(8);
                } else {
                    SET_ST(4);
                }
                break;
            case 2:
                CALL(0x3ecb00, v20, (P32(v16 + 8) << 0x10) | 0x519);
                ADV();
                break;
            case 3:
                c = CALL(0x3ecb70, v20);
                if (c == 0)
                    ADV();
                break;
            case 4:
                CALL(0x3ecae0, v20, (P32(v16 + 8) << 0x10) | 0x51b, 0);
                ADV();
                break;
            case 5:
                c = CALL(0x3ecb70, v20);
                if (c == 0) {
                    lv = CALL(0x3ecb80, v20);
                    if (lv == 1) {
                        CALL(0x3ecad0, v20, (P32(v16 + 8) << 0x10) | 0x517);
                        CALL(0x3def70, v9, 0);
                    } else if (lv == 0) {
                        CALL(0x3def70, v9);
                    }
                    SET_SUB(1);
                }
                break;
            }
            break;
        case 6:
            v8 = P32(v7 + 0x28);
            if (v8 == 2) {
                if (P32(v7 + 0x2c) == 1) {
                    c = ss_marks(api, v21);
                    if (c == 1) {
                        if (P8(v30 + 0x37) == 1)
                            SET_ST(6);
                        else if (P8(v30 + 0x36) == 1)
                            SET_ST(3);
                        else
                            SET_ST(7);
                        CALL(0x3ecb90, v20);
                    }
                } else if (P32(v7 + 0x2c) == 0) {
                    W32(v30 + 0x4c, 2);
                    W32(v30 + 0x58, 0);
                    W32(v30 + 0x54, 0);
                    W32(v30 + 0x50, 0);
                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                    W32(v7 + 0x30, 0);
                }
            } else if (v8 == 1) {
                if (P32(v7 + 0x2c) == 1) {
                    if (P32(v7 + 0x30) == 1) {
                        v8 = REC(P32(v16 + 8));
                        v8 = P32(v8 + 0x14);
                        if (v8 == 4) {
                            v8 = P32(v27 + 0x38);
                            v26 = 0xffffffff;
                            if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3009;
                            else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2009;
                            else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1009;
                            CALL(0x3ecad0, v20, v26);
                            ss_pub_cursor(api, v21, 0);
                            SET_SUB(1);
                        } else if ((v8 == 2) || (v8 == 1)) {
                            v8 = P32(v27 + 0x38);
                            v26 = 0xffffffff;
                            if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3009;
                            else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2009;
                            else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1009;
                            CALL(0x3ecad0, v20, v26);
                            ss_pub_cursor(api, v21, 0);
                            SET_SUB(1);
                        } else if (v8 == 0) {
                            ADV();
                        }
                    } else if (P32(v7 + 0x30) == 0) {
                        v8 = P32(v27 + 0x38);
                        v26 = 0xffffffff;
                        if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3004;
                        else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2004;
                        else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1004;
                        CALL(0x3ecad0, v20, v26);
                        CALL(0x3ee250, v18, P32(v16 + 8), 5);
                        W32(v7 + 0x30, P32(v7 + 0x30) + 1);
                    }
                } else if (P32(v7 + 0x2c) == 0) {
                    v16 = REC(P32(v16 + 8));
                    c = ss_update(api, v21, P8(v16 + 0x0f), 1);
                    if (c == 1) {
                        if (P8(v30 + 0x37) == 1)
                            ADV();
                        else if (P8(v30 + 0x36) == 1)
                            ADV();
                        else {
                            W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                            W32(v7 + 0x30, 0);
                        }
                    }
                }
            } else if (v8 == 0) {
                if (P32(v7 + 0x2c) == 1) {
                    c = ss_open(api, v21, -1);
                    if (c == 1) {
                        W32(v30 + 0x4c, 1);
                        W32(v30 + 0x58, 0);
                        W32(v30 + 0x54, 0);
                        W32(v30 + 0x50, 0);
                        ADV();
                    }
                } else if (P32(v7 + 0x2c) == 0) {
                    CALL(0x3ee320, v18, P32(v16 + 8));
                    ss_init(api, v21);
                    W32(v30 + 0x4c, 0);
                    W32(v30 + 0x58, 0);
                    W32(v30 + 0x54, 0);
                    W32(v30 + 0x50, 0);
                    v8 = P32(v27 + 0x38);
                    v26 = 0xffffffff;
                    if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3009;
                    else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2009;
                    else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1009;
                    CALL(0x3ecad0, v20, v26);
                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                    W32(v7 + 0x30, 0);
                }
            }
            break;
        case 7:
            v8 = P32(v7 + 0x28);
            if (v8 == 100) {
                if (P32(v7 + 0x2c) == 1) {
                    c = CALL(0x3dbf90, v12, 0);
                    if (c == 1) {
                        v18 = CALL(0x301000, self);
                        if (P8(0x554c14) == 0)
                            v18 = CALL(0x2f88e0, P32(0x587110));
                        s14 = CALL(0x3c6830, v18);
                        CALL(0x3e9160, P32(v27 + 0x24), P32(v16 + 8), s14);
                        CALL(0x3e9110, s14);
                        SET_ST(6);
                    }
                } else if (P32(v7 + 0x2c) == 0) {
                    CALL(0x3daff0, v12, 0);
                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                    W32(v7 + 0x30, 0);
                }
            } else if (v8 == 2) {
                if (P8(v12 + 0x49) == 1) {
                    SET_ST(6);
                } else {
                    W8(v7 + 0x1c, 0);
                    SET_ST(8);
                }
            } else if (v8 == 1) {
                v8 = P32(v7 + 0x2c);
                if (v8 == 4) {
                    c = CALL(0x3dbf90, v12, 0);
                    if (c == 1) {
                        if (P32(v7 + 0x30) == 1) {
                            SET_SUB(100);
                        } else if (P32(v7 + 0x30) == 0) {
                            ADV();
                        }
                    }
                } else if (v8 == 3) {
                    v16 = REC(P32(v16 + 8));
                    if (P8(v16 + 0x10) == 1) {
                        CALL(0x3daff0, v12, 0);
                        W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                        W32(v7 + 0x30, 0);
                        W32(v7 + 0x30, 1);
                    } else {
                        c = CALL(0x3db780, v12, 0);
                        if (c == 1) {
                            CALL(0x3daff0, v12, 0);
                            W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                            W32(v7 + 0x30, 0);
                            W32(v7 + 0x30, 0);
                        }
                    }
                } else if (v8 == 2) {
                    CALL(0x3daff0, v12, 0);
                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                    W32(v7 + 0x30, 0);
                } else if (v8 == 1) {
                    c = CALL(0x3db060, v12, 0);
                    if (c == 1) {
                        W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                        W32(v7 + 0x30, 0);
                    }
                } else if (v8 == 0) {
                    CALL(0x3daff0, v12, 0);
                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                    W32(v7 + 0x30, 0);
                }
            } else if (v8 == 0) {
                CALL(0x3dafb0, v12, P32(v16 + 8), 0);
                ADV();
            }
            break;
        case 8:
            v14 = P32(v7 + 0x28);
            if (v14 == 3) {
                v8 = P32(v7 + 0x2c);
                if (v8 != 3) {
                    if (v8 == 1) {
                        if (((s1a0 & 0x2000) == 0) || (P8(v7 + 0x1d) != 1)) {
                            v10 = P32(v27 + 0x28);
                            v9 = 0; v8 = 0; v16 = 0;
                            lv = CALL(0x2294f0, v10);
                            if (lv > 0) {
                                do {
                                    v18 = CALL(0x3e9240, v10, v16);
                                    c = CALL(0x3e90c0, v18);
                                    if (c == 1) v9 = v9 + 1;
                                    v18 = CALL(0x3e9240, v10, v16);
                                    c = CALL(0x3e90b0, v18);
                                    if (c == 1) v8 = v8 + 1;
                                    v16 = v16 + 1;
                                    v11 = CALL(0x2294f0, v10);
                                } while (v16 < v11);
                            }
                            if (v9 == v8) {
                                if ((s1a0 & 8) != 0) {
                                    v16 = 0;
                                    W32(v27 + 0x30, 3);
                                    v10 = P32(v27 + 0x28);
                                    lv = CALL(0x2294f0, v10);
                                    if (lv > 0) {
                                        do {
                                            v18 = CALL(0x3e9240, v10, v16);
                                            CALL(0x3e90a0, v18, 0);
                                            v16 = v16 + 1;
                                            v8 = CALL(0x2294f0, v10);
                                        } while (v16 < v8);
                                    }
                                    W8(P32(v27 + 0x14) + 99, 0);
                                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                                    W32(v7 + 0x30, 0);
                                }
                            } else {
                                SET_SUB(1);
                            }
                        } else {
                            v16 = REC(P32(v16 + 8));
                            W8(v16 + 0x0d, 0);
                            SET_SUB(2);
                        }
                    } else if (v8 == 0) {
                        if (P8(v7 + 0x1d) == 1)
                            CALL(0x3ecad0, v20, (P32(v16 + 8) << 0x10) | 0x51d);
                        else
                            CALL(0x3ecad0, v20, (P32(v16 + 8) << 0x10) | 0x521);
                        W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                        W32(v7 + 0x30, 0);
                    }
                }
            } else if (v14 == 2) {
                v8 = P32(v7 + 0x2c);
                if (v8 == 3) {
                    v18 = CALL(0x3e9260, P32(v11 + 0x10), 0);
                    c = CALL(0x3da7c0, v18);
                    if (c == 1) {
                        if (P8(v7 + 0x1c) == 1) {
                            SET_ST(5);
                            CALL(0x3de260, v9, 0);
                        } else {
                            v18 = CALL(0x301000, self);
                            if (P8(0x554c14) == 0)
                                v18 = CALL(0x2f88e0, P32(0x587110));
                            s14 = CALL(0x3c6830, v18);
                            CALL(0x3e9160, P32(v27 + 0x24), P32(v16 + 8), s14);
                            CALL(0x3e9110, s14);
                            SET_ST(6);
                        }
                    }
                } else if (v8 == 2) {
                    v18 = CALL(0x3e9260, P32(v11 + 0x10), 0);
                    CALL(0x3d9e70, v18, 0);
                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                    W32(v7 + 0x30, 0);
                } else if (v8 == 1) {
                    c = cm_open_empty(api, v19);
                    if (c == 1) {
                        W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                        W32(v7 + 0x30, 0);
                    }
                } else if (v8 == 0) {
                    CALL(0x3e4030, v19, P32(v16 + 8), 0x516cc0, LI2_T_SQCANCEL, 1);
                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                    W32(v7 + 0x30, 0);
                }
            } else if (v14 == 1) {
                if (P32(v7 + 0x2c) == 1) {
                    if (P32(v7 + 0x30) == 1) {
                        v10 = P32(v27 + 0x28);
                        v9 = 0; v11 = 0; v8 = 0;
                        lv = CALL(0x2294f0, v10);
                        if (lv > 0) {
                            do {
                                v18 = CALL(0x3e9240, v10, v8);
                                c = CALL(0x3e90c0, v18);
                                if (c == 1) v9 = v9 + 1;
                                v18 = CALL(0x3e9240, v10, v8);
                                c = CALL(0x3e90b0, v18);
                                if (c == 1) v11 = v11 + 1;
                                v8 = v8 + 1;
                                v12 = CALL(0x2294f0, v10);
                            } while (v8 < v12);
                        }
                        if (v9 == v11) {
                            if (((s1a0 & 0x2000) != 0) && (P8(v7 + 0x1d) == 1)) {
                                v16 = REC(P32(v16 + 8));
                                W8(v16 + 0x0d, 0);
                                ADV();
                            }
                        }
                    } else if (P32(v7 + 0x30) == 0) {
                        if (P32(v16 + 8) == 0) {
                            v10 = P32(v27 + 0x28);
                            v11 = 0; v9 = 0; v8 = 0;
                            lv = CALL(0x2294f0, v10);
                            if (lv > 0) {
                                do {
                                    v18 = CALL(0x3e9240, v10, v8);
                                    c = CALL(0x3e90c0, v18);
                                    if (c == 1) v11 = v11 + 1;
                                    v18 = CALL(0x3e9240, v10, v8);
                                    c = CALL(0x3e90b0, v18);
                                    if (c == 1) v9 = v9 + 1;
                                    v8 = v8 + 1;
                                    v12 = CALL(0x2294f0, v10);
                                } while (v8 < v12);
                            }
                            if (v11 == v9) {
                                SET_SUB(3);
                            } else if (((s1a0 & 0x2000) != 0) && (P8(v7 + 0x1d) == 1)) {
                                v16 = REC(P32(v16 + 8));
                                W8(v16 + 0x0d, 0);
                                ADV();
                            }
                        } else {
                            v10 = P32(v27 + 0x28);
                            v9 = 0; v11 = 0; v8 = 0;
                            lv = CALL(0x2294f0, v10);
                            if (lv > 0) {
                                do {
                                    v18 = CALL(0x3e9240, v10, v8);
                                    c = CALL(0x3e90c0, v18);
                                    if (c == 1) v9 = v9 + 1;
                                    v18 = CALL(0x3e9240, v10, v8);
                                    c = CALL(0x3e90b0, v18);
                                    if (c == 1) v11 = v11 + 1;
                                    v8 = v8 + 1;
                                    v12 = CALL(0x2294f0, v10);
                                } while (v8 < v12);
                            }
                            if (v9 == v11) {
                                if (P8(v7 + 0x1d) == 1)
                                    CALL(0x3ecad0, v20, (P32(v16 + 8) << 0x10) | 0x51f);
                                else
                                    CALL(0x3ecad0, v20, (P32(v16 + 8) << 0x10) | 0x522);
                                W32(v7 + 0x30, P32(v7 + 0x30) + 1);
                            } else if (((s1a0 & 0x2000) != 0) && (P8(v7 + 0x1d) == 1)) {
                                v16 = REC(P32(v16 + 8));
                                W8(v16 + 0x0d, 0);
                                ADV();
                            }
                        }
                    }
                } else if (P32(v7 + 0x2c) == 0) {
                    if (P8(v7 + 0x1d) == 1)
                        CALL(0x3ecad0, v20, (P32(v16 + 8) << 0x10) | 0x530);
                    else
                        CALL(0x3ecad0, v20, (P32(v16 + 8) << 0x10) | 0x52f);
                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                    W32(v7 + 0x30, 0);
                }
            } else if (v14 == 0) {
                if (P32(v7 + 0x2c) == 1) {
                    v18 = CALL(0x3e9260, P32(v11 + 0x10), 0);
                    c = CALL(0x3da7c0, v18);
                    if (c == 1) {
                        v8 = REC(P32(v16 + 8));
                        W8(v8 + 0x0d, 1);
                        if (P32(v16 + 8) == 0) {
                            v10 = P32(v27 + 0x28);
                            v9 = 0; v16 = 0; v8 = 0;
                            lv = CALL(0x2294f0, v10);
                            if (lv > 0) {
                                do {
                                    v18 = CALL(0x3e9240, v10, v16);
                                    c = CALL(0x3e90c0, v18);
                                    if (c == 1) v9 = v9 + 1;
                                    v18 = CALL(0x3e9240, v10, v16);
                                    c = CALL(0x3e90b0, v18);
                                    if (c == 1) v8 = v8 + 1;
                                    v16 = v16 + 1;
                                    v11 = CALL(0x2294f0, v10);
                                } while (v16 < v11);
                            }
                            if (v9 == v8)
                                SET_SUB(3);
                            else
                                SET_SUB(1);
                        } else {
                            SET_SUB(1);
                        }
                    }
                } else if (P32(v7 + 0x2c) == 0) {
                    if (P32(v7 + 0x30) == 1) {
                        v8 = REC(P32(v16 + 8));
                        c = CALL(0x3ddb80, v13, P8(v8 + 0x0f));
                        if (c == 1) {
                            if (P8(v13 + 0x25) == 1) {
                                v18 = CALL(0x301000, self);
                                if (P8(0x554c14) == 0)
                                    v18 = CALL(0x2f88e0, P32(0x587110));
                                s10 = CALL(0x3c6830, v18);
                                CALL(0x3e9160, P32(v27 + 0x24), P32(v16 + 8), s10);
                                CALL(0x3e9110, s10);
                                v16 = REC(P32(v16 + 8));
                                W8(v16 + 0x0d, 0);
                                SET_ST(6);
                            } else {
                                W32(v27 + 0x3c, P32(v13 + 0x10));
                                v10 = P32(v16 + 8);
                                v18 = CALL(0x3e9260, P32(v11 + 0x10), 0);
                                CALL(0x3d9e10, v18, 1, v10);
                                W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                                W32(v7 + 0x30, 0);
                            }
                        }
                    } else if (P32(v7 + 0x30) == 0) {
                        if (P8(v7 + 0x1d) == 1) {
                            if (P8(v7 + 0x1c) == 1) {
                                CALL(0x38e5d0, P32(v28 + 0x14), LI2_T_GAMERAM);
                                CALL(0x38f250, P32(v28 + 0x14), P32(v16 + 8));
                                CALL(0x38e060, P32(v28 + 0x14), LI2_T_GAMEDATAINIT);
                                v18 = CALL(0x301000, self);
                                if (P8(0x554c14) == 0)
                                    v18 = CALL(0x2f88e0, P32(0x587108));
                                s8 = CALL(0x3614f0, v18);
                                CALL(0x3843c0, s8, 8);
                                v9 = 0;
                                {
                                    int32_t sp = P32(s8 + 0x0c);
                                    int32_t dp = sp;
                                    do {
                                        W16(dp, P16(v9 + 0xec));
                                        if (P16(v9 + 0xec) == 0) break;
                                        v9 = v9 + 1;
                                        v12 = v9;
                                        dp = dp + 2;
                                    } while (v12 < 8);
                                    sp = sp + 2 * v9;
                                    for (; v9 < 8; v9 = v9 + 1) {
                                        W16(sp, 0);
                                        sp = sp + 2;
                                    }
                                }
                                CALL(0x38e5d0, P32(v28 + 0x14), LI2_T_GAMERAM);
                                CALL(0x38f250, P32(v28 + 0x14), P32(v16 + 8));
                                CALL(0x38f830, P32(v28 + 0x14), P32(0x4cec70 + P32(v8 + 0x30) * 12));
                                CALL(0x38f670, P32(v28 + 0x14), s8);
                                CALL(0x38e060, P32(v28 + 0x14), LI2_T_GAMESTART);
                                CALL(0x3e9110, s8);
                                CALL(0x38e5d0, P32(v28 + 0x14), LI2_T_GAMERAM);
                                CALL(0x38f250, P32(v28 + 0x14), P32(v16 + 8));
                                CALL(0x38e060, P32(v28 + 0x14), LI2_T_GETPLAYER);
                                v18 = CALL(0x38f800, P32(v28 + 0x14), 0);
                                v19 = P32(P32(v28 + 0x0c) + 0x50);
                                v8 = CALL(0x3a9220, v18, 0x517428);
                                W32(v8 + 0x0c, v19);
                                v19 = CALL(0x3e9260, P32(v27 + 0x24), P32(v16 + 8));
                                CALL(0x3ee6d0, v19, v18);
                            } else {
                                CALL(0x38e5d0, P32(v28 + 0x14), LI2_T_GAMERAM);
                                CALL(0x38f250, P32(v28 + 0x14), P32(v16 + 8));
                                CALL(0x38e060, P32(v28 + 0x14), LI2_T_GAMEDATAINIT);
                                v10 = P32(v12 + 0x14);
                                v8 = CALL(0x3e9240, P32(v27 + 0x28), P32(v16 + 8));
                                s8 = CALL(0x3e90f0, P32(P32(v8 + 0x20) + 0x0c), v10);
                                CALL(0x3e90d0, s8);
                                CALL(0x3e9160, P32(v27 + 0x24), P32(v16 + 8), s8);
                                CALL(0x3ee320, v18, P32(v16 + 8));
                                CALL(0x3e9110, s8);
                                CALL(0x38e5d0, P32(v28 + 0x14), LI2_T_GAMERAM);
                                CALL(0x38f250, P32(v28 + 0x14), P32(v16 + 8));
                                CALL(0x38e060, P32(v28 + 0x14), LI2_T_GETPLAYER);
                                v18 = CALL(0x38f800, P32(v28 + 0x14), 0);
                                v19 = CALL(0x236f80, P32(v28 + 0x0c), P32(0x589678));
                                v20 = CALL(0x3e9260, P32(v27 + 0x24), P32(v16 + 8));
                                CALL(0x3ef5d0, v20, v18, v19);
                                v8 = CALL(0x3e9260, P32(v27 + 0x24), P32(v16 + 8));
                                v10 = P32(v8 + 0x30);
                                CALL(0x38e5d0, P32(v28 + 0x14), LI2_T_GAMERAM);
                                CALL(0x38f250, P32(v28 + 0x14), P32(v16 + 8));
                                CALL(0x38f830, P32(v28 + 0x14), v10);
                                CALL(0x38e060, P32(v28 + 0x14), 0x517430);
                                CALL(0x38e5d0, P32(v28 + 0x14), LI2_T_GAMERAM);
                                CALL(0x38f250, P32(v28 + 0x14), P32(v16 + 8));
                                CALL(0x38e060, P32(v28 + 0x14), 0x517440);
                            }
                        }
                        v14 = 0; v12 = 0; v8 = v12; v9 = v14;
                        if ((P32(v16 + 8) == 0) && (P8(v7 + 0x1d) == 1)) {
                            W32(v27 + 0x3c, 0);
                            W32(v28 + 0x2c, 0);
                            W32(0x58a1e0, 0);
                            v18 = CALL(0x236f80, P32(v28 + 0x0c), P32(0x589208));
                            CALL(0x389ff0, v18, LI2_T_HOSTLOAD, 0);
                            if (P32(v28 + 0x2c) == 2) { v8 = 2; v9 = 1; }
                            else { v8 = 1; v9 = 1; if (P32(v28 + 0x2c) != 1) { v8 = 0; v9 = 0; } }
                        }
                        if (v9 == 0) {
                            v10 = P32(v16 + 8);
                            v18 = CALL(0x3e9260, P32(v11 + 0x10), 0);
                            CALL(0x3d9e10, v18, 1, v10);
                            W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                            W32(v7 + 0x30, 0);
                        } else {
                            if (v8 == 2)
                                CALL(0x3ddb10, v13, 1, P32(v16 + 8));
                            else if (v8 == 1)
                                CALL(0x3ddb10, v13, 0, P32(v16 + 8));
                            W32(v7 + 0x30, P32(v7 + 0x30) + 1);
                        }
                    }
                }
            }
            break;
        }
        break;
    case 2:
        v8 = REC(P32(v16 + 8));
        v8 = P32(v8 + 0x28);
        if (v8 != 3) {
            if (v8 == 2) {
                v18 = CALL(0x3e9260, P32(v11 + 0x10), 0);
                c = CALL(0x3da7c0, v18);
                if (c == 1) {
                    c = cm_close_empty(api, v19);
                    if (c == 1) {
                        v7 = REC(P32(v16 + 8));
                        W8(v7 + 0x0e, 1);
                        v16 = CALL(0x3e9240, P32(v27 + 0x28), P32(v16 + 8));
                        W32(v16 + 0x28, 3);
                        W32(v16 + 0x30, 0);
                        W32(v16 + 0x2c, 0);
                    }
                }
            } else if (v8 == 1) {
                c = cm_close_empty(api, v19);
                if (c == 1) {
                    v7 = REC(P32(v16 + 8));
                    W8(v7 + 0x0e, 1);
                    v16 = CALL(0x3e9240, P32(v27 + 0x28), P32(v16 + 8));
                    W32(v16 + 0x28, 3);
                    W32(v16 + 0x30, 0);
                    W32(v16 + 0x2c, 0);
                }
            } else if (v8 == 0) {
                if (P32(v7 + 0x24) == 8) {
                    CALL(0x3e42a0, v19, P32(v16 + 8), LI2_T_JCHRSELMESS, LI2_T_SQCLOSE, 1);
                    CALL(0x3ecaa0, v20);
                    v18 = CALL(0x3e9260, P32(v11 + 0x10), 0);
                    CALL(0x3d9e90, v18);
                    v7 = CALL(0x3e9240, P32(v27 + 0x28), P32(v16 + 8));
                    W32(v7 + 0x28, 2); W32(v7 + 0x30, 0); W32(v7 + 0x2c, 0);
                } else if (P32(v7 + 0x24) == 2) {
                    v7 = CALL(0x3e9240, P32(v27 + 0x28), P32(v16 + 8));
                    W32(v7 + 0x28, 1); W32(v7 + 0x30, 0); W32(v7 + 0x2c, 0);
                } else {
                    v7 = CALL(0x3e9240, P32(v27 + 0x28), P32(v16 + 8));
                    W32(v7 + 0x28, 1); W32(v7 + 0x30, 0); W32(v7 + 0x2c, 0);
                }
                CALL(0x3e42a0, v19, P32(v16 + 8), LI2_T_JCHRSELBASE, LI2_T_SQCLOSE, 1);
            }
        }
        break;
    case 5:
        if (P8(P32(v27 + 0x34) + 0x0c) == 1) {
            v7 = REC(P32(v16 + 8));
            switch (P32(v7 + 0x28)) {
            case 0:
                lv = CALL(0x3ed050, v18, P32(v16 + 8), v20, P32(v30 + 0x40), 3);
                if (lv == 2) {
                    v16 = P32(P32(v27 + 0x34) + 0x20);
                    if ((v16 != 3) && (v16 != 4)) {
                        if (v16 == 0x0c) { SET_ST(6); return; }
                        if (v16 == 7) {
                            if (P32(v27 + 0x38) == 1) { SET_SUB(3); return; }
                            SET_ST(6); return;
                        }
                        if (v16 == 2) { SET_SUB(5); return; }
                    }
                    SET_ST(6);
                } else if (lv == 1) {
                    SET_SUB(5);
                }
                break;
            case 1:
                v8 = CALL(0x3e9260, P32(P32(v27 + 0x34) + 0x2c), P32(v30 + 0x40));
                if (P8(v8 + 8) == 1) {
                    v8 = P32(v27 + 0x38);
                    v26 = 0xffffffff;
                    if (v8 == 2) { v15 = P32(v16 + 8) << 0x10; v26 = v15 | 0x3002; v15 = v15 | 0x3000; }
                    else if (v8 == 1) { v15 = P32(v16 + 8) << 0x10; v26 = v15 | 0x2002; v15 = v15 | 0x2000; }
                    else { v15 = v26; if (v8 == 0) { v15 = P32(v16 + 8) << 0x10; v26 = v15 | 0x1002; v15 = v15 | 0x1000; } }
                    lv = CALL(0x3ecdc0, v18, P32(v16 + 8), v20, v15, v26, 0, 3);
                    if (lv == 2) {
                        SET_ST(7);
                        W32(v7 + 0x14, 1);
                    } else if (lv == 1) {
                        SET_SUB(2);
                    }
                } else {
                    CALL(0x3ecb20, v20);
                    SET_ST(7);
                    W32(v7 + 0x14, 2);
                }
                break;
            case 2:
                if (P32(v7 + 0x2c) == 1) {
                    lv = CALL(0x3ed2e0, v18, P32(v16 + 8), v20, P32(v30 + 0x40), 3);
                    if (lv == 2) {
                        switch (P32(P32(v27 + 0x34) + 0x20)) {
                        default:
                            SET_ST(6); W32(v7 + 0x14, 1); break;
                        case 7:
                            SET_SUB(3); break;
                        case 9:
                        case 10:
                            SET_ST(6); W32(v7 + 0x14, 1);
                        }
                    } else if (lv == 1) {
                        SET_SUB(5);
                    }
                    if (lv != 0) {
                        if (P8(v27 + 0x40) == 0)
                            W8(P32(v28 + 0x20) + 99, 1);
                        W8(P32(v28 + 0x20) + 0x5f, 1);
                    }
                } else if (P32(v7 + 0x2c) == 0) {
                    if (P8(v27 + 0x40) == 0)
                        W8(P32(v28 + 0x20) + 99, 0);
                    W8(P32(v28 + 0x20) + 0x5f, 0);
                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                    W32(v7 + 0x30, 0);
                }
                break;
            case 3:
                v8 = CALL(0x3e9260, P32(P32(v27 + 0x34) + 0x2c), P32(v30 + 0x40));
                if (P8(v8 + 8) == 1) {
                    v8 = P32(v27 + 0x38);
                    v26 = 0xffffffff;
                    if (v8 == 2) { v15 = P32(v16 + 8) << 0x10; v26 = v15 | 0x3007; v15 = v15 | 0x3005; }
                    else if (v8 == 1) { v15 = P32(v16 + 8) << 0x10; v26 = v15 | 0x2007; v15 = v15 | 0x2005; }
                    else { v15 = v26; if (v8 == 0) { v15 = P32(v16 + 8) << 0x10; v26 = v15 | 0x1007; v15 = v15 | 0x1005; } }
                    lv = CALL(0x3ecdc0, v18, P32(v16 + 8), v20, v15, v26, 1, 3);
                    if (lv == 2) { SET_ST(7); W32(v7 + 0x14, 1); }
                    else if (lv == 1) { SET_SUB(4); }
                } else {
                    CALL(0x3ecb20, v20);
                    SET_ST(7);
                    W32(v7 + 0x14, 2);
                }
                break;
            case 4:
                if (P32(v7 + 0x2c) == 1) {
                    lv = CALL(0x3edf60, v18, P32(v16 + 8), v20, P32(v30 + 0x40), 3);
                    if (lv == 2) {
                        switch (P32(P32(v27 + 0x34) + 0x20)) {
                        default:
                            W32(v7 + 0x14, 2); SET_ST(6); break;
                        case 4:
                            SET_ST(6); W32(v7 + 0x14, 2);
                        }
                    } else if (lv == 1) {
                        W32(v7 + 0x14, 4); SET_ST(7);
                    }
                    if (lv != 0) {
                        if (P8(v27 + 0x40) == 0)
                            W8(P32(v28 + 0x20) + 99, 1);
                        W8(P32(v28 + 0x20) + 0x5f, 1);
                    }
                } else if (P32(v7 + 0x2c) == 0) {
                    v8 = P32(v27 + 0x38);
                    v26 = 0xffffffff;
                    if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3008;
                    else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2008;
                    else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1008;
                    CALL(0x3ecad0, v20, v26);
                    if (P8(v27 + 0x40) == 0)
                        W8(P32(v28 + 0x20) + 99, 0);
                    W8(P32(v28 + 0x20) + 0x5f, 0);
                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                    W32(v7 + 0x30, 0);
                }
                break;
            case 5:
                lv = 0; v8 = 0;
                if (P32(P32(v27 + 0x20) + 8) > 0) {
                    do {
                        v9 = CALL(0x3e9260, P32(v27 + 0x20), v8);
                        if (P32(v9 + 8) == P32(v30 + 0x40)) {
                            lv = CALL(0x3e9260, P32(v27 + 0x20), v8);
                            break;
                        }
                        v8 = v8 + 1;
                    } while (v8 < P32(P32(v27 + 0x20) + 8));
                }
                if (lv == 0) {
                    if (P8(P32(v27 + 0x34) + 0x0c) != 0)
                        ADV();
                } else {
                    v8 = P32(lv + 0x10);
                    v9 = P32(v8 + 8);
                    v10 = P32(v16 + 8);
                    if (v9 < P32(v8 + 0x0c))
                        W32(v8 + 8, P32(v8 + 8) + 1);
                    else
                        CALL(0x2d6790, v8, v9 + 1, 4);
                    v16 = CALL(0x3e9090, v8);
                    W32(v16 + v9 * 4, v10);
                    W32(v7 + 0x20, lv);
                    SET_ST(7);
                    W32(v7 + 0x14, 0);
                }
                break;
            case 6:
                if (P32(v7 + 0x2c) == 1) {
                    lv = CALL(0x3ed650, v18, P32(v16 + 8), v20, P32(v30 + 0x40), 3);
                    if (lv == 2) {
                        switch (P32(P32(v27 + 0x34) + 0x20)) {
                        default:
                            SET_ST(6); W32(v7 + 0x14, 1); break;
                        case 7:
                            SET_SUB(3); break;
                        case 9:
                        case 10:
                            SET_ST(6); W32(v7 + 0x14, 1);
                        }
                    } else if (lv == 1) {
                        SET_ST(7);
                        W32(v7 + 0x14, 0);
                    }
                } else if (P32(v7 + 0x2c) == 0) {
                    W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                    W32(v7 + 0x30, 0);
                }
                break;
            }
        }
        break;
    case 6:
        v7 = REC(P32(v16 + 8));
        if (P32(v27 + 0x38) == 2)
            ss_update(api, v21, 0, 0);
        if (P32(v7 + 0x28) == 0) {
            if (P32(v7 + 0x2c) == 1) {
                c = CALL(0x3ecb70, v20);
                if (c == 0) {
                    W32(v7 + 0x14, 1); SET_ST(7);
                }
            } else if (P32(v7 + 0x2c) == 0) {
                v8 = P32(v27 + 0x34);
                if (P8(v8 + 0x10) == 1) {
                    if (P32(v8 + 0x20) == 0x0c)
                        ss_select(api, v21, P32(v30 + 0x40));
                    else
                        ss_select(api, v21, -1);
                    v8 = P32(v27 + 0x38);
                    v26 = 0xffffffff;
                    if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x300e;
                    else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x200e;
                    else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x100e;
                    CALL(0x3ecb00, v20, v26);
                } else {
                    v8 = CALL(0x3e9260, P32(v8 + 0x2c), P32(v30 + 0x40));
                    if (P8(v8 + 8) == 1) {
                        v8 = P32(P32(v27 + 0x34) + 0x20);
                        if (P32(v27 + 0x38) != 2) {
                            if (v8 == 0x0c)
                                ss_select(api, v21, P32(v30 + 0x40));
                            else
                                ss_select(api, v21, -1);
                        }
                        switch (v8) {
                        default:
                            v8 = P32(v27 + 0x38); v26 = 0xffffffff;
                            if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x300d;
                            else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x200d;
                            else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x100d;
                            CALL(0x3ecb00, v20, v26);
                            break;
                        case 4:
                            v8 = P32(v27 + 0x38); v26 = 0xffffffff;
                            if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3028;
                            else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2028;
                            else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1028;
                            CALL(0x3ecb00, v20, v26);
                            break;
                        case 5:
                            v8 = P32(v27 + 0x38); v26 = 0xffffffff;
                            if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3010;
                            else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2010;
                            else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1010;
                            CALL(0x3ecb00, v20, v26);
                            break;
                        case 6:
                            v8 = P32(v27 + 0x38); v26 = 0xffffffff;
                            if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3011;
                            else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2011;
                            else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1011;
                            CALL(0x3ecb00, v20, v26);
                            break;
                        case 7:
                            v8 = P32(v27 + 0x38); v26 = 0xffffffff;
                            if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3012;
                            else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2012;
                            else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1028;
                            CALL(0x3ecb00, v20, v26);
                            break;
                        case 8:
                            v8 = P32(v27 + 0x38); v26 = 0xffffffff;
                            if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3013;
                            else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2013;
                            else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1013;
                            CALL(0x3ecb00, v20, v26);
                            break;
                        case 9:
                            v8 = P32(v27 + 0x38); v26 = 0xffffffff;
                            if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3014;
                            else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2014;
                            else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1014;
                            CALL(0x3ecb00, v20, v26);
                            break;
                        case 10:
                            v8 = P32(v27 + 0x38); v26 = 0xffffffff;
                            if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3015;
                            else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2015;
                            else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1015;
                            CALL(0x3ecb00, v20, v26);
                            break;
                        case 0x0c:
                            v8 = P32(v27 + 0x38); v26 = 0xffffffff;
                            if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3016;
                            else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2016;
                            else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1016;
                            CALL(0x3ecb00, v20, v26);
                        }
                    } else {
                        if (P32(v27 + 0x38) != 2)
                            ss_select(api, v21, P32(v30 + 0x40));
                        v8 = P32(v27 + 0x38); v26 = 0xffffffff;
                        if (v8 == 2) v26 = (P32(v16 + 8) << 0x10) | 0x3016;
                        else if (v8 == 1) v26 = (P32(v16 + 8) << 0x10) | 0x2016;
                        else if (v8 == 0) v26 = (P32(v16 + 8) << 0x10) | 0x1016;
                        CALL(0x3ecb00, v20, v26);
                    }
                }
                W32(v7 + 0x2c, P32(v7 + 0x2c) + 1);
                W32(v7 + 0x30, 0);
            }
        }
        break;
    case 7:
        v16 = 0;
        do {
            v7 = CALL(0x3e9240, P32(v27 + 0x28), v16);
            v16 = v16 + 1;
            W32(v7 + 0x24, 8);
            W32(v7 + 0x30, 0);
            W32(v7 + 0x2c, 0);
            W32(v7 + 0x28, 0);
        } while (v16 < 4);
        break;
    case 8:
        CALL(0x3ecbc0, v20);
        v7 = CALL(0x3e9240, P32(v27 + 0x28), P32(v16 + 8));
        W32(v7 + 0x24, 0);
        W32(v7 + 0x30, 0);
        W32(v7 + 0x2c, 0);
        W32(v7 + 0x28, 0);
        v16 = REC(P32(v16 + 8));
        W8(v16 + 0x0f, 1);
        break;
    }
}

/* 0x003e9430 — RUN/… message handler.  `info` is the Info whose +0x14 is the
 * message data list.  Returns 1 (handled) or 0 (unknown command). */
int32_t dw4_loadintf2_message(int32_t self, int32_t frame, int32_t info,
                              const Dw4LoadIntf2Api *api)
{
    int32_t messenger = P32(self + 0x14);
    int32_t cls = CALL(0x3c46a0);
    int32_t cmd = CALL(0x38d4a0, messenger, cls, P32(info + 0x14));
    int32_t ret = 0;

    if (cmd == 0) {
        if (P32(frame + 0x28) == 0) {
            int32_t ins, ctrl, o, ct, kind;
            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            ctrl = CALL(0x36ae80, ins);
            addref(api, ctrl);
            release(api, P32(frame + 0x28));
            W32(frame + 0x28, ctrl);
            W32(self + 0x20, CALL(0x236f80, P32(self + 0x0c), P32(SYS_NODE)));

            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            o = CALL(0x3c43c0, ins);
            CALL(0x301e30, P32(frame + 0x28), o);
            W8(o + 0x10, 1);                     /* _isRun */
            if (P32(frame + 8) == 0) {
                W8(o + 0x11, 0);                 /* _isRdy   */
                W8(o + 0x12, 1);                 /* _isEntry */
                W8(o + 0x13, 1);                 /* _isCtrl  */
            } else {
                W8(o + 0x11, 0);
                W8(o + 0x12, 0);
                W8(o + 0x13, 1);
            }
            release(api, o);

            CALL(0x38e5f0, messenger, LI2_LOADCTRL2, 0, 0, LI2_GETCOMMON);
            CALL(0x301e30, P32(frame + 0x28), CALL(0x38f800, messenger, 0));

            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            o = CALL(0x3c40c0, ins);
            CALL(0x301e30, P32(frame + 0x28), o);
            release(api, o);

            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            o = CALL(0x3c6ea0, ins);
            CALL(0x301e30, P32(frame + 0x28), o);
            W32(o + 0x10, messenger);
            kind = P32(frame + 8) * 0x0c;
            W32(o + 0x1c, P32(0x4cd0a0 + kind));
            W32(o + 0x20, P32(0x4cd0a4 + kind));
            W32(o + 0x24, P32(0x4cd0a8 + kind));
            release(api, o);

            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            o = CALL(0x3c76c0, ins);
            W32(o + 0x10, messenger);
            W32(o + 0x14, CALL(0x236f80, P32(self + 0x0c), P32(SYS_NODE3)));
            CALL(0x301e30, P32(frame + 0x28), o);
            release(api, o);

            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            o = CALL(0x3c2e60, ins);
            W32(o + 0x30, P32(frame + 8));
            W32(o + 0x10, messenger);
            W32(o + 0x14, CALL(0x236f80, P32(self + 0x0c), P32(SYS_NODE2)));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);    /* note: unreachable here */
            W32(o + 0x18, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMDLCTRL));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x1c, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_TEXTORDER));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x20, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMONINTF));
            CALL(0x301e30, P32(frame + 0x28), o);
            release(api, o);

            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            o = CALL(0x3c27c0, ins);
            W32(o + 0x20, P32(frame + 8));
            W32(o + 0x10, messenger);
            W32(o + 0x14, CALL(0x236f80, P32(self + 0x0c), P32(SYS_NODE2)));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            ct = CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMDLCTRL);
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x18, ct);
            W32(o + 0x1c, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_TEXTORDER));
            CALL(0x301e30, P32(frame + 0x28), o);
            release(api, o);

            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            o = CALL(0x3c6b00, ins);
            W32(o + 0x2c, P32(frame + 8));
            W32(o + 0x10, messenger);
            W32(o + 0x14, CALL(0x236f80, P32(self + 0x0c), P32(SYS_NODE2)));
            CALL(0x301e30, P32(frame + 0x28), o);
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x18, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_TEXTORDER));
            release(api, o);

            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            o = CALL(0x3c3900, ins);
            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            ct = CALL(0x3c3e40, ins);
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            {
                int32_t a = CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMONINTF);
                int32_t b, c;
                if (P32(frame + 0x28) == 0)
                    ensure_work_null(api, frame);
                b = CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_TEXTORDER);
                if (P32(frame + 0x28) == 0)
                    ensure_work_null(api, frame);
                c = CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMDLCTRL);
                CALL(0x3d9de0, ct, P32(frame + 8), a, b, c, messenger, 0);
            }
            CALL(0x301e30, P32(o + 0x10), ct);
            release(api, ct);

            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            ct = CALL(0x3c3e40, ins);
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            {
                int32_t a = CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMONINTF);
                int32_t b, c;
                if (P32(frame + 0x28) == 0)
                    ensure_work_null(api, frame);
                b = CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_TEXTORDER);
                if (P32(frame + 0x28) == 0)
                    ensure_work_null(api, frame);
                c = CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMDLCTRL);
                CALL(0x3d9de0, ct, P32(frame + 8), a, b, c, messenger, 1);
            }
            CALL(0x301e30, P32(o + 0x10), ct);
            release(api, ct);
            CALL(0x301e30, P32(frame + 0x28), o);
            release(api, o);

            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            o = CALL(0x3c3560, ins);
            W32(o + 0x18, CALL(0x236f80, P32(self + 0x0c), P32(SYS_NODE2)));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x1c, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMDLCTRL));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x20, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_TEXTORDER));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x24, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMONINTF));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x28, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_MESWIN));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x2c, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_DEGISTATECTRL));
            CALL(0x301e30, P32(frame + 0x28), o);
            release(api, o);

            ins = CALL(0x301000, self);
            if (P8(LI2_GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(SYSTEM_REF));
            o = CALL(0x3c31e0, ins);
            W32(o + 0x28, CALL(0x236f80, P32(self + 0x0c), P32(SYS_NODE2)));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x2c, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMDLCTRL));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x30, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_TEXTORDER));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x34, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMONINTF));
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            W32(o + 0x38, CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_MESWIN));
            CALL(0x301e30, P32(frame + 0x28), o);
            release(api, o);

            release(api, ctrl);
        }
        ret = 1;
    } else if (P32(frame + 0x28) == 0) {
        ret = 1;
    } else {
        int32_t ctrl, chr;
        if (P32(frame + 0x28) == 0)
            ensure_work_null(api, frame);
        ctrl = CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_CTRL);
        if (P32(frame + 0x28) == 0)
            ensure_work_null(api, frame);
        chr = CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_MAKECHR);
        (void)chr;
        switch (cmd) {
        case 2:
            if (CALL(0x38f240, messenger) == 0)
                CALL(0x38f250, messenger, 0);
            if (P8(ctrl + 0x12) == 1)
                CALL(0x38f2e0, messenger, 0, CALL(0x38f320, messenger, 0) + 1);
            ret = 1;
            break;
        case 3:
            if (CALL(0x38f240, messenger) == 0)
                CALL(0x38f250, messenger, 0);
            if (P8(ctrl + 0x11) == 1)
                CALL(0x38f2e0, messenger, 0, CALL(0x38f320, messenger, 0) + 1);
            ret = 1;
            break;
        case 4:
            W8(ctrl + 0x13, 1);
            ret = 1;
            break;
        case 5:
            W8(ctrl + 0x13, 0);
            ret = 1;
            break;
        case 6:
            if (P32(frame + 0x28) == 0)
                ensure_work_null(api, frame);
            {
                int32_t ci = CALL(0x3022c0, P32(frame + 0x28), TBL, LI2_COMMONINTF);
                int32_t e = P32(P32(P32(ci + 0x28) + 0x10) + P32(frame + 8) * 4);
                if (P8(e + 0x0d) != 1) {
                    CALL(0x38e5d0, messenger, LI2_MSG_517338);
                    CALL(0x38f250, messenger, P32(frame + 8));
                    CALL(0x38e060, messenger, LI2_GAMEREMOVE);
                }
            }
            ret = 1;
            break;
        case 7:
            if (CALL(0x38f240, messenger) == 0)
                CALL(0x38f250, messenger, 0);
            W32(self + 0x2c, CALL(0x38f320, messenger, 0));   /* _difficultMax */
            ret = 1;
            break;
        default:
            ret = 0;
            break;
        }
    }
    return ret;
}
