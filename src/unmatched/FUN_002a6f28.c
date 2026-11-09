typedef struct AudStateDesc {
    int w[6];
    int f24;
    int f28;
} AudStateDesc;

typedef struct AudStateState {
    int done;
    AudStateDesc desc;
    int a;
    int b;
} AudStateState;

typedef struct AudStateObj {
    char pad[3428];
    AudStateState state;
    char pad3472[92];
    AudStateDesc src2;
    char pad3596[52];
    AudStateState state2;
} AudStateObj;

int FUN_002a6308(AudStateObj *obj, int id);
int FUN_002a64c0(AudStateObj *obj, int id);
void FUN_002af070(AudStateDesc *desc, int *a, int *b);

void FUN_002a6f28(AudStateObj *obj)
{
    AudStateState *state2 = &obj->state2;
    AudStateState *state = &obj->state;
    AudStateDesc desc;
    int a, b;

    if (state2->done != 0)
        return;
    desc = obj->src2;
    if (FUN_002a6308(obj, 3) == 0 && FUN_002a64c0(obj, 3) == 0)
        desc.f24 = 0;
    FUN_002af070(&desc, &a, &b);
    state2->desc = desc;
    state2->a = a - state->a;
    state2->b = b;
    state2->done = 1;
}
