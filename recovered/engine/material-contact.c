#include "material-contact.h"

/* beMatCtrl fields are recovered from reflection and the retail accesses:
 * +32 four inline player-existence bytes; +40 current material index;
 * +48 requested change index; +52 requested change byte;
 * +56 current and +60 previous igIntList references. List data is at +16.
 * No helper checks material bounds or null lists. */
static uint32_t mask(const Dw4MaterialContactApi *a, uint32_t self, unsigned field)
{
    uint32_t list = a->read(a->user, self + field, 4);
    uint32_t index = a->read(a->user, self + 40, 4);
    uint32_t data = a->read(a->user, list + 16, 4);
    return a->read(a->user, data + index * 4u, 4);
}

/* 0x0038aca0 — MATisPlayer: any set bit, including bits above player three. */
int dw4_mat_is_player(const Dw4MaterialContactApi *a, uint32_t self)
{
    return mask(a, self, 56) != 0;
}

/* 0x0038acd0 — MATisAllPlayer: true when no players exist. */
int dw4_mat_is_all_player(const Dw4MaterialContactApi *a, uint32_t self)
{
    int i;
    for (i = 0; i < 4; ++i) {
        uint32_t bit = 1u << i;
        if (a->read(a->user, self + 32u + i, 1) && (mask(a, self, 56) & bit) != bit)
            return 0;
    }
    return 1;
}

/* 0x0038ad40 — first existing player entering, not first player present.
 * Zero is also the no-result sentinel. */
int dw4_mat_get_player_no(const Dw4MaterialContactApi *a, uint32_t self)
{
    int i;
    for (i = 0; i < 4; ++i) {
        uint32_t bit = 1u << i;
        if (a->read(a->user, self + 32u + i, 1) &&
            (mask(a, self, 56) & bit) == bit && (mask(a, self, 60) & bit) != bit)
            return i;
    }
    return 0;
}

/* 0x0038add0 and 0x0038ae30. EE SLLV uses only the low five bits of player. */
int dw4_mat_is_ride_player(const Dw4MaterialContactApi *a, uint32_t self, int32_t player)
{
    uint32_t bit = 1u << ((uint32_t)player & 31u);
    return (mask(a, self, 56) & bit) == bit && (mask(a, self, 60) & bit) != bit;
}

int dw4_mat_is_ride_off_player(const Dw4MaterialContactApi *a, uint32_t self, int32_t player)
{
    uint32_t bit = 1u << ((uint32_t)player & 31u);
    return (mask(a, self, 56) & bit) != bit && (mask(a, self, 60) & bit) == bit;
}

/* 0x0038ae90 — record a deferred request, preserving the low byte of value. */
void dw4_mat_set_run(const Dw4MaterialContactApi *a, uint32_t self, uint32_t value)
{
    a->write(a->user, self + 48, 4, a->read(a->user, self + 40, 4));
    a->write(a->user, self + 52, 1, value & 255u);
}

/* 0x0038aea0 — outside=0, leaving=1, entering=2, staying=3. */
int dw4_mat_get_player_status(const Dw4MaterialContactApi *a, uint32_t self, int32_t player)
{
    uint32_t bit = 1u << ((uint32_t)player & 31u);
    int now = (mask(a, self, 56) & bit) == bit;
    int old = (mask(a, self, 60) & bit) == bit;
    if (now && old) return 3;
    if (now && !old) return 2;
    if (!now && old) return 1;
    return 0;
}
