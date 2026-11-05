#include "item-database.h"
#define P(p) ((uint32_t)a->read(a->user, (p), 4))
#define W(p, v) a->write(a->user, (p), 4, (uint32_t)(v))
#define CALL(e, ...) a->call(a->user, (e), (const uint64_t[8]){__VA_ARGS__})
static uint64_t word(uint32_t value) { return (uint64_t)(int64_t)(int32_t)value; }
uint64_t dw4_item_database(const Dw4MessengerResultsApi *a, uint32_t entry, const uint64_t v[8],
                           uint32_t scratch) {
    uint32_t self = (uint32_t)v[0];
    if (entry == 0x447bc0) {
        uint32_t messenger = P((uint32_t)v[1] + 20);
        CALL(0x38e5f0, word(messenger), 0x51d550, v[2], 0, 0x51d560);
        return CALL(0x38f800, word(messenger), 0);
    }
    if (entry == 0x448640)
        return CALL(0x447bc0, v[0], v[1], 0x51d598);
    if (entry == 0x447c10 || entry == 0x447c60 || entry == 0x447cb0) {
        uint64_t key = v[2];
        uint64_t database = CALL(P(P(self) + 92), v[0], v[1]);
        return CALL(entry == 0x447c10   ? 0x3a9460
                    : entry == 0x447c60 ? 0x3a9540
                                        : 0x3a9580,
                    database, word(P(self + 12)), key);
    }
    if (entry == 0x3a93a0) {
        uint32_t columns = (uint32_t)v[3], stride = P(columns + 8);
        if (!stride)
            return UINT64_MAX;
        uint64_t found = CALL(0x3022c0, v[3], word(P(0x585be0)), v[2]);
        if (!found)
            return UINT64_MAX;
        W(scratch + 76, found);
        int32_t count = (int32_t)P(columns + 8), column = 0;
        if (count > 0) {
            uint32_t data = P(columns + 16), wanted = P(scratch + 76);
            do {
                if (P(data) == wanted)
                    goto found_column;
                column++;
                data += 4;
            } while (column < count);
        }
        column = -1;
    found_column:
        return word(stride * (uint32_t)v[1] + (uint32_t)column);
    }
    if (entry == 0x3a9460) {
        uint64_t index = CALL(0x3a93a0, v[0], v[1], v[2], word(P(self + 8)));
        if (index != UINT64_MAX)
            return (uint64_t)(int64_t)(int8_t)a->read(a->user,
                                                      P(P(self + 12) + 16) + (uint32_t)index, 1);
        index = CALL(0x3a93a0, v[0], v[1], v[2], word(P(self + 16)));
        if (index != UINT64_MAX)
            return (uint64_t)(int64_t)(int16_t)a->read(
                a->user, P(P(self + 20) + 16) + (uint32_t)index * 2, 2);
        index = CALL(0x3a93a0, v[0], v[1], v[2], word(P(self + 24)));
        if (index != UINT64_MAX)
            return word(P(P(P(self + 28) + 16) + (uint32_t)index * 4));
        return 0;
    }
    if (entry == 0x3a9540) {
        uint32_t index = (uint32_t)CALL(0x3a93a0, v[0], v[1], v[2], word(P(self + 40)));
        return a->read(a->user, P(P(self + 44) + 16) + index, 1);
    }
    if (entry == 0x3a9580) {
        uint32_t index = (uint32_t)CALL(0x3a93a0, v[0], v[1], v[2], word(P(self + 48)));
        uint32_t text = P(P(P(P(self + 52) + 16) + index * 4) + 8);
        return word(text ? text : 0x4e0858);
    }
    if (entry == 0x3a95e0) {
        static const uint32_t order[] = {48, 8, 16, 24, 32, 40};
        for (unsigned i = 0; i < 6; i++) {
            uint32_t offset = order[i];
            int32_t columns = (int32_t)P(P(self + offset) + 8);
            if (columns) {
                int32_t values = (int32_t)P(P(self + offset + 4) + 8);
                return word((uint32_t)((int64_t)values / columns));
            }
        }
        return 0;
    }
    return UINT64_MAX;
}
