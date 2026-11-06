/* Runs the hook in D_00498c70 when +232 is set, releases the handle at +8 through FUN_0026f108 and
 * clears +4. */
typedef struct Rec25de68 {
    char pad0[4];
    int f4;             /* +4: cleared once the handle is released */
    void *handle;       /* +8 */
    char pad12[220];
    int hook_enabled;   /* +232 */
} Rec25de68;

extern void (*D_00498c70)(void);
void FUN_0026f108(void *handle);

void FUN_0025de68(Rec25de68 *rec) {
    if (rec->hook_enabled) {
        D_00498c70();
    }
    FUN_0026f108(rec->handle);
    rec->f4 = 0;
}
