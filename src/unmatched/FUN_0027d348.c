/* Returns the number of nodes queued on one lane of a handle (linked list at +24 + 4 * lane); null
 * and unused handles are reported through SJERR_CallErr and return 0. */
struct Node27d {
    struct Node27d *next;   /* +0 */
};

struct Handle27d {
    int f0;
    signed char used;           /* +4 */
    char pad5[19];
    struct Node27d *lanes[4];   /* +24 */
};

extern void SJERR_CallErr(const char *message);
extern const char E2004090279_NULL_pointer_is_specified[];
extern const char E2004090280_Specified_handle_is_invalid[];

int FUN_0027d348(struct Handle27d *handle, int lane) {
    struct Node27d *node;
    int count;

    if (handle == 0) {
        SJERR_CallErr(E2004090279_NULL_pointer_is_specified);
        return 0;
    }
    if (handle->used == 0) {
        SJERR_CallErr(E2004090280_Specified_handle_is_invalid);
        return 0;
    }
    count = 0;
    for (node = handle->lanes[lane]; node != 0; node = node->next) {
        count++;
    }
    return count;
}
