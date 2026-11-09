class TextureImage {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void setPixels(void *pixels, int format, int quality, int width, int height);
    char pad4[44];
    int f48;
    void *pixels;
};

class BufferAllocator {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void *allocate(int size, int align);
};

struct TextureEntry { char pad0[8]; int depth; int pad12; int indexed; char pad20[8]; int kind; char pad32[4]; int palette; int layout; char pad44[4]; };
struct TextureTable { char pad0[16]; TextureEntry *entries; };
struct PaletteEntry { int format; char pad4[132]; };
struct PaletteTable { char pad0[16]; PaletteEntry *entries; };
struct VisualContextTextures { char pad0[324]; PaletteTable *palettes; char pad328[540]; TextureTable *textures; };
extern "C" {
BufferAllocator *FUN_00165cf0(VisualContextTextures *self);
void FUN_00203c50(void *source, int sourceFormat, int width, int height, int layout, void *pixels, int flags);
void FUN_00203580(void *source, int sourceFormat, int width, int height, int layout, void *pixels, int flags);
void FUN_0015a530(TextureImage *image, void *pixels, int format, int width, int height);
void Memory_FreeBuffer(void *);
/* matching construct: a small sweep of spellings */
int FUN_00169e40(VisualContextTextures *self, int index, TextureImage *image, void *source, int sourceFormat, int width, int height, int flags);
}
int FUN_00169e40(VisualContextTextures *self, int index, TextureImage *image, void *source, int sourceFormat, int width, int height, int flags) {
    void *pixels;
    TextureEntry *entry;
    entry = &self->textures->entries[index];
    pixels = image->pixels;
    bool allocated = false;
    int format;
    if (pixels == 0 || image->f48 < 0 || ((int)pixels & 15) != 0) {
        pixels = FUN_00165cf0(self)->allocate(width * height * 4, 16);
        allocated = true;
    }
    if (entry->kind == 2) {
        FUN_00203c50(source, sourceFormat, width, height, entry->layout, pixels, flags);
        format = self->palettes->entries[entry->palette].format;
    } else {
        FUN_00203580(source, sourceFormat, width, height, 1, pixels, flags);
        if (entry->depth == 32) {
            format = 7;
        } else if (entry->depth == 24) {
            if (entry->indexed) {
                format = 7;
            } else {
                format = 5;
            }
        } else if (entry->depth == 15 || entry->depth == 16) {
            format = 8;
        } else {
            format = 7;
        }
    }
    if (allocated) {
        image->setPixels(pixels, format, 100, width, height);
        Memory_FreeBuffer(pixels);
    } else {
        FUN_0015a530(image, pixels, format, width, height);
    }
    return 1;
}
