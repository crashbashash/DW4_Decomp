typedef struct AudInitDesc {
    int w[6];
    int f24;
    int f28;
} AudInitDesc;

typedef struct AudInitState {
    int done;
    AudInitDesc desc;
    int a;
    int b;
} AudInitState;

typedef struct AudInitObj {
    char pad[3396];
    AudInitDesc src;
    AudInitState state;
} AudInitObj;

void FUN_002af070(AudInitDesc *desc, int *a, int *b);

void FUN_002a5b48(AudInitObj *obj)
{
    AudInitState *state = &obj->state;
    AudInitDesc desc;
    int a, b;

    if (state->done != 0)
        return;
    desc = obj->src;
    desc.f24 = 0;
    FUN_002af070(&desc, &a, &b);

    state->desc = desc;
    state->a = a;
    state->b = b;
    state->done = 1;

}
