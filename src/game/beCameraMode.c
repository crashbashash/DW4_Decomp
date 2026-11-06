#include "dw4/reflected.h"
extern int g_beCameraMode_metaObject[4];
int FUN_004577f0(int, void *);
int Gap__Core__igObject__vfunc_08__002ff0f0(void *);

int Gap__Bec__beCameraMode__vfunc_20(void)
{
    return g_beCameraMode_metaObject[0];
}

/* Slot 23: empty body. */
void Gap__Bec__beCameraMode__vfunc_23(void)
{
}

/* Slot 24: empty body. */
void Gap__Bec__beCameraMode__vfunc_24(void)
{
}

/* Slot 25: empty body. */
void Gap__Bec__beCameraMode__vfunc_25(void)
{
}

/* Slot 26: empty body. */
void Gap__Bec__beCameraMode__vfunc_26(void)
{
}

/* Slot 27: empty body. */
void Gap__Bec__beCameraMode__vfunc_27(void)
{
}

/* Teardown slot (the slot the other classes' teardown bodies also chain from to the igObject
 * base): if the mode still has its _model, FUN_004577f0 detaches the mode from it (it nulls the
 * mode's entry in the model's list at +8), then the base igObject teardown runs. */
void Gap__Bec__beCameraMode__vfunc_08(beCameraMode *self) {
    int model;

    model = self->_model;
    if (model != 0) {
        FUN_004577f0(model, self);
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(self);
}
