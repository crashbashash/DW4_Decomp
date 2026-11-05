#include "chip-controller.h"
/* Original update 43aae0..43c71c; all guest addresses are explicit.
 * Window: primary28, phase32, subphase36, counter/error40, child result48,
 * retained children52, close queues60..76, captured child count80.
 * ListCtrl: page84, max pages88, cursor92. Chip controller: item list96.
 * ItemBase: kind8, catalogue record12, equipped byte16. Record12 is NOT
 * an inferred upgrade counter. Preview temporarily changes that same field.
 */
#define P(p) ((uint32_t)a->read(a->user, (p), 4))
#define B(p) ((uint32_t)a->read(a->user, (p), 1))
#define W(p, v) a->write(a->user, (p), 4, (uint32_t)(v))
#define CALL(e, ...) a->call(a->user, (e), (const uint64_t[8]){__VA_ARGS__})
#define MSG word(P(self + 12))
static uint64_t word(uint32_t n) { return (uint64_t)(int64_t)(int32_t)n; }
static void release(const Dw4MessengerResultsApi *a, uint32_t p) {
    if (p) {
        W(p + 4, P(p + 4) - 1);
        if (!(P(p + 4) & 0x7fffff))
            CALL(0x2ff820, word(p));
    }
}
static void unstring(const Dw4MessengerResultsApi *a, uint32_t p) {
    if (p) {
        W(p - 4, P(p - 4) - 1);
        if (!P(p - 4))
            CALL(0x30c940, word(P(p - 8)), word(p - 8));
    }
}
static uint64_t allocator(const Dw4MessengerResultsApi *a, uint64_t owner) {
    uint64_t p = CALL(0x301000, owner);
    if (!B(0x554c14))
        p = CALL(0x2f88e0, word(P(0x587110)));
    return p;
}
static uint32_t intern(const Dw4MessengerResultsApi *a, uint64_t s) {
    if (!P(0x586f20)) {
        uint64_t m = CALL(0x2eb010, 16);
        W(0x586f20, m ? CALL(0x2eadf0, m) : 0);
    }
    return (uint32_t)CALL(0x2eaf60, word(P(0x586f20)), s);
}
static void append(const Dw4MessengerResultsApi *a, uint32_t list, uint32_t temp, uint64_t s) {
    W(temp, intern(a, s));
    CALL(0x1ca620, word(list), temp);
    unstring(a, P(temp));
}
static void advance(const Dw4MessengerResultsApi *a, uint32_t self) {
    W(self + 28, P(self + 28) + 1);
    W(self + 40, 0);
    W(self + 36, 0);
    W(self + 32, 0);
}
static void phase(const Dw4MessengerResultsApi *a, uint32_t self, uint32_t n) {
    W(self + 32, n);
    W(self + 40, 0);
    W(self + 36, 0);
}
static void subphase(const Dw4MessengerResultsApi *a, uint32_t self) {
    W(self + 36, P(self + 36) + 1);
    W(self + 40, 0);
}
static void restart(const Dw4MessengerResultsApi *a, uint32_t self) {
    phase(a, self, 0);
    W(self + 36, 1);
    W(self + 40, 0);
}
static uint32_t children(const Dw4MessengerResultsApi *a, uint32_t self) {
    return P(P(self + 52) + 8);
}
static void snapshot(const Dw4MessengerResultsApi *a, uint32_t self) {
    W(self + 80, children(a, self));
}
static int changed(const Dw4MessengerResultsApi *a, uint32_t self) {
    return children(a, self) != P(self + 80);
}
static void child(const Dw4MessengerResultsApi *a, uint32_t self, uint64_t owner, uint32_t temp,
                  uint32_t factory, uint64_t entry, int live_error) {
    W(temp, CALL(factory, allocator(a, owner)));
    CALL(0x3f63c0, word(P(temp)), owner, word(P(self + 8)), word(P(self + 20)),
         live_error ? word(P(self + 40)) : entry);
    CALL(0x301e30, word(P(self + 52)), word(P(temp)));
}
static void message(const Dw4MessengerResultsApi *a, uint32_t self, uint32_t group,
                    uint32_t command, int select) {
    if (select)
        CALL(0x38d860, MSG, group, 0, 0);
    else
        CALL(0x38e5d0, MSG, group);
    CALL(0x38f250, MSG, word(P(self + 20)));
    CALL(0x38e060, MSG, command);
}
static uint64_t player(const Dw4MessengerResultsApi *a, uint32_t self) {
    message(a, self, 0x51b398, 0x51b3e8, 0);
    return CALL(0x38f800, MSG, 0);
}
static uint64_t status(const Dw4MessengerResultsApi *a, uint32_t self) {
    return CALL(0x236f80, word(P(self + 8)), word(P(0x58b028)));
}
static uint32_t index(const Dw4MessengerResultsApi *a, uint32_t self) {
    return P(self + 84) * 12 + P(self + 92);
}
static uint32_t item(const Dw4MessengerResultsApi *a, uint32_t self, uint32_t idx) {
    return P(P(P(self + 96) + 16) + idx * 4);
}
static void queue(const Dw4MessengerResultsApi *a, uint32_t cell, uint64_t group, uint64_t font,
                  uint64_t value, uint64_t style) {
    CALL(0x3f5410, word(P(cell)), group, font, value, style);
}
uint64_t dw4_chip_controller(const Dw4MessengerResultsApi *a, const uint64_t v[8],
                             uint32_t scratch) {
    uint32_t self = (uint32_t)v[0], primary = P(self + 28);
    if (primary == 3) {
        if (CALL(0x3f6090, v[0]))
            a->write(a->user, self + 24, 1, 0);
        return 0;
    }
    if (primary == 2) {
        CALL(0x3f5f80, v[0]);
        CALL(0x3f5a40, v[0]);
        CALL(0x3f6350, v[0]);
        advance(a, self);
        return 0;
    }
    if (primary != 1) {
        if (primary)
            return 0;
        append(a, P(self + 60), scratch + 252, 0x51b668);
        append(a, P(self + 64), scratch + 248, 0x51b1c8);
        append(a, P(self + 60), scratch + 244, 0x51be10);
        append(a, P(self + 64), scratch + 240, 0x51b1c8);
        for (uint32_t i = 0; i < 12; i++) {
            CALL(0x3f5410, v[0], 0x51b3c8, word(P(0x4cf8a0 + i * 4)), 0x51b590, 0x51b598);
            CALL(0x3f5410, v[0], 0x51b680, word(P(0x4cf8a0 + i * 4)), 0x51b590, 0x51b460);
        }
        CALL(0x3f5410, v[0], 0x51b470, word(P(0x4cf8a0)), 0x51b590, 0x51b598);
        CALL(0x3f5410, v[0], 0x51b470, 0x51b548, 0x51b590, 0x51b598);
        CALL(0x3f5410, v[0], 0x51bd60, word(P(0x4cf8a0)), 0x51b590, 0x51bd98);
        CALL(0x3f5410, v[0], 0x51bd60, word(P(0x4cf8a4)), 0x51b590, 0x51bd98);
        advance(a, self);
    }
    uint32_t main = P(self + 32), sub = P(self + 36);
    /* Empty-list error closes the owner; other errors return to selection. */
    if (main == 10 || main == 11) {
        if (sub != 1) {
            if (sub)
                return 0;
            uint32_t temp = scratch + (main == 10 ? 260 : 256);
            child(a, self, v[0], temp, 0x3b4f50, 0, 1);
            if (main == 10) {
                uint32_t box = P(temp), token = intern(a, 0x51b548);
                unstring(a, P(box + 112));
                W(box + 112, token);
            }
            release(a, P(temp));
            snapshot(a, self);
            subphase(a, self);
        }
        if (changed(a, self)) {
            if (main == 10)
                advance(a, self);
            else
                restart(a, self);
        }
        return 0;
    }
    /* Quote eligibility compares full signed64 NEXTX against sign-extended wallet. */
    if (main == 3) {
        uint64_t folder = player(a, self);
        uint32_t p = (uint32_t)CALL(0x3a9220, folder, 0x51b440), balance = P(p + 12),
                 idx = index(a, self);
        uint64_t ctx = status(a, self);
        int64_t cost = (int64_t)CALL(0x447c10, word(item(a, self, idx)), ctx, 0x51be38);
        if (cost == -1) {
            phase(a, self, 11);
            W(self + 40, 0x492);
        } else if ((int32_t)balance < cost) {
            phase(a, self, 11);
            W(self + 40, 0x489);
        } else
            phase(a, self, P(self + 32) + 1);
        return 0;
    }
    /* Build preview/notice, await it, ask confirmation, then commit fresh values. */
    if (main == 4) {
        if (sub != 2) {
            if (sub != 1) {
                if (sub)
                    return 0;
                child(a, self, v[0], scratch + 280, 0x3b4f50, 0, 0);
                uint32_t idx = index(a, self);
                uint64_t ctx = status(a, self);
                uint32_t selected = item(a, self, idx), rec = P(selected + 12);
                if (B(selected + 16)) {
                    W(selected + 12, rec + 1);
                    message(a, self, 0x51b398, 0x51b3a0, 1);
                    message(a, self, 0x51b498, 0x51bdf0, 0);
                    W(selected + 12, rec);
                    message(a, self, 0x51b398, 0x51b3a0, 1);
                }
                W(scratch + 276, CALL(0x3c87f0, allocator(a, v[0])));
                CALL(0x448660, word(P(scratch + 276)), word(rec + 1));
                uint64_t name = CALL(0x447cb0, word(P(scratch + 276)), ctx, 0x51b678);
                queue(a, scratch + 280, 0x51b470, word(P(0x4cf8a0)), name, 0x51b598);
                for (unsigned i = 1; i <= 3; i++)
                    queue(a, scratch + 280, 0x51b448, word(P(0x4cf8a0 + i * 4)), 0x51b590,
                          0x51b598);
                queue(a, scratch + 280, 0x51b470, word(P(0x4cf8a8)), 0x51b590, 0x51b598);
                W(scratch + 272, CALL(0x2b90e0, allocator(a, v[0])));
                static const uint32_t keys[] = {0x51b3f8, 0x51b408, 0x51b418, 0x51b420,
                                                0x51be40, 0x51be50, 0x51be58, 0x51be68,
                                                0x51be78, 0x51be88, 0x51be90, 0x51be98};
                for (unsigned i = 0; i < 12; i++)
                    append(a, P(scratch + 272), scratch + 236 - i * 4, keys[i]);
                /* Retail deliberately performs a second status lookup here. */
                uint64_t comparison_ctx = status(a, self);
                /* This unused integer-list object still has allocation/release effects. */
                W(scratch + 268, CALL(0x2caa70, allocator(a, v[0])));
                uint32_t i = 0;
                if ((int32_t)P(P(scratch + 272) + 8) > 0) {
                    do {
                        CALL(0x1c64e0, scratch + 188, word(P(scratch + 272)), word(i));
                        uint64_t difference = CALL(0x447c10, word(P(scratch + 276)), comparison_ctx,
                                                   word(P(scratch + 188)));
                        unstring(a, P(scratch + 188));
                        if ((int64_t)difference > 0) {
                            CALL(0x129e60, scratch + 144, 0x51b468, difference);
                            queue(a, scratch + 280, 0x51b448, 0x51b220, scratch + 144, 0x51b460);
                            if (i >= 8)
                                i = 7;
                            for (unsigned j = 0; j < 8; j++)
                                W(scratch + 112 + j * 4, P(0x4cfaa0 + j * 4));
                            W(P(scratch + 280) + 44, P(scratch + 112 + i * 4));
                            break;
                        }
                        i++;
                    } while ((int32_t)i < (int32_t)P(P(scratch + 272) + 8));
                }
                release(a, P(scratch + 268));
                release(a, P(scratch + 272));
                uint64_t folder = player(a, self);
                uint32_t p = (uint32_t)CALL(0x3a9220, folder, 0x51b440), balance = P(p + 12),
                         cost = (uint32_t)CALL(0x447c10, word(selected), ctx, 0x51be38);
                CALL(0x129e60, scratch + 144, 0x51b468, word(balance - cost));
                queue(a, scratch + 280, 0x51b448, 0x51b248, scratch + 144, 0x51b460);
                release(a, P(scratch + 276));
                release(a, P(scratch + 280));
                snapshot(a, self);
                subphase(a, self);
            }
            if (!changed(a, self))
                return 0;
            child(a, self, v[0], scratch + 264, 0x3b4d90, 0x493, 0);
            release(a, P(scratch + 264));
            snapshot(a, self);
            subphase(a, self);
        }
        if (changed(a, self)) {
            message(a, self, 0x51b498, 0x51be00, 0);
            if (!P(self + 48)) {
                uint32_t idx = index(a, self);
                uint64_t ctx = status(a, self);
                uint32_t selected = item(a, self, idx);
                uint64_t folder = player(a, self);
                uint32_t p = (uint32_t)CALL(0x3a9220, folder, 0x51b440), balance = P(p + 12),
                         cost = (uint32_t)CALL(0x447c10, word(selected), ctx, 0x51be38);
                p = (uint32_t)CALL(0x3a9220, folder, 0x51b440);
                W(p + 12, balance - cost);
                W(selected + 12, P(selected + 12) + 1);
                message(a, self, 0x51b398, 0x51b3a0, 0);
                message(a, self, 0x51b498, 0x51b4a0, 0);
            }
            restart(a, self);
        }
        return 0;
    }
    if (main != 0 && main != 1 && main != 2)
        return 0;
    /* Always rebuild the retained chip list; subphase only gates initial UI. */
    if (main == 0) {
        {
            uint64_t folder = player(a, self);
            uint32_t p = (uint32_t)CALL(0x3a9340, folder, 0x51b528), inventory = P(p + 12),
                     list = P(self + 96), n = P(list + 8);
            for (uint32_t i = 0; (int32_t)i < (int32_t)n; i++)
                release(a, P(P(list + 16) + i * 4));
            n = P(list + 8);
            for (uint32_t i = 0; (int32_t)i < (int32_t)n; i++)
                W(P(list + 16) + i * 4, 0);
            W(list + 8, 0);
            uint32_t i = 0;
            if ((int32_t)P(inventory + 8) > 0) {
                do {
                    uint32_t entry = P(P(inventory + 16) + i * 4);
                    if (entry && P(entry + 8) == 3)
                        CALL(0x301e30, word(P(self + 96)), word(entry));
                    i++;
                } while ((int32_t)i < (int32_t)P(inventory + 8));
            }
            if ((int32_t)P(P(self + 96) + 8) < 1) {
                phase(a, self, 10);
                W(self + 40, 0x491);
                return 0;
            }
        }
        uint64_t rows = CALL(0x43c720, v[0]);
        if (!P(self + 36)) {
            CALL(0x3f5f00, v[0], 0x51b610, 0, 0x51be20, 0x51b620);
            CALL(0x3f5920, v[0], 0x51b3b0, 0x456);
            W(scratch + 160, 0x436c0000);
            W(scratch + 168, 0);
            W(scratch + 164, 0x41c80000);
            W(scratch + 176, 0xc3120000);
            W(scratch + 180, 0x41c80000);
            W(scratch + 184, 0);
            CALL(P(P(self) + 96), v[0], scratch + 176, scratch + 160);
        }
        child(a, self, v[0], scratch + 284, 0x3b51b0, 0, 0);
        W(P(scratch + 284) + 88, 0xc2f20000);
        W(P(scratch + 284) + 92, 0x43000000);
        W(P(scratch + 284) + 96, 0);
        W(P(scratch + 284) + 84, rows);
        W(P(scratch + 284) + 100, P(self + 92));
        release(a, P(scratch + 284));
        snapshot(a, self);
        phase(a, self, P(self + 32) + 1);
        return 0;
    }
    if (main == 1) {
        if (P(self + 48) != UINT32_MAX)
            CALL(0x43c7f0, v[0], 1, 1);
        phase(a, self, P(self + 32) + 1);
    }
    if (!changed(a, self)) {
        if (P(self + 48) != UINT32_MAX) {
            if (P(self + 40) != P(self + 48)) {
                CALL(0x43c7f0, v[0], 0, 1);
                W(self + 40, P(self + 48));
            } else {
                uint32_t box = P(P(P(self + 52) + 16));
                if (!box || !CALL(0x300cd0, word(box), word(P(0x58abd8))))
                    box = 0;
                if (box && CALL(0x423700, word(box))) {
                    uint64_t turn = CALL(P(P(self) + 100), v[0]);
                    if (!turn)
                        turn = CALL(P(P(self) + 104), v[0]);
                    if (turn) {
                        W(box + 28, 4);
                        W(box + 40, 0);
                        W(box + 36, 0);
                        W(box + 32, 0);
                        phase(a, self, 1);
                        uint64_t rows = CALL(0x43c720, v[0]);
                        W(box + 84, rows);
                    }
                }
            }
        }
    } else if (P(self + 48) == UINT32_MAX)
        advance(a, self);
    else {
        W(self + 92, P(self + 48));
        phase(a, self, P(self + 32) + 1);
    }
    return 0;
}
