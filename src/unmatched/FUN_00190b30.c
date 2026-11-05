typedef struct V { float f0; float f4; float f8; float f12; float f16; float f20; float f24; float f28; float f32; float f36; float f40; float f44; float f48; float f52; float f56; float f60; } V;
void FUN_00190b30(V *arg0, V *arg1) {
    { float t = arg1->f0; arg0->f0 = arg0->f0 + arg0->f12 * t; }
    { float t = arg1->f4; arg0->f4 = arg0->f4 + arg0->f12 * t; }
    { float t = arg1->f8; arg0->f8 = arg0->f8 + arg0->f12 * t; }
    { float t = arg1->f0; arg0->f16 = arg0->f16 + arg0->f28 * t; }
    { float t = arg1->f4; arg0->f20 = arg0->f20 + arg0->f28 * t; }
    { float t = arg1->f8; arg0->f24 = arg0->f24 + arg0->f28 * t; }
    { float t = arg1->f0; arg0->f32 = arg0->f32 + arg0->f44 * t; }
    { float t = arg1->f4; arg0->f36 = arg0->f36 + arg0->f44 * t; }
    { float t = arg1->f8; arg0->f40 = arg0->f40 + arg0->f44 * t; }
    { float t = arg1->f0; arg0->f48 = arg0->f48 + arg0->f60 * t; }
    { float t = arg1->f4; arg0->f52 = arg0->f52 + arg0->f60 * t; }
    { float t = arg1->f8; arg0->f56 = arg0->f56 + arg0->f60 * t; }
}
