#include "dw4/igSmartPointer.h"

extern "C" {
int FUN_001c66c0(void *, int);
int FUN_00306770(int, int, const char *, void *, int *, int);
extern int DAT_004e4660[4];
}
struct ShaderObject : public igObject { };
struct Factory { char pad32[32]; int f32; int f36; int f40; };

extern "C" igSmartPointer<ShaderObject> Gap__Sg__igIniShaderFactory__vfunc_24(Factory *self, const char *name) {
    igSmartPointer<ShaderObject> shader(0, kRetainReference);
    if (FUN_001c66c0(self, 0) == 0) {
        return igSmartPointer<ShaderObject>(0, kRetainReference);
    }
    if (FUN_00306770(self->f32, self->f40, name, &shader.p, &DAT_004e4660[0], 0) == 0) {
        return igSmartPointer<ShaderObject>(0, kRetainReference);
    }
    return shader;
}
