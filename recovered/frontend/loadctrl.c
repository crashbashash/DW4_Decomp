/* recovered/frontend/loadctrl.c — behavioral reconstruction of the Game Start
 * load controller, Gap::Bec::beNDMWLoadCtrl2:
 *
 *   0x003f1a80  vfunc_31  the per-frame update           (2512 bytes)
 *   0x003f2490  vfunc_34  the RUN/GAMESTART message handler (1820 bytes)
 *
 * NOT a matching decompilation and not in src/. A port-facing behavioral
 * reference, checked by scripts/verify_loadctrl.py, which runs the original MIPS
 * instructions of both functions through a restricted R5900 interpreter and
 * compares the ordered engine calls and the object writes.  Every engine call is
 * routed through api->call() with its own retail address so the two call streams
 * compare call-for-call; engine-owned reads/writes go through peek/poke.
 *
 * The "frame" second argument is the per-frame context; only +0x28 (the named
 * work registry) and, in the handler, its use as the created work's store are
 * exercised here.  Its C++ owner is not pinned (see loadctrl.h).
 */
#include "loadctrl.h"

#define P32(a)     api->peek(api->user, (a), 4)
#define P8(a)      api->peek(api->user, (a), 1)
#define W32(a, v)  api->poke(api->user, (a), 4, (v))
#define W8(a, v)   api->poke(api->user, (a), 1, (v))
/* Missing argument registers are zero-padded by the C99 compound literal. */
#define CALL(addr, ...) api->call(api->user, (addr), (const int32_t[5]){__VA_ARGS__})

/* gp-relative lazy-init flag read by the FUN_00301000 insight guard. */
#define GP_FLAG    0x554c14

/* Decrement the +4 reference count of `obj`; release at zero. Mirrors retail's
 * "addiu -1; sw; lw; (x<<0x29)>>0x29" idiom. */
static void release(const Dw4LoadApi *api, int32_t obj)
{
    int32_t r;
    if (obj == 0)
        return;
    r = P32(obj + 4) - 1;
    W32(obj + 4, r);
    if ((r & 0x7fffff) == 0)
        CALL(0x2ff820, obj);
}

/* 0x003f1a80 — per-frame update. Retail returns immediately when the work
 * registry is null; the two recompute blocks at 0x3f1ab4 and 0x3f1b98 are
 * unreachable for the same reason and are not reproduced. */
void dw4_loadctrl_update(int32_t self, int32_t frame, const Dw4LoadApi *api)
{
    int32_t messenger = P32(self + 0x14);
    int32_t ctrl, intf, st0, st1, st2, i, off, n;

    if (P32(frame + 0x28) == 0)
        return;

    ctrl = CALL(0x3022c0, P32(frame + 0x28), DW4_LOAD_TBL, DW4_LOAD_CTRL);
    intf = CALL(0x3022c0, P32(frame + 0x28), DW4_LOAD_TBL, DW4_LOAD_COMMONINTF);

    st0 = P32(ctrl + 0x14);
    if (st0 == 3) {
        st1 = P32(ctrl + 0x18);
        if (st1 == 1) {
            if (CALL(0x3f13d0, P32(intf + 0x34)) == 1) {
                if (P8(ctrl + 0x10) == 0) {
                    CALL(0x38d860, messenger, 0x518230, 0, -1);
                    CALL(0x38f250, messenger, 4);
                    CALL(0x38e060, messenger, 0x518240);
                } else {
                    int32_t obj;
                    W32(0x58a1e0, 0);
                    obj = CALL(0x236f80, P32(self + 0xc), P32(0x589208));
                    CALL(0x389ff0, obj, 0x518250, 0);
                    CALL(0x38d860, messenger, 0x518230, 0, -1);
                    CALL(0x38f250, messenger, 0);
                    CALL(0x38e060, messenger, 0x518240);
                }
                CALL(0x38e5d0, messenger, 0x518260);
                CALL(0x38f830, messenger, 0x518270);
                CALL(0x38e060, messenger, 0x518280);
                W32(ctrl + 0x14, P32(ctrl + 0x14) + 1);
                W32(ctrl + 0x20, 0);
                W32(ctrl + 0x1c, 0);
                W32(ctrl + 0x18, 0);
            }
        } else if (st1 == 0) {
            CALL(0x3f1380, P32(intf + 0x34));
            W32(ctrl + 0x18, P32(ctrl + 0x18) + 1);
            W32(ctrl + 0x20, 0);
            W32(ctrl + 0x1c, 0);
        }
        return;
    }

    if (st0 == 2) {
        st1 = P32(ctrl + 0x18);
        if (st1 == 4) {
            st2 = P32(ctrl + 0x1c);
            if (st2 == 4) {
                CALL(0x38e5f0, messenger, 0x518188, 0, -1, 0x5181b8);
                n = 0;
                off = 0;
                for (i = 0; i < 4; i++) {
                    if (P8(P32(P32(P32(intf + 0x28) + 0x10) + off) + 0xd) == 1)
                        n++;
                    off += 4;
                }
                CALL(0x38e670, messenger, 0x5181c8, 0x5181d0);
                {
                    int32_t gameram = CALL(0x38f800, messenger, 0);
                    W32(CALL(0x3a9220, gameram, 0x5181e0) + 0xc, n);
                    if (P8(ctrl + 0x10) == 1) {
                        W32(CALL(0x3a9220, gameram, 0x5181e8) + 0xc, P32(intf + 0x3c));
                        W32(CALL(0x3a9220, gameram, 0x5181f8) + 0xc, P32(self + 0x24));
                        W32(CALL(0x3a9220, gameram, 0x518208) + 0xc, P32(self + 0x28));
                        CALL(0x38e670, messenger, 0x518218, 0x518220);
                    }
                }
                W32(ctrl + 0x14, 3);
                W32(ctrl + 0x20, 0);
                W32(ctrl + 0x1c, 0);
                W32(ctrl + 0x18, 0);
            } else if (st2 == 3) {
                CALL(0x38e5f0, messenger, 0x517a48, 0x518148, 0, 0x518170);
                if (CALL(0x38f220, messenger, 0) == 0) {
                    W32(ctrl + 0x1c, P32(ctrl + 0x1c) + 1);
                    W32(ctrl + 0x20, 0);
                }
            } else if (st2 == 2) {
                CALL(0x38e5f0, messenger, 0x517a48, 0x518160, 0, 0x517fe0);
                CALL(0x38e5f0, messenger, 0x517a48, 0x518160, 0, 0x518198);
                CALL(0x38e5f0, messenger, 0x517a48, 0x518148, 0, 0x5181a8);
                W32(ctrl + 0x1c, P32(ctrl + 0x1c) + 1);
                W32(ctrl + 0x20, 0);
            } else if (st2 == 1) {
                int32_t all = 1;
                off = 0;
                for (i = 0; i < 4; i++) {
                    if (P8(P32(P32(P32(intf + 0x28) + 0x10) + off) + 0xe) != 1) {
                        all = 0;
                        break;
                    }
                    off += 4;
                }
                if (all) {
                    W32(ctrl + 0x1c, P32(ctrl + 0x1c) + 1);
                    W32(ctrl + 0x20, 0);
                }
            } else if (st2 == 0) {
                off = 0;
                for (i = 0; i < 4; i++) {
                    int32_t e = P32(P32(P32(intf + 0x28) + 0x10) + off);
                    W8(e + 0xe, 0);
                    W32(e + 0x24, 2);
                    W32(e + 0x30, 0);
                    W32(e + 0x2c, 0);
                    W32(e + 0x28, 0);
                    off += 4;
                }
                W32(ctrl + 0x1c, P32(ctrl + 0x1c) + 1);
                W32(ctrl + 0x20, 0);
            }
        } else if (st1 == 3) {
            int32_t s = P32(intf + 0x30);
            if (s == 3) {
                W32(ctrl + 0x18, P32(ctrl + 0x18) + 1);
                W32(ctrl + 0x20, 0);
                W32(ctrl + 0x1c, 0);
            } else if (s == 2) {
                /* no action */
            } else if (s == 0) {
                CALL(0x3ecc60, intf);
            }
        } else if (st1 == 2) {
            CALL(0x38e5f0, messenger, 0x518188, 0, -1, 0x517fe0);
            W32(ctrl + 0x18, P32(ctrl + 0x18) + 1);
            W32(ctrl + 0x20, 0);
            W32(ctrl + 0x1c, 0);
        } else if (st1 == 1) {
            st2 = P32(ctrl + 0x1c);
            if (st2 == 2) {
                CALL(0x38e5f0, messenger, 0x517a48, 0x518160, 0, 0x518170);
                if (CALL(0x38f220, messenger, 0) == 0) {
                    W32(ctrl + 0x18, P32(ctrl + 0x18) + 1);
                    W32(ctrl + 0x20, 0);
                    W32(ctrl + 0x1c, 0);
                }
            } else if (st2 == 1) {
                CALL(0x38e5f0, messenger, 0x517a48, 0x518160, 0, 0x518170);
                if (CALL(0x38f220, messenger, 0) == 1)
                    CALL(0x38e5f0, messenger, 0x517a48, 0x518160, 0, 0x518178);
                W32(ctrl + 0x1c, P32(ctrl + 0x1c) + 1);
                W32(ctrl + 0x20, 0);
            } else if (st2 == 0) {
                CALL(0x38d860, messenger, 0x517a48, 0x518148, 0, -1);
                CALL(0x38f830, messenger, 0x518158);
                CALL(0x38e060, messenger, 0x517af8);
                if (CALL(0x38f220, messenger, 0) == 0) {
                    if (P8(ctrl + 0x10) == 1) {
                        W32(ctrl + 0x1c, P32(ctrl + 0x1c) + 1);
                        W32(ctrl + 0x20, 0);
                    } else {
                        W32(ctrl + 0x18, P32(ctrl + 0x18) + 1);
                        W32(ctrl + 0x20, 0);
                        W32(ctrl + 0x1c, 0);
                    }
                }
            }
        } else if (st1 == 0) {
            CALL(0x38e5f0, messenger, 0x517a48, 0x518148, 0, 0x517fe0);
            CALL(0x38e5f0, messenger, 0x517a48, 0x518148, 0, 0x518158);
            W32(ctrl + 0x18, P32(ctrl + 0x18) + 1);
            W32(ctrl + 0x20, 0);
            W32(ctrl + 0x1c, 0);
        }
        return;
    }

    /* st0 == 1: the fade/entry substate. */
    if (st0 == 1) {
        st1 = P32(ctrl + 0x18);
        if (st1 == 1) {
            if (CALL(0x3f12f0, P32(intf + 0x34)) == 1) {
                W32(ctrl + 0x14, 2);
                W32(ctrl + 0x20, 0);
                W32(ctrl + 0x1c, 0);
                W32(ctrl + 0x18, 0);
            }
        } else if (st1 == 0) {
            CALL(0x3f1270, P32(intf + 0x34));
            W32(ctrl + 0x18, P32(ctrl + 0x18) + 1);
            W32(ctrl + 0x20, 0);
            W32(ctrl + 0x1c, 0);
        }
    }
    /* st0 == 0: nothing. */
}

/* 0x003f2490 — RUN/GAMESTART message handler. `info` is the Info whose +0x14 is
 * the message data list. Returns 1 (handled) or 0 (unknown command). */
int32_t dw4_loadctrl_message(int32_t self, int32_t frame, int32_t info, const Dw4LoadApi *api)
{
    int32_t messenger = P32(self + 0x14);
    int32_t cls = CALL(0x3c7d40);
    int32_t cmd = CALL(0x38d4a0, messenger, cls, P32(info + 0x14));
    int32_t ret = 0;

    if (cmd == 0 || cmd == 1) {
        if (cmd == 1) {
            if (CALL(0x38f240, messenger) < 1) {
                W32(self + 0x24, 0);
                W32(self + 0x28, 0);
            } else {
                W32(self + 0x24, CALL(0x38f320, messenger, 0));
                W32(self + 0x28, CALL(0x38f320, messenger, 1));
            }
        }
        if (P32(frame + 0x28) == 0) {
            int32_t ins, ctrl, i;
            ins = CALL(0x301000, self);
            if (P8(GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(0x587110));
            ctrl = CALL(0x36ae80, ins);
            if (ctrl != 0)
                W32(ctrl + 4, P32(ctrl + 4) + 1);
            release(api, P32(frame + 0x28));
            W32(frame + 0x28, ctrl);
            ins = CALL(0x301000, self);
            if (P8(GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(0x587110));
            {
                int32_t work = CALL(0x3c7a40, ins);
                CALL(0x301e30, P32(frame + 0x28), work);
                i = 1;
                W32(work + 0x14, 1);
                W32(work + 0x20, 0);
                W32(work + 0x1c, 0);
                W32(work + 0x18, 0);
                if (cmd == 1) {
                    i = 0;
                    W8(work + 0x10, 1);
                    do {
                        CALL(0x38e5d0, messenger, 0x5181c8);
                        CALL(0x38f250, messenger, i);
                        CALL(0x38e060, messenger, 0x5182a0);
                        i++;
                    } while (i < 4);
                } else {
                    do {
                        CALL(0x38e5d0, messenger, 0x5181c8);
                        CALL(0x38f250, messenger, i);
                        CALL(0x38e060, messenger, 0x5182b0);
                        if (P8(CALL(0x3a9280, CALL(0x38f800, messenger, 0), 0x517e58) + 0xc) != 1) {
                            CALL(0x38e5d0, messenger, 0x5181c8);
                            CALL(0x38f250, messenger, i);
                            CALL(0x38e060, messenger, 0x5182a0);
                        }
                        i++;
                    } while (i < 4);
                    W8(work + 0x10, 0);
                }
                release(api, work);
            }
            ins = CALL(0x301000, self);
            if (P8(GP_FLAG) == 0)
                ins = CALL(0x2f88e0, P32(0x587110));
            {
                int32_t cm = CALL(0x3c4be0, ins);
                W32(cm + 0x14, CALL(0x236f80, P32(self + 0xc), P32(0x587d08)));
                W32(cm + 0x18, frame);
                W32(cm + 0x1c, P32(self + 0xc));
                if (cmd == 1)
                    W8(cm + 0x40, 1);
                for (i = 0; i < 4; i++) {
                    ins = CALL(0x301000, self);
                    if (P8(GP_FLAG) == 0)
                        ins = CALL(0x2f88e0, P32(0x587110));
                    {
                        int32_t o1 = CALL(0x3c6830, ins);
                        CALL(0x301e30, P32(cm + 0x24), o1);
                        release(api, o1);
                    }
                    ins = CALL(0x301000, self);
                    if (P8(GP_FLAG) == 0)
                        ins = CALL(0x2f88e0, P32(0x587110));
                    {
                        int32_t o2 = CALL(0x3c56b0, ins);
                        CALL(0x301e30, P32(cm + 0x28), o2);
                        release(api, o2);
                    }
                }
                W32(cm + 0x38, 0);
                CALL(0x3f0ed0, P32(cm + 0x34), messenger, 0);
                CALL(0x301e30, P32(frame + 0x28), cm);
                release(api, cm);
            }
            release(api, ctrl);
        }
        ret = 1;
    } else if (P32(frame + 0x28) != 0) {
        CALL(0x3022c0, P32(frame + 0x28), DW4_LOAD_TBL, DW4_LOAD_CTRL);
        if (cmd == 3) {
            if (CALL(0x38f660, messenger) == 0) {
                int32_t ci = CALL(0x3022c0, P32(frame + 0x28), DW4_LOAD_TBL, DW4_LOAD_COMMONINTF);
                CALL(0x38f670, messenger, ci);
            }
            ret = 1;
        } else if (cmd == 2) {
            ret = 1;
        } else {
            ret = 0;
        }
    }
    return ret;
}
