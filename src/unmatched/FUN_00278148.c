/* Releases a buffer: clears its busy byte (FUN_00278410) and, if it was in use, clears the in-use
 * byte and frees it through FUN_00278018. */
struct Buffer278 {
    signed char used;     /* +0 */
};

extern void FUN_00278410(struct Buffer278 *buffer);
extern void FUN_00278018(struct Buffer278 *buffer);

/* matching construct: hand search — int return type with no return value (implicit-int style); a void
   return type lets GCC turn the last call into a sibling call */
int FUN_00278148(struct Buffer278 *buffer) {
    if (buffer != 0) {
        FUN_00278410(buffer);
        if (buffer->used == 1) {
            buffer->used = 0;
            FUN_00278018(buffer);
        }
    }
}
