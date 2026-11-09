typedef struct P2ModeState {
    char pad0[70];
    signed char mode : 7;
    unsigned char top : 1;
} P2ModeState;

void FUN_002084a0(P2ModeState *s)
{
    const P2ModeState *view = s;

    if (view->mode == 2)
        s->mode = 3;
}
