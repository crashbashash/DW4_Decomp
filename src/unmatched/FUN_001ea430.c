typedef struct TextureInfo {
    char pad[44];
    struct ImageNode *owner;
} TextureInfo;

typedef struct ImageNode {
    int pad0;
    struct ImageNode *next;
    void *data;
    TextureInfo *texture;
    signed char format : 2;
    signed char order : 4;
    short layout : 4;
} ImageNode;

void FUN_00204240(int kind, ImageNode **pool);
TextureInfo *p2LoadTexture(void *data, int width, int height, int psm, int flags);
extern ImageNode *DAT_00562d88;

ImageNode *FUN_001ea430(int format, int order, int layout, void *data)
{
    /* matching construct: declaration-order permutation sweep (24 variants) */
    int psm;
    int width;
    int height;
    ImageNode *node;

    switch (layout) {
    case 0:
    case 2:
    case 10:
        break;
    default:
        return 0;
    }
    switch (format) {
    case 0:
        width = 8;
        height = 2;
        psm = 13;
        break;
    case 1:
        width = 16;
        psm = 14;
        height = width;
        break;
    default:
        return 0;
    }
    if (DAT_00562d88 == 0) FUN_00204240(3, &DAT_00562d88);
    node = DAT_00562d88;
    DAT_00562d88 = node->next;
    node->data = 0;
    node->data = data;
    node->format = format;
    node->order = order;
    node->layout = layout;
    node->texture = p2LoadTexture(node->data, width, height, psm, 0);
    if (node->texture != 0) node->texture->owner = node;
    return node;
}
