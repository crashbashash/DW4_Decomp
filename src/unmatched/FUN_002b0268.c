/* Links 0x74-byte entry `from` to 0x44-byte entry `to` in both directions: entry44[to] (+7992)
 * records from, entry74[from] (+4952) records to. */

/* Views of the two entry tables as indexed from ctx; FUN_002ad828 follows the same links
 * (entry74 +4952 selects an entry44 of the table at ctx+7976). */
struct Entry44 {
    char pad[7992];
    int from;                             /* +16 within the entry at ctx+7976 */
};

struct Entry74 {
    char pad[4952];
    int to;                               /* index of the linked Entry44 */
};

void FUN_002b0268(char *ctx, int from, int to) {
    /* matching construct: manual — byte offsets in int temporaries keep ctx as the first addu operand */
    int off44 = to * 0x44;
    int off74 = from * 0x74;

    ((struct Entry44 *)(ctx + off44))->from = from;
    ((struct Entry74 *)(ctx + off74))->to = to;
}
