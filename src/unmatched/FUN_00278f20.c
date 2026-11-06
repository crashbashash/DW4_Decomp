/* 0x00278f20 — FUN_00278f20 (308 bytes). Attaches Dolby Pro Logic II processing (per its error strings) to an ADXT handle with at least two channels (+3): resets it (FUN_0026bc60, FUN_00279058), installs the FUN_00279200 hook (FUN_00278640) and clears FUN_002786c8, creates the processor with FUN_00278780(a, b) and binds it to the renderer state (+4 then +4: words +232/+236/+240) via FUN_00278d58, then installs the four FUN_00279128/2791b0/279198/2791e8 callbacks and calls FUN_00265080. Failures are reported through FUN_002607e8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Renderer_278f20 {
    char pad0[232];
    void *stream;   /* 0xe8 */
    int f236;     /* 0xec */
    int f240;     /* 0xf0 */
} Renderer_278f20;

typedef struct Source_278f20 {
    int pad0;
    Renderer_278f20 *renderer;  /* 0x04 */
} Source_278f20;

typedef struct Adxt_278f20 {
    signed char pad0[3];
    signed char channels;       /* 0x03 */
    Source_278f20 *source;      /* 0x04 */
} Adxt_278f20;

extern char E2003091101_ADXT_handle_must_be_created_for_stereo_output[]; /* 'E2003091101 : ADXT handle must be created for stereo output.' */
extern char E2003091002_Fail_to_attach_Dolby_Pro_Logic_II[]; /* 'E2003091002 : Fail to attach Dolby Pro Logic II.' */
extern void *DAT_004a8e68;
extern void *DAT_00498c6c;
extern void *DAT_00498c70;
extern void *DAT_004a52d0;
void FUN_002607e8(const char *message);
void FUN_0026bc60(Adxt_278f20 *adxt);
void FUN_00279058(Adxt_278f20 *adxt);
void FUN_00278640(void (*hook)(), int arg);
void FUN_00279200();
void FUN_002786c8(int arg);
void FUN_00265068(void);
void *FUN_00278780(int a, int b);
void FUN_00278d58(void *stream, int a, int b);
void FUN_00279128();
void FUN_002791b0();
void FUN_00279198();
void FUN_002791e8();
void FUN_00265080(void);

void FUN_00278f20(Adxt_278f20 *adxt, int a, int b) {
    Renderer_278f20 *renderer;
    void *stream;

    if (adxt->channels < 2) {
        FUN_002607e8(E2003091101_ADXT_handle_must_be_created_for_stereo_output);
        return;
    }
    FUN_0026bc60(adxt);
    FUN_00279058(adxt);
    FUN_00278640(FUN_00279200, 0);
    FUN_002786c8(0);
    renderer = adxt->source->renderer;
    FUN_00265068();
    stream = FUN_00278780(a, b);
    if (stream == 0) {
        FUN_002607e8(E2003091002_Fail_to_attach_Dolby_Pro_Logic_II);
        return;
    }
    FUN_00278d58(stream, renderer->f236, renderer->f240);
    renderer->stream = stream;
    DAT_004a8e68 = FUN_00279128;
    DAT_00498c6c = FUN_002791b0;
    DAT_00498c70 = FUN_00279198;
    DAT_004a52d0 = FUN_002791e8;
    FUN_00265080();
}

