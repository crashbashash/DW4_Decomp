/* Dispatches a descriptor to the handler DAT_004f5088[type][variant] with the type's context from
 * DAT_004f5060; without a handler reports error 0xFF000221 and returns 0 / 1 through the outputs. */
struct Descriptor {
    int type;    /* +0 */
    int variant; /* +4 */
};

typedef void (*DescriptorHandler)(int context, struct Descriptor *desc, int *a, int *b);

extern int DAT_004f5060[];
extern DescriptorHandler DAT_004f5088[][2];

int FUN_002a0bb8(void *obj, int code);

void FUN_002af070(struct Descriptor *desc, int *a, int *b) {
    int type = desc->type;
    int context = DAT_004f5060[type];
    DescriptorHandler handler = DAT_004f5088[type][desc->variant];

    if (handler == 0) {
        FUN_002a0bb8(0, 0xFF000221);
        *a = 0;
        *b = 1;
        return;
    }
    handler(context, desc, a, b);
}
