/* Lays out a frame buffer at base for width x height: 64-byte aligned luma/chroma strides and the
 * plane addresses. */
struct Planes {
    char *luma;
    char *chroma;
    char *base;
    short chromaStride;
    short lumaStride;
};

void FUN_002a3170(char *base, int width, int height, struct Planes *planes) {
    int columns = (width + 15) / 16;
    int rows;
    int lumaBlocks = (columns * 16 + 63) / 64;
    int chromaBlocks;

    rows = (height + 15) / 16;
    chromaBlocks = (columns * 8 + 63) / 64;
    planes->lumaStride = lumaBlocks << 6;
    planes->chromaStride = chromaBlocks << 6;
    planes->base = base;
    planes->luma = base + ((lumaBlocks * rows) << 10);
    planes->chroma = planes->luma + ((chromaBlocks * rows) << 9);
}
