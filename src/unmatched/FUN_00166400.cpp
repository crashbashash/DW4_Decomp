/* 0x00166400 - resets a visual context to its default render state (hypothesis: the
 * Gap::Core::igPsx2VisualContext "set defaults" entry; the flags select which state groups).
 * Evidence: every call is a virtual call through the context's vtable (lw t9,0(obj); lw t9,off(t9);
 * jalr), the registry lookups name "shadingMode", "cullEnable", "cullMode", "fillMode"
 * (strings at 0x4df0c8..0x4df0f8) and the texture-unit loop clamps vfunc_35(8) to 1..16.
 * Vtable entries are 4 bytes starting at +8, so slot N is at offset 8 + 4*N; slots are named by
 * index because the methods have no recovered names yet. Argument types follow the registers. */
struct Vec4 { float x, y, z, w; };

class igVisualContext {
public:
    virtual void vfunc_0(); virtual void vfunc_1(); virtual void vfunc_2(); virtual void vfunc_3();
    virtual void vfunc_4(); virtual void vfunc_5(); virtual void vfunc_6(); virtual void vfunc_7();
    virtual void vfunc_8(); virtual void vfunc_9(); virtual void vfunc_10(); virtual void vfunc_11();
    virtual void vfunc_12(); virtual void vfunc_13(); virtual void vfunc_14();
    virtual void vfunc_15(); virtual void vfunc_16(); virtual void vfunc_17();
    virtual void vfunc_18(); virtual void vfunc_19(); virtual void vfunc_20();
    virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23();
    virtual void vfunc_24(); virtual void vfunc_25(); virtual void vfunc_26();
    virtual void vfunc_27(); virtual void vfunc_28(); virtual void vfunc_29();
    virtual void vfunc_30(); virtual void vfunc_31(); virtual void vfunc_32();
    virtual void vfunc_33(); virtual void vfunc_34(); virtual int vfunc_35(int);
    virtual void vfunc_36(); virtual void vfunc_37(); virtual void vfunc_38();
    virtual void vfunc_39(); virtual void vfunc_40(); virtual void vfunc_41();
    virtual void vfunc_42(); virtual void vfunc_43(); virtual void vfunc_44();
    virtual void vfunc_45(); virtual void vfunc_46(); virtual void vfunc_47();
    virtual void vfunc_48(); virtual void vfunc_49(); virtual void vfunc_50();
    virtual void vfunc_51(); virtual void vfunc_52(); virtual void vfunc_53();
    virtual void vfunc_54(); virtual void vfunc_55(); virtual void vfunc_56();
    virtual void vfunc_57(); virtual void vfunc_58(); virtual void vfunc_59();
    virtual void vfunc_60(); virtual void vfunc_61(); virtual void vfunc_62();
    virtual void vfunc_63(const Vec4 *); virtual void vfunc_64(); virtual void vfunc_65();
    virtual void vfunc_66(); virtual void vfunc_67(const int *); virtual void vfunc_68();
    virtual void vfunc_69(); virtual void vfunc_70(); virtual void vfunc_71();
    virtual void vfunc_72(); virtual void vfunc_73(int); virtual void vfunc_74();
    virtual void vfunc_75(); virtual void vfunc_76(); virtual void vfunc_77();
    virtual void vfunc_78(); virtual void vfunc_79(); virtual void vfunc_80();
    virtual void vfunc_81(); virtual void vfunc_82(); virtual void vfunc_83();
    virtual void vfunc_84(); virtual void vfunc_85(); virtual void vfunc_86();
    virtual void vfunc_87(); virtual void vfunc_88(); virtual void vfunc_89();
    virtual void vfunc_90(); virtual void vfunc_91(); virtual void vfunc_92();
    virtual void vfunc_93(); virtual void vfunc_94(); virtual void vfunc_95();
    virtual void vfunc_96(float); virtual void vfunc_97(); virtual void vfunc_98(int);
    virtual void vfunc_99(); virtual void vfunc_100(const Vec4 *); virtual void vfunc_101();
    virtual void vfunc_102(const Vec4 *); virtual void vfunc_103();
    virtual void vfunc_104(const Vec4 *); virtual void vfunc_105();
    virtual void vfunc_106(const Vec4 *); virtual void vfunc_107(); virtual void vfunc_108(int);
    virtual void vfunc_109(); virtual void vfunc_110(); virtual void vfunc_111(int);
    virtual void vfunc_112(); virtual void vfunc_113(const Vec4 *); virtual void vfunc_114();
    virtual void vfunc_115(int, int); virtual void vfunc_116(); virtual void vfunc_117();
    virtual void vfunc_118(); virtual void vfunc_119(); virtual void vfunc_120();
    virtual void vfunc_121(); virtual void vfunc_122(); virtual void vfunc_123();
    virtual void vfunc_124(); virtual void vfunc_125(); virtual void vfunc_126();
    virtual void vfunc_127(); virtual void vfunc_128(); virtual void vfunc_129();
    virtual void vfunc_130(); virtual void vfunc_131(); virtual void vfunc_132();
    virtual void vfunc_133(); virtual void vfunc_134(); virtual void vfunc_135();
    virtual void vfunc_136(); virtual void vfunc_137(); virtual void vfunc_138();
    virtual void vfunc_139(); virtual void vfunc_140(); virtual void vfunc_141();
    virtual void vfunc_142(); virtual void vfunc_143(int); virtual void vfunc_144();
    virtual void vfunc_145(); virtual void vfunc_146(int, int); virtual void vfunc_147();
    virtual void vfunc_148(int, int, int); virtual void vfunc_149(); virtual void vfunc_150(int);
    virtual void vfunc_151(); virtual void vfunc_152(); virtual void vfunc_153();
    virtual void vfunc_154(); virtual void vfunc_155(); virtual void vfunc_156(int, int);
    virtual void vfunc_157(int); virtual void vfunc_158(); virtual void vfunc_159(int);
    virtual void vfunc_160(); virtual void vfunc_161(int); virtual void vfunc_162();
    virtual void vfunc_163(int, int, int); virtual void vfunc_164(); virtual void vfunc_165(int);
    virtual void vfunc_166(); virtual void vfunc_167(int); virtual void vfunc_168();
    virtual void vfunc_169(); virtual void vfunc_170(); virtual void vfunc_171();
    virtual void vfunc_172(); virtual void vfunc_173(); virtual void vfunc_174();
    virtual void vfunc_175(const Vec4 *); virtual void vfunc_176(); virtual void vfunc_177();
    virtual void vfunc_178(); virtual void vfunc_179(float); virtual void vfunc_180();
    virtual void vfunc_181(int); virtual void vfunc_182(); virtual void vfunc_183();
    virtual void vfunc_184(); virtual void vfunc_185(); virtual void vfunc_186();
    virtual void vfunc_187(); virtual void vfunc_188(int); virtual void vfunc_189();
    virtual void vfunc_190(); virtual void vfunc_191(); virtual void vfunc_192();
    virtual void vfunc_193(); virtual void vfunc_194(); virtual void vfunc_195();
    virtual void vfunc_196(); virtual void vfunc_197(); virtual void vfunc_198();
    virtual void vfunc_199(); virtual void vfunc_200(); virtual void vfunc_201();
    virtual void vfunc_202(); virtual void vfunc_203(); virtual void vfunc_204();
    virtual void vfunc_205(); virtual void vfunc_206(); virtual void vfunc_207(int, int);
    virtual void vfunc_208(); virtual void vfunc_209(int); virtual void vfunc_210();
    virtual void vfunc_211(); virtual void vfunc_212(); virtual void vfunc_213();
    virtual void vfunc_214(); virtual void vfunc_215(int); virtual void vfunc_216();
    virtual void vfunc_217(int); virtual void vfunc_218(); virtual void vfunc_219(float);
    virtual void vfunc_220(); virtual void vfunc_221(int); virtual void vfunc_222();
    virtual void vfunc_223(int, int, int, int); virtual void vfunc_224();
    virtual void vfunc_225(int); virtual void vfunc_226(); virtual void vfunc_227(int);
    virtual void vfunc_228(); virtual void vfunc_229(int); virtual void vfunc_230();
    virtual void vfunc_231(int); virtual void vfunc_232(); virtual void vfunc_233(int);
    virtual void vfunc_234(); virtual void vfunc_235(int); virtual void vfunc_236();
    virtual void vfunc_237(int); virtual void vfunc_238(); virtual void vfunc_239(int);
    virtual void vfunc_240(); virtual void vfunc_241(float); virtual void vfunc_242();
    virtual void vfunc_243(int); virtual void vfunc_244(); virtual void vfunc_245(const Vec4 *);
    virtual void vfunc_246(); virtual void vfunc_247(float); virtual void vfunc_248();
    virtual void vfunc_249(float); virtual void vfunc_250(); virtual void vfunc_251();
    virtual void vfunc_252(); virtual void vfunc_253(); virtual void vfunc_254();
    virtual void vfunc_255(); virtual void vfunc_256(); virtual void vfunc_257();
    virtual void vfunc_258(); virtual void vfunc_259(int, int);
};

extern "C" {
/* registry lookups: (settings, type 4, key, out, default, flag) */
void thunk_FUN_003065f0(void *settings, int type, const char *key, int *out, int dflt, int flag);
void thunk_FUN_00306e50(void *settings, int type, const char *key, unsigned char *out, int dflt, int flag);
extern char DAT_004df0c8[]; /* "shadingMode" */
extern char DAT_004df0d8[]; /* "cullEnable" */
extern char DAT_004df0e8[]; /* "cullMode" */
extern char DAT_004df0f8[]; /* "fillMode" */
struct SystemConfig { char pad[56]; void *settings; };
extern SystemConfig *DAT_00586dc8[4]; /* array form keeps the access out of small data */
void FUN_00166400(igVisualContext *ctx, int flags);
}

void FUN_00166400(igVisualContext *ctx, int flags)
{
    void *settings = DAT_00586dc8[0]->settings;
    int shadingMode;
    int cullMode;
    int fillMode;
    unsigned char cullEnable;
    int i, n;
    Vec4 clear, white, tint, ambient, diffuse, specular, lightDir, colour;
    int hot;

    if (flags & 1) {
        ctx->vfunc_73(0);
        ctx->vfunc_111(0);
        clear.x = 0.0f; clear.y = 0.0f; clear.z = 0.0f; clear.w = 0.0f;
        ctx->vfunc_113(&clear);
    }
    if (flags & 2) {
        white.x = 1.0f; white.y = 1.0f; white.z = 1.0f; white.w = 1.0f;
        ctx->vfunc_63(&white);
        ctx->vfunc_96(0.0f);
        tint.x = 1.0f; tint.y = 1.0f; tint.z = 1.0f; tint.w = 1.0f;
        ctx->vfunc_100(&tint);
        ambient.x = 0.0f; ambient.y = 0.0f; ambient.z = 0.0f; ambient.w = 1.0f;
        ctx->vfunc_102(&ambient);
        diffuse.x = 0.0f; diffuse.y = 0.0f; diffuse.z = 0.0f; diffuse.w = 1.0f;
        ctx->vfunc_104(&diffuse);
        specular.x = 0.0f; specular.y = 0.0f; specular.z = 0.0f; specular.w = 1.0f;
        ctx->vfunc_106(&specular);
        ctx->vfunc_108(1);
        ctx->vfunc_98(0);
    }
    if (flags & 4) {
        n = ctx->vfunc_35(8);
        if (n > 512) n = 1;
        if (n > 16) n = 16;
        n = (n <= 0) ? 1 : n; /* ternary form: the if form schedules the loop init into the bgtz delay slot */
        i = 0;
        while (i < n) {
            ctx->vfunc_115(i, 0);
            ctx->vfunc_146(i, 1);
            ctx->vfunc_148(i, 0, 0);
            ctx->vfunc_207(i, 0);
            i++;
        }
    }
    if (flags & 8) {
        ctx->vfunc_150(0);
        ctx->vfunc_156(4, 5);
    }
    if (flags & 0x80) {
        ctx->vfunc_157(0);
        ctx->vfunc_159(0);
        ctx->vfunc_161(7);
        ctx->vfunc_165(-1);
        ctx->vfunc_167(-1);
        ctx->vfunc_163(0, 0, 0);
    }
    if (flags & 0x10) {
        ctx->vfunc_239(0);
        ctx->vfunc_241(0.0f);
        ctx->vfunc_243(2);
        lightDir.x = 0.0f; lightDir.y = 0.0f; lightDir.z = 0.0f; lightDir.w = 1.0f;
        ctx->vfunc_245(&lightDir);
        ctx->vfunc_247(1.0f);
        ctx->vfunc_249(1000.0f);
    }
    if (flags & 0x20) {
        thunk_FUN_003065f0(settings, 4, DAT_004df0c8, &shadingMode, 1, 1);
        hot = -1;
        ctx->vfunc_67(&hot);
        colour.x = 0.0f; colour.y = 0.0f; colour.z = 0.0f; colour.w = 1.0f;
        ctx->vfunc_175(&colour);
        ctx->vfunc_179(1.0f);
        ctx->vfunc_181(0);
        ctx->vfunc_209(0);
        ctx->vfunc_221(1);
        ctx->vfunc_223(1, 1, 1, 1);
        ctx->vfunc_225(shadingMode);
    }
    if (flags & 0x40) {
        thunk_FUN_00306e50(settings, 4, DAT_004df0d8, &cullEnable, 0, 1);
        thunk_FUN_003065f0(settings, 4, DAT_004df0e8, &cullMode, 0, 1);
        thunk_FUN_003065f0(settings, 4, DAT_004df0f8, &fillMode, 0, 1);
        ctx->vfunc_215(0);
        ctx->vfunc_217(6);
        ctx->vfunc_219(0.0f);
        ctx->vfunc_227(cullEnable);
        ctx->vfunc_229(cullMode);
        ctx->vfunc_231(1);
        ctx->vfunc_233(3);
        ctx->vfunc_235(1);
        ctx->vfunc_237(fillMode);
        ctx->vfunc_143(0);
        ctx->vfunc_188(0);
        ctx->vfunc_259(0, 0);
        for (i = 1; i < 16; i++)
            ctx->vfunc_259(0, i);
    }
}
