#include "registry-bootstrap.h"
#include "allocator-registry.h"
#define P(p) ((uint32_t)a->read(a->user, (p), 4))
#define W(p,v) a->write(a->user, (p), 4, (uint32_t)(v))
#define CALL(e,...) a->call(a->user, (e), (const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_registry_bootstrap(a, (e), (const uint64_t[8]){__VA_ARGS__}, scratch)
static uint64_t word(uint32_t v) {return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t method(const Dw4MessengerResultsApi *a, uint32_t object, unsigned slot) {
    return P(P(object) + slot);
}
static uint32_t allocator(const Dw4MessengerResultsApi *a) {return P(P(0x586dc8) + 48);}
uint64_t dw4_registry_bootstrap(const Dw4MessengerResultsApi *a, uint32_t entry,
                                const uint64_t v[8], uint32_t scratch) {
    uint32_t self = (uint32_t)v[0], pool, value;
    switch (entry) {
    case 0x2fa4d0:
        W(self + 8, 64); W(self + 4, 0);
        pool = allocator(a);
        value = (uint32_t)CALL(method(a, pool, 216), pool, word(P(self + 8) * 4));
        W(self, value);
        CALL(0x12724c, P(self), 0, word(P(self + 8) * 4));
        return word(self);
    case 0x2fa540:
        if (self) {
            value = P(self);
            if (value) {pool = allocator(a); CALL(method(a, pool, 264), pool, value);}
            if ((int16_t)v[1] > 0) CORE(0x2fa6e0, v[0]);
        }
        return v[0];
    case 0x2fa5c0:
        return dw4_allocator_registry(a, entry, v);
    case 0x2fa610:
        if ((int32_t)P(self + 4) >= (int32_t)P(self + 8)) {
            W(self + 8, P(self + 8) + 4);
            pool = allocator(a);
            value = (uint32_t)CALL(method(a, pool, 232), pool, P(self), word(P(self + 8) * 4));
            W(self, value);
            CALL(0x12724c, P(self) + (P(self + 8) - 4) * 4, 0, 16);
        }
        value = P(self + 4); W(self + 4, value + 1);
        W(P(self) + value * 4, v[1]);
        return 0;
    case 0x2fa6c0:
        pool = allocator(a); return CALL(method(a, pool, 216), pool, v[0]);
    case 0x2fa6e0:
        pool = allocator(a); CALL(method(a, pool, 264), pool, v[0]); return 0;
    case 0x2f2180:
        value = (uint32_t)CORE(0x2fa6c0, 12);
        if (value) value = (uint32_t)CORE(0x2fa4d0, value);
        W(0x586f58, value); CORE(0x2fa610, value, v[0]);
        a->write(a->user, self + 7, 1, 0);
        value = (uint32_t)CORE(0x2fa6c0, 12);
        if (value) value = (uint32_t)CORE(0x2fa4d0, value);
        W(0x586f60, value); return 0;
    case 0x2f2200:
        CORE(0x2fa540, P(0x586f58), 1);
        CORE(0x2fa540, P(0x586f60), 1);
        W(0x586f58, 0); W(0x586f60, 0);
        CALL(method(a, self, 392), v[0]); return 0;
    case 0x2f8680: case 0x2f88d0:
        value = P(0x587010);
        if ((int32_t)value > 0 && (int32_t)value < 4) return word(P(0x586ffc + value * 4));
        if (!value && P(0x586fd0)) return word(P(0x586fd0));
        return 0;
    case 0x2f2730: {
        int32_t selector = (int32_t)v[1];
        if (selector < 0 || selector >= 46) return 0;
        uint32_t cell = self + (uint32_t)selector * 144 + 20;
        value = P(cell);
        if (value) return word(value);
        if (P(cell + 140) & 0x04000000) {
            CALL(method(a, self, 208), scratch, v[0], v[1], v[0]);
            return word(P(cell));
        }
        int32_t depth = (int32_t)P(0x587010);
        if (depth < 2) return 0;
        int32_t i = depth - 1;
        while (i >= 0 && P(0x587000 + (uint32_t)i * 4) != self) --i;
        int32_t previous = i - 1;
        if (previous < 0) return 0;
        uint32_t parent = P(0x587000 + (uint32_t)previous * 4);
        if (parent == self) return 0;
        return CALL(method(a, parent, 92), parent, v[1]);
    }
    case 0x2f2830: {
        uint32_t name = (uint32_t)v[1];
        if (!name || !a->read(a->user, name, 1)) return 0;
        for (uint32_t i = 0; i < 46; ++i)
            if (!CALL(0x12a4a4, self + i * 144 + 24, v[1]))
                return CALL(method(a, self, 92), v[0], i);
        return 0;
    }
    case 0x2f88e0: case 0x2f8920: case 0x2f8960: case 0x2f89a0: case 0x2f89e0: {
        uint32_t slot = entry == 0x2f88e0 ? 92 : entry == 0x2f8920 ? 96 :
                        entry == 0x2f8960 ? 104 : entry == 0x2f89a0 ? 108 : 116;
        uint64_t context = CORE(0x2f88d0);
        return CALL(method(a, (uint32_t)context, slot), context, v[0]);
    }
    default: return UINT64_MAX;
    }
}
