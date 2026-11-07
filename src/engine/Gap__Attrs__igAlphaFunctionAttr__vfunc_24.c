typedef struct { int pad[3]; volatile int a; float b; } S2;
void Gap__Gfx__igPsx2VisualContext__vfunc_219(int, int);
void Gap__Gfx__igPsx2VisualContext__vfunc_221(int, float);
void Gap__Attrs__igAlphaFunctionAttr__vfunc_24(S2* p, int q) { Gap__Gfx__igPsx2VisualContext__vfunc_219(q, p->a); Gap__Gfx__igPsx2VisualContext__vfunc_221(q, p->b); }
