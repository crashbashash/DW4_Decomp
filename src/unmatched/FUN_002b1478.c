/* Sets the state word (+4) of 0x44-byte entry 6 to 1 through FUN_002b03b8 when sftrn_GetFlagB reads
 * it as not 1, FUN_0029ea88(obj, obj+8400) reports 1 and FUN_002b14f8 agrees. */
int FUN_0029ea88();
int FUN_002b03b8();
int sftrn_GetFlagB();
int FUN_002b14f8();

struct EntryOwner {
    char pad[8400];
    int f8400;                            /* +8400 (0x20D0): argument for entry 6 */
    char pad8404[8536 - 8404];
    int f8536;                            /* +8536 (0x2158): argument for entry 8 */
};

void FUN_002b1478(struct EntryOwner *obj) {
    if (sftrn_GetFlagB(obj, 6) != 1 && FUN_0029ea88(obj, obj->f8400) == 1 && FUN_002b14f8(obj) != 0) {
        FUN_002b03b8(obj, 6, 1);
    }
}
