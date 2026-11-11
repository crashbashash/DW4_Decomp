int Gap__Gui__igOnOffColorChanger__vfunc_23(int arg0, OnOffColorState *s) { int n; bool t, f; if (!s->enabled) return arg0 + 0x48; t = s->on; n = 0; if (t) n += 1; f = s->hilite && t; if (s->current ^ f) n += 2; return arg0 + n * 0x10 + 8; }

void thunk_FUN_00453a40(igBasicColorChanger *arg0, int arg1, int arg2, int arg3, void *arg4)
{
    FUN_00453a40(arg0, arg1, arg2, arg3, arg4);
}

void FUN_00453b90(float *out, A *a) {
    B *b = a->b;
    float z0 = 0.0f, two = 2.0f; float dx = a->dx, dy = a->dy; float x = b->x, y = b->y, z = b->z; x += two * dx; y += two * dy; z += z0; out[0] = x; out[1] = y; out[2] = z;
}

