/* 0x002a1f28 — FUN_002a1f28 (168 bytes). Writes length bytes into the ring in up to two pieces (FUN_002a1fd0) when slot 36 reports room; counts short second writes in DAT_004beb00. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a1fd0();
extern volatile int DAT_004beb00;

struct Ring;
struct RingOps {
    char pad[36];
    int (*fn36)(struct Ring *, int);      /* free bytes on a side */
};
struct Ring {
    struct RingOps *ops;
};

/* Writes length bytes into the ring in up to two pieces when there is room; counts short second writes. */
int FUN_002a1f28(struct Ring *ring, char *data, int length) {
    int written;

    if (ring->ops->fn36(ring, 0) < length) {
        return 0;
    }
    written = FUN_002a1fd0(ring, data, length);
    if (written == 0) {
        return 0;
    }
    length -= written;
    data += written;
    if (length > 0 && FUN_002a1fd0(ring, data, length) != length) {
        DAT_004beb00++;
    }
    return 1;
}
