/* Sets the first word (+0) of 0x44-byte entry 8 to 1 through FUN_002b0388 when sftrn_GetFlagA reads
 * it as not 1, FUN_0029ea48(obj, obj+8536) reports 1 and FUN_002b1268 agrees. */
int FUN_0029ea48();
int FUN_002b0388();
int sftrn_GetFlagA();
int FUN_002b1268();

struct EntryOwner {
    char pad[8400];
    int f8400;                            /* +8400 (0x20D0): argument for entry 6 */
    char pad8404[8536 - 8404];
    int f8536;                            /* +8536 (0x2158): argument for entry 8 */
};

void FUN_002b11e8(struct EntryOwner *obj) {
    if (sftrn_GetFlagA(obj, 8) != 1 && FUN_0029ea48(obj, obj->f8536) == 1 && FUN_002b1268(obj) != 0) {
        FUN_002b0388(obj, 8, 1);
    }
}
