typedef struct PackedTable {
    char _pad0[10];
    unsigned char widthA;
    unsigned char widthB;
    char _pad12;
    unsigned char widthC;
    unsigned char widthD;
    char _pad15;
    char *data;
    char _pad20[16];
    unsigned char stride;
    char _pad37[7];
    short rowBytes;
    short _pad46;
    short rowLength;
    short _pad50;
    short _pad52;
    short offset;
} PackedTable;

/* matching construct: declaration-order sweep — values, row, cursor, column, rowLength, b, c, stride, width */
void FUN_001fe260(PackedTable *table, int index, float *first, float *second) {
    float *values;
    int row;
    char *cursor;
    int column;
    int rowLength;
    int b;
    int c;
    int stride;
    int width;

    rowLength = table->rowLength;
    cursor = table->data;
    b = table->widthB;
    width = table->widthA;
    stride = table->stride;
    row = index / rowLength;
    cursor += 0xC;
    column = index % rowLength;
    width = ((b < width) ? width : b) & 0xFF;
    c = table->widthC;
    width = (c < width) ? width : c;
    c = table->widthD;
    width = (c < width) ? width : c;
    cursor += row * table->rowBytes;
    cursor += table->offset;
    cursor += stride * (column * width) * 4;
    values = (float *)cursor;
    switch (width) {
    case 3:
    case 2:
        second[0] = *(float *)((char *)values + stride * 4 + 12);
    case 1:
        first[0] = values[3];
    }
}
