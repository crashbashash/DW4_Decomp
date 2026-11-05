/* recovered/frontend/textorder.c — see textorder.h for the contracts. */

#include "textorder.h"

#define P32(a)     api->peek(api->user, (a), 4)
#define W32(a, v)  api->poke(api->user, (a), 4, (v))
#define CALL(addr, ...) api->call(api->user, (addr), (const int32_t[8]){__VA_ARGS__})

/* The interface's static tables (read-only, in the ELF image). */
#define TO_TABLE     0x004cda40   /* {u32 id : 12; u32 ptr; u32 line-list}[] */
#define TO_TABLE_LEN 0x000fffff   /* id match mask (low 20 bits) */
#define TO_FONTS     0x004ceb30   /* font[sets][index] table, stride 0x14 */
#define TO_TEXT_PTR  0x0058a220   /* process-wide current-text pointer */
#define TO_TEXT_AUX  0x0058a1e0   /* its companion, always cleared here */

#define TO_T_ANIM_ON  0x517a28    /* animation token for id&0xf000 != 0 */
#define TO_T_ANIM_OFF 0x517a18    /* animation token for id&0xf000 == 0 */

/* Begin one TEXTCTL message. Reload owner+0x10 before each engine call,
 * as retail does: a messenger callback may replace the binding. */
static void to_begin(const Dw4LoadIntf2Api *api, int32_t owner,
                     int32_t name, int32_t font)
{
    CALL(0x38d860, P32(owner + 0x10), 0x5179b0, 0, -1);
    CALL(0x38f830, P32(owner + 0x10), name);
    CALL(0x38f830, P32(owner + 0x10), font);
}

/* 0x003eba10..0x003ebcd4: configure text, then SWITCH SET.
 * Unsupported alignment/colour values preserve that existing setting. */
void to_configure(const Dw4LoadIntf2Api *api, int32_t owner, int32_t name,
                  int32_t font, int32_t text, int32_t align, int32_t colour)
{
    if (align >= 0 && align <= 2) {
        to_begin(api, owner, name, font);
        CALL(0x38f830, P32(owner + 0x10),
             align == 0 ? 0x5179b8 : align == 1 ? 0x5179c8 : 0x5179d0);
        CALL(0x38e060, P32(owner + 0x10), 0x5179c0); /* ALIGN */
    }
    if (colour == 0 || colour == 1) {
        to_begin(api, owner, name, font);
        CALL(0x38e060, P32(owner + 0x10),
             colour == 0 ? 0x5179d8 : 0x5179e8); /* DEFAULT/CANCELCOLOR */
    }
    to_begin(api, owner, name, font);
    CALL(0x38f830, P32(owner + 0x10), text);
    CALL(0x38e060, P32(owner + 0x10), 0x5179f8); /* TEXTSET */
    to_begin(api, owner, name, font);
    CALL(0x38f830, P32(owner + 0x10), 0x517a00); /* SET */
    CALL(0x38e060, P32(owner + 0x10), 0x517a08); /* SWITCH */
}

/* 0x003ebd70: seven-argument font-table wrapper. */
void to_configure_font(const Dw4LoadIntf2Api *api, int32_t owner, int32_t name,
                       int32_t set, int32_t index, int32_t text,
                       int32_t align, int32_t colour)
{
    uint32_t address = TO_FONTS + (uint32_t)set * 0x50u + (uint32_t)index * 4u;
    to_configure(api, owner, name, P32(address), text, align, colour);
}

/* 0x003ebdc0: clear a line selected through the same font table. */
void to_clear_font(const Dw4LoadIntf2Api *api, int32_t owner, int32_t name,
                   int32_t set, int32_t index)
{
    uint32_t address = TO_FONTS + (uint32_t)set * 0x50u + (uint32_t)index * 4u;
    to_line(api, owner, name, P32(address));
}

/* 0x003ebce0 — publish one text line. */
void to_line(const Dw4LoadIntf2Api *api, int32_t owner, int32_t name, int32_t font)
{
    to_begin(api, owner, name, font);
    CALL(0x38f830, P32(owner + 0x10), 0x517a10);
    CALL(0x38e060, P32(owner + 0x10), 0x517a08);
}

/* Walk the line list at `list`, publishing each {name; set; index} triple. */
static void to_lines(const Dw4LoadIntf2Api *api, int32_t owner, int32_t list)
{
    while (P32(list) != 0) {
        int32_t set = P32(list + 4);
        int32_t idx = P32(list + 8);
        to_line(api, owner, P32(list), P32(TO_FONTS + set * 0x50 + idx * 4));
        list += 0xc;
    }
}

/* Index of the table entry whose low 20 bits are `id`; -1 if absent.
 * `sentinel` selects 0x003ebe00's -1 terminator check (0x003ec050 walks
 * without one, relying on the id always being present). */
static int32_t to_index(const Dw4LoadIntf2Api *api, int32_t id, int sentinel)
{
    int32_t i;
    for (i = 0; ; i++) {
        int32_t w = P32(TO_TABLE + i * 0xc);
        if (sentinel && w == -1)
            return -1;
        if ((w & TO_TABLE_LEN) == id)
            return i;
    }
}

/* id & 0xf000 selects the on/off animation token. */
static void to_anim(const Dw4LoadIntf2Api *api, int32_t owner, int32_t hi)
{
    if (hi == 0x3000 || hi == 0x2000 || hi == 0x1000)
        CALL(0x389ff0, P32(owner + 0x14), TO_T_ANIM_ON, 0);
    else if (hi == 0)
        CALL(0x389ff0, P32(owner + 0x14), TO_T_ANIM_OFF, 0);
}

/* 0x003ec050 — publish the id's line list; no global or animation effects. */
void to_pub(const Dw4LoadIntf2Api *api, int32_t owner, int32_t id)
{
    int32_t i = to_index(api, id, 0);
    to_lines(api, owner, P32(TO_TABLE + 8 + i * 0xc));
}

/* 0x003ebe00 — publish the id's line list, latch the text pointers, fire the
 * animation token, and optionally latch the following entry too. */
void to_set(const Dw4LoadIntf2Api *api, int32_t owner, int32_t id, int32_t flag)
{
    int32_t i = to_index(api, id, 1);
    int32_t hi;
    if (i == -1)
        return;
    to_lines(api, owner, P32(TO_TABLE + 8 + i * 0xc));
    hi = id & 0xf000;
    W32(TO_TEXT_PTR, P32(TO_TABLE + 4 + i * 0xc));
    W32(TO_TEXT_AUX, 0);
    to_anim(api, owner, hi);
    if (flag == 1 && (P32(TO_TABLE + i * 0xc) & 0x100000)) {
        W32(TO_TEXT_PTR, P32(TO_TABLE + 4 + (i + 1) * 0xc));
        W32(TO_TEXT_AUX, 0);
        to_anim(api, owner, hi);
    }
}
