/* 0x002784d0 — FUN_002784d0 (124 bytes). Changes a handle's unit size (+4): recomputes the unit count of the total (+8, rounded up) at +12, rescales the position (+16) to the new unit and sets +20 to +24 units; a NULL handle is reported through FUN_00277de8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Handle_2784d0 {
    int pad0;
    int unit;       /* 0x04 */
    int total;      /* 0x08 */
    int units;      /* 0x0c: total in units, rounded up */
    int position;   /* 0x10: in units */
    int limit;      /* 0x14 */
    int count;      /* 0x18 */
} Handle_2784d0;

extern char E0040302_handl_is_null[]; /* 'E0040302:handl is null.' */
void FUN_00277de8(Handle_2784d0 *handle, const char *message);

void FUN_002784d0(Handle_2784d0 *handle, int unit) {
    int old_unit;
    int position;

    if (handle == 0) {
        FUN_00277de8(handle, E0040302_handl_is_null);
        return;
    }
    position = handle->position;
    old_unit = handle->unit;
    handle->unit = unit;
    handle->units = (handle->total + unit - 1) / unit;
    handle->position = position * old_unit / unit;
    handle->limit = handle->count * unit;
}

