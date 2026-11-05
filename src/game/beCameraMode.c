/* src/game/beCameraMode.c — the beCameraMode methods
 *
 * One translation unit: 7 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern int g_beCameraMode_metaObject_00589b90[4];
int FUN_004577f0(int, void *);
int Gap__Core__igObject__vfunc_08__002ff0f0(void *);

/* 0x0037aa60 — class MetaObject accessor: slot 0 of the published
 * beCameraMode MetaObject handle at 0x589b90. */
int Gap__Bec__beCameraMode__vfunc_20(void)
{
    return g_beCameraMode_metaObject_00589b90[0];
}

/* 0x0037aa70 — slot 23: empty body. */
void Gap__Bec__beCameraMode__vfunc_23(void)
{
}

/* 0x0037aa80 — slot 24: empty body. */
void Gap__Bec__beCameraMode__vfunc_24(void)
{
}

/* 0x0037aa90 — slot 25: empty body. */
void Gap__Bec__beCameraMode__vfunc_25(void)
{
}

/* 0x0037aaa0 — slot 26: empty body. */
void Gap__Bec__beCameraMode__vfunc_26(void)
{
}

/* 0x0037aab0 — slot 27: empty body. */
void Gap__Bec__beCameraMode__vfunc_27(void)
{
}

/* 0x00457ef0 — teardown slot (vfunc_08, the slot the other classes' teardown bodies also
 * chain from to the igObject base): if the mode still has its _model, FUN_004577f0
 * detaches the mode from it (it nulls the mode's entry in the model's list at +8), then
 * the base igObject teardown runs. */
void Gap__Bec__beCameraMode__vfunc_08(beCameraMode *self) {
    int model;

    model = self->_model;
    if (model != 0) {
        FUN_004577f0(model, self);
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(self);
}
