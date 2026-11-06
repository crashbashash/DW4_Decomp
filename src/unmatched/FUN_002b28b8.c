/* For a video descriptor `id` (FUN_002b25a8, tag 0xE0 from FUN_002b2ea0), unpacks the two 12-bit
 * picture dimensions packed in the three bytes at +28 into *width and *height; returns 1 then,
 * else 0 with both cleared. */
struct Descriptor {
    char pad0[28];
    unsigned char size[3]; /* +28; 12-bit width, 12-bit height */
};

struct Descriptor *FUN_002b25a8(void *ctx, unsigned char id);
int FUN_002b2ea0(unsigned char id);

int FUN_002b28b8(void *ctx, unsigned char id, int *width, int *height) {
    struct Descriptor *desc;
    unsigned char *size;

    *width = 0;
    *height = 0;
    desc = FUN_002b25a8(ctx, id);
    if (desc == 0) {
        return 0;
    }
    if (FUN_002b2ea0(id) != 0xE0) {
        return 0;
    }
    size = desc->size;
    *width = size[0];
    *width = (*width << 4) | (size[1] >> 4);
    *height = size[1];
    *height = ((*height << 8) | size[2]) & 0xFFF;
    return 1;
}
