typedef struct ViewerAxisState {
    char pad0[88];
    float f88;
    float f92;
    float f96;
    float f100;
    float f104;
} ViewerAxisState;

void FUN_00465880(ViewerAxisState *s, int unused, unsigned short axis, float x, float y)
{
    if (axis == 0) {
        s->f100 = x;
        s->f104 = y;
    } else if (axis == 1) {
        s->f88 = -x;
        s->f92 = 0.0f;
        s->f96 = y;
    }
}
