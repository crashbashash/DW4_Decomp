/* recovered/frontend/completion.c — see completion.h for the contracts. */

#include "completion.h"

#define P32(a)     api->peek(api->user, (a), 4)
#define W32(a, v)  api->poke(api->user, (a), 4, (v))
#define W8(a, v)   api->poke(api->user, (a), 1, (v))

/* 0x003e4280 — is the open-data list empty?  retail masks with
 * slt/xori, i.e. returns (count <= 0). */
int cm_open_empty(const Dw4LoadIntf2Api *api, int32_t cm)
{
    return P32(P32(cm + 0x14) + 8) < 1;
}

/* 0x003e44d0 — is the close-data list empty? */
int cm_close_empty(const Dw4LoadIntf2Api *api, int32_t cm)
{
    return P32(P32(cm + 0x18) + 8) < 1;
}

/* 0x003ee190 — arm every per-player record, then select one row. */
void ds_select(const Dw4LoadIntf2Api *api, int32_t common, int32_t sel)
{
    int32_t data = P32(P32(common + 0x28) + 0x10);
    int32_t i, r;
    for (i = 0; i < 4; i++) {
        r = P32(data + i * 4);
        W32(r + 0x24, 1);
        W32(r + 0x30, 0);
        W32(r + 0x2c, 0);
        W32(r + 0x28, 0);
        W8(r + 0x0f, 0);
        W32(r + 8, 0x3c);
    }
    r = P32(data + sel * 4);
    W32(r + 0x24, 0);
    W32(r + 0x30, 0);
    W32(r + 0x2c, 0);
    W32(r + 0x28, 0);
    W8(r + 0x0f, 1);
    W32(r + 8, 0);
}
