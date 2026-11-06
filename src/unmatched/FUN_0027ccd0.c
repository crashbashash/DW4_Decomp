/* 0x0027ccd0 — FUN_0027ccd0 (164 bytes). Returns the total size queued on one of the four lanes of a handle
   (sum of +12 over the lane's linked list at +24 + 4 * lane); an out-of-range lane is reported through the
   handle's error callback (+40, context +44, code -3) and returns 0. Null and unused handles are reported
   through FUN_0027b2e0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Node27c {
    struct Node27c *next;   /* +0 */
    int f4;
    int f8;
    int size;               /* +12 */
};

struct Handle27c {
    int f0;
    signed char used;                         /* +4 */
    char pad5[19];
    struct Node27c *lanes[4];                 /* +24 */
    void (*error_callback)(int context, int code);   /* +40 */
    int error_context;                        /* +44 */
};

extern void FUN_0027b2e0(const char *message);
extern const char E2004090269_NULL_pointer_is_specified[];
extern const char E2004090270_Specified_handle_is_invalid[];

int FUN_0027ccd0(struct Handle27c *handle, unsigned int lane) {
    struct Node27c *node;
    int total;

    if (handle == 0) {
        FUN_0027b2e0(E2004090269_NULL_pointer_is_specified);
        return 0;
    }
    if (handle->used == 0) {
        FUN_0027b2e0(E2004090270_Specified_handle_is_invalid);
        return 0;
    }
    if (lane >= 4) {
        if (handle->error_callback != 0) {
            handle->error_callback(handle->error_context, -3);
        }
        return 0;
    }
    total = 0;
    for (node = handle->lanes[lane]; node != 0; node = node->next) {
        total += node->size;
    }
    return total;
}
