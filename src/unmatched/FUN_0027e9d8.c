int FUN_0027e398();
extern char DAT_004f26a0[];
extern char DAT_004f26c8[];

typedef struct {
    int (*func)(int);
    int arg;
} Callback;

extern Callback DAT_005709e0[][6];

int FUN_0027e9d8(int id, unsigned int kind)
{
    int result;
    Callback *cb;

    result = 0;
    if (kind >= 6) {
        FUN_0027e398(DAT_004f26a0);
    }
    if (id < 0 || (int)kind >= 8) {
        FUN_0027e398(DAT_004f26c8);
    }
    cb = &DAT_005709e0[id][kind];
    if (cb->func != 0) {
        result = cb->func(cb->arg);
    }
    return result;
}
