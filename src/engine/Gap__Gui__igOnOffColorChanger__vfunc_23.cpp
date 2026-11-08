struct OnOffColorState { unsigned char pad[12]; bool enabled; bool on; unsigned char pad2; bool hilite; unsigned char pad3[20]; bool current; };
extern "C" int Gap__Gui__igOnOffColorChanger__vfunc_23(int arg0, OnOffColorState *s);
int Gap__Gui__igOnOffColorChanger__vfunc_23(int arg0, OnOffColorState *s) { int n; bool t, f; if (!s->enabled) return arg0 + 0x48; t = s->on; n = 0; if (t) n += 1; f = s->hilite && t; if (s->current ^ f) n += 2; return arg0 + n * 0x10 + 8; }
