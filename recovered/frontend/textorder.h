/* beNDMWLoadIntf2's text-order publishing helpers.
 *
 * Recovered from the retail binary (see docs/engine/load-intf2.md §Recovered
 * text-order helpers).  These six functions turn a screen control id into
 * the actual "text line" published to the interface messenger:
 *
 *   0x003eba10  to_configure       alignment/colour/text/show commands
 *   0x003ebd70  to_configure_font  configure via font set/index
 *   0x003ebdc0  to_clear_font      clear via font set/index
 *   0x003ebce0  to_line   publish one line (name + font + the two style tags)
 *   0x003ebe00  to_set    publish the id's line list, set the global text
 *                         pointers, and fire the open/close animation token
 *   0x003ec050  to_pub    close variant: publish the id's line list only
 *
 * They own no state of their own beyond the two process-wide text pointers at
 * 0x0058a220 / 0x0058a1e0; everything else is passed in.  The engine/messenger
 * callees stay opaque (api->call) as in the rest of recovered/frontend/.
 */
#ifndef DW4_TEXTORDER_H
#define DW4_TEXTORDER_H

#include <stdint.h>

#include "loadintf2.h"

/* 0x003eba10 — ALIGN (0=LEFT, 1=CENTER, 2=RIGHT), colour
 * (0=DEFAULTCOLOR, 1=CANCELCOLOR), TEXTSET, SWITCH SET in that order.
 * Other align/colour values omit that command, preserving existing settings. */
void to_configure(const Dw4LoadIntf2Api *api, int32_t owner, int32_t name,
                  int32_t font, int32_t text, int32_t align, int32_t colour);

/* 0x003ebd70 — resolve font[set][index], then configure the text. */
void to_configure_font(const Dw4LoadIntf2Api *api, int32_t owner, int32_t name,
                       int32_t set, int32_t index, int32_t text,
                       int32_t align, int32_t colour);

/* 0x003ebdc0 — resolve font[set][index], then SWITCH CLR. */
void to_clear_font(const Dw4LoadIntf2Api *api, int32_t owner, int32_t name,
                   int32_t set, int32_t index);

/* 0x003ebce0 — publish one text line: set the messenger string, then the
 * name, the font, and the two style tags. */
void to_line(const Dw4LoadIntf2Api *api, int32_t owner, int32_t name, int32_t font);

/* 0x003ebe00 — publish the line list for `id`, set 0x58a220/0x58a1e0 from the
 * entry, fire the animation token keyed off `id & 0xf000`, and (when flag==1
 * and the entry carries bit 20) latch the following entry's text pointer and
 * repeat the animation without publishing its line list. */
void to_set(const Dw4LoadIntf2Api *api, int32_t owner, int32_t id, int32_t flag);

/* 0x003ec050 — the close variant of to_set: publish the line list for `id`
 * with no global or animation side effects. */
void to_pub(const Dw4LoadIntf2Api *api, int32_t owner, int32_t id);

#endif /* DW4_TEXTORDER_H */
