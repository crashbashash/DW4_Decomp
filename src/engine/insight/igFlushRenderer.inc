igMetaObject *g_igFlushRenderer_metaObject;
struct FlushShared *g_viewerOptions;

igMetaObject *FUN_00233a40(void) {
    if (g_igFlushRenderer_metaObject == 0) {
        g_igFlushRenderer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igFlushRenderer_metaObject;
}

/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
igMetaObject *igFlushRenderer_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igFlushRenderer_metaObject != 0) {
        ready = (g_igFlushRenderer_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00233b80();
done:
    return g_igFlushRenderer_metaObject;
}

int igFlushRenderer_GetVTable(void) {
    union U_233a90 u;
    int temp_s0;
    S_ref *q1;


    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0052d060[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&g_igFlushRenderer_vtable[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0052d060[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void FUN_00233b80(void)
{
    igMetaObject_RunStaticInit(igFlushRenderer_Register);
}

void igFlushRenderer_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFlushRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igFlushRenderer_GetMetaObject,
        "igFlushRenderer",
        0xC, /* instance size */
        igFlushRenderer_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igFlushRenderer_GetMetaObject(void) {
    igFlushRenderer_GetMetaObject();
}

static inline int countOf(const IntList *list) { return list->count; }

/* The Alchemy viewer's usage / option help printer: prints the banner and then one help entry per
 * command-line option (name, description and default value) through five typed helpers (bool, int,
 * float, vec3, vec4) that format the entry with printf. Each entry is guarded by `if (name)`: the
 * literal's address is tested against zero, so the guard comes from the option macro, not from the
 * data. Argument: the program name for the USAGE line. */




void FUN_00233c10(const char *programName)
{
    /* matching construct: variant search — declaration order of the local arrays; b52 gives the first-declared array the highest stack slot */
    float defaultUpVector[3];
    float defaultNormalsColor[4];
    float defaultInvalidNormalsColor[4];
    float defaultScaledNormalsColor[4];
    float defaultHeadLightDiffuse[4];
    float defaultHeadLightSpecular[4];
    float defaultHeadLightAmbient[4];
    float defaultClearColor[4];
    printf("USAGE: %s [option1 [option2 ...]] [[-n number] filename1] [[-n number] filename2 ...]\n\n", programName);
    printf("-n number\n\tloads n instances of the next file\n\n");
    printf("Possible options are :\n");
    printf("--help\n\tPrints this message.\n\n");
    printf("--nologo\n\tremoves the logo display\n\n");
    OPTION_BOOL("--show-bbox", "show bounding box on selected object", 1);
    OPTION_BOOL("--show-normals", "show normals on selected object", 0.0f);
    {
        const char *optionName = "--normals-color";
        if (optionName) {
            defaultNormalsColor[0] = 0.0f;
            defaultNormalsColor[1] = 1.0f;
            defaultNormalsColor[2] = 0.0f;
            defaultNormalsColor[3] = 1.0f;
            FUN_002343d0(optionName, "sets the normals color", defaultNormalsColor);
        }
    }
    {
        const char *optionName = "--invalid-stored-normals-color";
        if (optionName) {
            defaultInvalidNormalsColor[0] = 1.0f;
            defaultInvalidNormalsColor[1] = 0.5f;
            defaultInvalidNormalsColor[2] = 0.0f;
            defaultInvalidNormalsColor[3] = 1.0f;
            FUN_002343d0(optionName, "sets the non-normalized stored normals color", defaultInvalidNormalsColor);
        }
    }
    {
        const char *optionName = "--scaled-normals-color";
        if (optionName) {
            defaultScaledNormalsColor[0] = 1.0f;
            defaultScaledNormalsColor[1] = 0.0f;
            defaultScaledNormalsColor[2] = 0.0f;
            defaultScaledNormalsColor[3] = 1.0f;
            FUN_002343d0(optionName, "sets the scaled normals color", defaultScaledNormalsColor);
        }
    }
    OPTION_FLOAT("--invalid-normals-precision", "sets the precision on the normals norm", 0.00100000005f);
    OPTION_BOOL("--auto-select-camera", "select the first camera if any in the scene", 1);
    OPTION_FLOAT("--hfov", "sets the horizontal field of view", 45.0f);
    OPTION_BOOL("--auto-planes", "find automatically near and far clipping planes", 1);
    OPTION_FLOAT("--near-plane", "sets the default near clipping plane", 0.100000001f);
    OPTION_FLOAT("--far-plane", "sets the default far clipping plane", 1000.0f);
    {
        const char *optionName = "--up-vector";
        if (optionName) {
            defaultUpVector[0] = g_vec3Zero[0];
            defaultUpVector[1] = g_vec3Zero[1];
            defaultUpVector[2] = g_vec3Zero[2];
            FUN_00234350(optionName, "sets the default up vector (<0,0,0> means use scene up vector)", defaultUpVector);
        }
    }
    OPTION_BOOL("--auto-scene-lights", "sets automatic usage of scene lights", 1);
    OPTION_BOOL("--auto-head-light", "sets automatic usage of head light", 0.0f);
    OPTION_BOOL("--use-scene-lights", "use scene lights (if not automatic)", 0.0f);
    OPTION_BOOL("--use-head-light", "enable head light (if not automatic)", 0.0f);
    OPTION_BOOL("--use-head-light-specular", "use specular head light", 0.0f);
    {
        const char *optionName = "--head-light-diffuse";
        if (optionName) {
            defaultHeadLightDiffuse[0] = 1.0f;
            defaultHeadLightDiffuse[1] = 1.0f;
            defaultHeadLightDiffuse[2] = 1.0f;
            defaultHeadLightDiffuse[3] = 1.0f;
            FUN_002343d0(optionName, "sets the diffuse color for the head light", defaultHeadLightDiffuse);
        }
    }
    {
        const char *optionName = "--head-light-specular";
        if (optionName) {
            defaultHeadLightSpecular[0] = 1.0f;
            defaultHeadLightSpecular[1] = 1.0f;
            defaultHeadLightSpecular[2] = 1.0f;
            defaultHeadLightSpecular[3] = 1.0f;
            FUN_002343d0(optionName, "sets the specular color for the head light", defaultHeadLightSpecular);
        }
    }
    {
        const char *optionName = "--head-light-ambient";
        if (optionName) {
            defaultHeadLightAmbient[0] = g_vec4Zero[0];
            defaultHeadLightAmbient[1] = g_vec4Zero[1];
            defaultHeadLightAmbient[2] = g_vec4Zero[2];
            defaultHeadLightAmbient[3] = g_vec4Zero[3];
            FUN_002343d0(optionName, "sets the ambient color for the head light", defaultHeadLightAmbient);
        }
    }
    {
        const char *optionName = "--clear-color";
        if (optionName) {
            defaultClearColor[0] = 0.200000003f;
            defaultClearColor[1] = 0.200000003f;
            defaultClearColor[2] = 0.200000003f;
            defaultClearColor[3] = 1.0f;
            FUN_002343d0(optionName, "sets the clear color", defaultClearColor);
        }
    }
    OPTION_BOOL("--wireframe-mode", "sets wireframe mode", 0.0f);
    OPTION_BOOL("--force-wireframe", "force wireframe on all geometries", 0.0f);
    OPTION_BOOL("--backface-culling-mode", "sets back-face culling mode", 0.0f);
    OPTION_BOOL("--force-backface-culling", "force back-face culling on all geometries", 0.0f);
    OPTION_BOOL("--alpha-test", "sets alpha test state", 0.0f);
    OPTION_BOOL("--force-alpha-test", "force alpha test on all geometries", 0.0f);
    OPTION_FLOAT("--alpha-test-reference", "sets alpha test reference value", 0.100000001f);
    OPTION_FLOAT("--maximum-frame-rate", "sets the maximum frame rate (0 means no maximum)", 0.0f);
    OPTION_BOOL("--optimize-textures", "share textures at load time", 1);
    OPTION_BOOL("--half-buffer", "sets PSX2 half-buffer mode", 0.0f);
    OPTION_BOOL("--pal-video-mode", "sets PAL video mode", 0.0f);
    OPTION_INT("--width", "viewer window width", 640);
    OPTION_INT("--height", "viewer window height", 448);
    OPTION_INT("--swap-interval", "sets the swap interval (0 means no vsync)", 0.0f);
    OPTION_INT("--color-bits", "sets color buffer bits (-1 means default)", -1);
    OPTION_INT("--alpha-bits", "sets alpha buffer bits (-1 means default)", -1);
    OPTION_INT("--depth-bits", "sets depth buffer bits (-1 means default)", -1);
    OPTION_INT("--stencil-bits", "sets stencil buffer bits (-1 means default)", -1);
    OPTION_BOOL("--report-video-format", "if set, reports requested and actual video format", 1);
    OPTION_BOOL("--show-logo", "shows Alchemy logo", 1);
    OPTION_BOOL("--show-ui", "sets initial GUI visibility", 1);
    OPTION_BOOL("--enable-maya-controls", "enables or disable maya controls", 0.0f);
    OPTION_BOOL("--benchmark", "enables or disable the benchmark mode", 0.0f);
    OPTION_INT("--benchmark-skip-frames", "sets the number of frames to skip before benchmarking", 5);
    OPTION_INT("--benchmark-frames", "sets the number of frames to benchmark", 30);
    OPTION_BOOL("--column-statistics", "Output statistics to console in comma-separated column form", 0.0f);
    OPTION_BOOL("--allocate-visual-context-in-scratchpad", "Allocate visual context from scratchpad (effect on PS2 only)", 0.0f);
}

void FUN_002342b0(const char *arg0, const char *arg1, int arg2) {
    const char *boolText;

    if (arg2 != 0) {
        boolText = "true";
    } else {
        boolText = "false";
    }
    printf("%s on|off|true|false\n\t%s\n\tdefault: %s\n\n", arg0, arg1, boolText);
}

void FUN_002342e0(const char *arg0, const char *arg1, int arg2) {
    printf("%s int\n\t%s\n\tdefault: %d\n\n", arg0, arg1, arg2);
}

void FUN_00234300(const char *arg0, const char *arg1, float arg2) {
    printf("%s float\n\t%s\n\tdefault: %f\n\n", arg0, arg1, fptodp(arg2));
}

void FUN_00234350(const char *arg0, const char *arg1, float *arg2) {
    /* matching construct: variant search — declaration order of the locals; b52 gives the last-declared local s0 */
    int temp_s1;
    int temp_s0;

    temp_s1 = fptodp(arg2[0]);
    temp_s0 = fptodp(arg2[1]);
    printf("%s <3-vector>\n\t%s\n\tdefault: <%f,%f,%f>\n\n", arg0, arg1, temp_s1, temp_s0, fptodp(arg2[2]));
}

void FUN_002343d0(const char *arg0, const char *arg1, float *arg2) {
    /* matching construct: variant search — declaration order of the locals; b52 gives the last-declared local s0 */
    int temp_s2;
    int temp_s1;
    int temp_s0;
    temp_s2 = fptodp(*(float *)((char *)(arg2) + 0));
    temp_s1 = fptodp(*(float *)((char *)(arg2) + 4));
    temp_s0 = fptodp(*(float *)((char *)(arg2) + 12));
    printf("%s <4-vector>\n\t%s\n\tdefault: <%f,%f,%f,%f>\n\n", arg0, arg1, temp_s2, temp_s1, temp_s0, fptodp(*(float *)((char *)(arg2) + 8)));
}

int FUN_00234470(igStringRefList *arg0, int *arg1, const char *arg2) {
    void *sp3C;
    int *temp_a1;
    int temp_s1;
    int temp_v0;

    if (arg2 != 0) {
        StringList_CopyRetained(&sp3C, arg0, *arg1);
        temp_s1 = strcmp(sp3C, arg2) == 0;
        if (sp3C != 0) {
            temp_a1 = (int *)((char *)sp3C - 8);
            temp_v0 = *(int *)((char *)(sp3C) - 4) - 1;
            *(int *)((char *)(sp3C) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        if (temp_s1 != 0) {
            *arg1 += 1;
            return 1;
        }
    }
    return 0;
}

int FUN_00234510(igStringRefList *a0, int *a1, const char *a2, int *arg3) {
    void *sp2C;

    if (FUN_002345b0(a0, a1, a2, &sp2C) != 0) {
        *arg3 = atoi(sp2C);
        return 1;
    }
    return 0;
}

int FUN_00234560(igStringRefList *arg0, int *arg1, const char *arg2, long long *arg3) {
    void *sp2C;

    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) != 0) {
        *arg3 = atof(sp2C);
        return 1;
    }
    return 0;
}

int FUN_002345b0(igStringRefList *arg0, int *arg1, const char *arg2, void **arg3) {
    void *sp5C;
    void *sp58;
    int eq;
    int v1;
    if (arg2 != 0) {
        StringList_CopyRetained(&sp5C, arg0, *arg1);
        eq = strcmp(sp5C, arg2) == 0;
        if (sp5C != 0) {
            int *a1 = (int *)((char *)sp5C - 8);
            int v0 = *(int *)((char *)sp5C - 4) - 1;
            *(int *)((char *)sp5C - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        if (eq != 0) {
            v1 = *arg1 + 1;
            if (v1 < arg0->_count) {
                *arg1 = v1;
                StringList_CopyRetained(&sp58, arg0, *arg1);
                *arg3 = sp58;
                if (sp58 != 0) {
                    int *a1 = (int *)((char *)sp58 - 8);
                    int v0 = *(int *)((char *)sp58 - 4) - 1;
                    *(int *)((char *)sp58 - 4) = v0;
                    if (v0 == 0) {
                        StringChunk_ReleaseHeader(*a1, a1);
                    }
                }
                v1 = *arg1;
                *arg1 = v1 + 1;
                return 1;
            }
        }
    }
    return 0;
}

int FUN_002346c0(igStringRefList *arg0, int *arg1, const char *arg2, void **arg3) {
    void *sp3C;
    int str;
    int *temp_a1;
    int temp_v0;
    int var_v0;
    void *temp_s1;
    void *temp_v1;

    sp3C = 0;
    if (FUN_002345b0(arg0, arg1, arg2, &sp3C) != 0) {
        str = (int)sp3C;
        if (g_stringPool[0] == 0) {
            var_v0 = StringPool_Allocate(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            g_stringPool[0] = var_v0;
        }
        temp_s1 = (void *)(StringPool_Intern(g_stringPool[0], str));
        temp_v1 = (void *)(*arg3);
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        *arg3 = temp_s1;
        return 1;
    }
    return 0;
}

int FUN_00234770(igStringRefList *arg0, int *arg1, const char *arg2, unsigned char *arg3) {
    void *sp2C;
    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) == 0) {
        return 0;
    }
    *arg3 = 0;
    if (strcmp(sp2C, "on") == 0) {
        *arg3 = 1;
    } else if (strcmp(sp2C, "true") == 0) {
        *arg3 = 1;
    }
    return 1;
}

int thunk_FUN_00234510(igStringRefList *args, int *index, const char *name, int *value)
{
    return FUN_00234510(args, index, name, value);
}

int FUN_00234810(igStringRefList *arg0, int *arg1, const char *arg2, float *arg3) {
    long long sp28;

    if (FUN_00234560(arg0, arg1, arg2, &sp28) != 0) {
        *arg3 = dptofp(sp28);
        return 1;
    }
    return 0;
}

int FUN_00234860(igStringRefList *arg0, int *arg1, const char *arg2, float *arg3) {
    void *sp2C;

    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) != 0) {
        return Vec3f_FromString(sp2C, arg3, " < %f , %f , %f > ");
    }
    return 0;
}

int FUN_002348b0(igStringRefList *arg0, int *arg1, const char *arg2, float *arg3) {
    void *sp2C;
    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) != 0) {
        return FUN_001e6d80(sp2C, arg3, " < %f , %f , %f , %f > ");
    }
    return 0;
}

static inline int renderAllocator(void) {
    if (g_useOwnerAllocator) {
        return Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent[0]);
    }
    return Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary[0]);
}

struct FlushSettings *FUN_00234900(struct FlushSettings *s) {
    s->f0 = 0;
    s->b4 = 1;
    s->b5 = 0;
    s->f8 = 0;
    s->f12 = 1.0f;
    s->f16 = 0.0f;
    s->f20 = 1.0f;
    s->f24 = 1.0f;
    s->f28 = 0.5f;
    s->f32 = 0.0f;
    s->f36 = 1.0f;
    s->f40 = 1.0f;
    s->f44 = 0.0f;
    s->f48 = 0.0f;
    s->f52 = 1.0f;
    s->f56 = 0.001f;
    s->b60 = 1;
    s->f64 = 45.0f;
    s->b68 = 1;
    s->f72 = 0.1f;
    s->f76 = 1000.0f;
    s->f80[0] = g_vec3Zero[0];
    s->f80[1] = g_vec3Zero[1];
    s->f80[2] = g_vec3Zero[2];
    s->b92 = 1;
    s->b93 = 0;
    s->b94 = 0;
    s->b95 = 0;
    s->b96 = 0;
    s->f100[0] = 1.0f;
    s->f100[1] = 1.0f;
    s->f100[2] = 1.0f;
    s->f100[3] = 1.0f;
    s->f100[4] = 1.0f;
    s->f100[5] = 1.0f;
    s->f100[6] = 1.0f;
    s->f100[7] = 1.0f;
    s->f132[0] = g_vec4Zero[0];
    s->f132[1] = g_vec4Zero[1];
    s->f132[2] = g_vec4Zero[2];
    s->f132[3] = g_vec4Zero[3];
    s->f148 = 0.2f;
    s->f152 = 0.2f;
    s->f156 = 0.2f;
    s->f160 = 1.0f;
    s->b164 = 0;
    s->b165 = 0;
    s->b166 = 0;
    s->b167 = 0;
    s->b168 = 0;
    s->b169 = 0;
    s->f172 = 0.1f;
    s->f176 = 0;
    s->b180 = 1;
    s->b181 = 0;
    s->b182 = 0;
    s->width = 640;
    s->height = 448;
    s->f192 = 0;
    s->f196 = -1;
    s->f200 = -1;
    s->f204 = -1;
    s->f208 = -1;
    s->b212 = 1;
    s->b213 = 1;
    s->b214 = 1;
    s->b215 = 0;
    s->b216 = 0;
    s->f220 = 5;
    s->f224 = 30;
    s->b228 = 0;
    s->b229 = 0;
    s->f232 = igIntList_Create(renderAllocator());
    s->f236 = igStringRefList_Create(renderAllocator());
    if (g_viewerOptions == 0) {
        struct FlushShared *shared = __nw__FUi(240);
        if (shared) {
            shared = (struct FlushShared *)ViewerOptions_Construct(shared);
        }
        g_viewerOptions = shared;
    }
    g_viewerOptions->refs++;
    s->shared = g_viewerOptions;
    FUN_00234ee0(s, s->shared->f0);
    return s;
}

void *FUN_00234b90(struct App *arg0, short arg1) {
    igObject *p;
    void *q;
    int *h;
    int rc;

    if (arg0 != 0) {
        ViewerOptions_ReleaseShared();
        if (&arg0->f236) {
            p = arg0->f236;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f232) {
            p = arg0->f232;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg0 != 0) {
            q = arg0->f0;
            if (q != 0) {
                h = (int *)((char *)(q) - 8);
                rc = *(int *)((char *)(q) - 4) - 1;
                *(int *)((char *)(q) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader(*h, h);
                }
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

/* Drops a reference to the shared viewer options, freeing them with the last one. */
static inline void releaseSharedOptions(void) {
    struct FlushShared *f;
    void *p;
    int *h;
    int rc;

    if (g_viewerOptions != 0) {
        if (--g_viewerOptions->refs <= 0) {
            f = g_viewerOptions;
            if (f != 0) {
                if (&f->f236) {
                    p = f->f236;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                if (f != 0) {
                    p = f->f0;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                __dl__FPv(f);
            }
            g_viewerOptions = 0;
        }
    }
}

void ViewerOptions_ReleaseShared(void) {
    releaseSharedOptions();
}

void FUN_00234d70(int self, int count, int *names) {
    int allocator;
    int i;
    if (g_useOwnerAllocator != 0) {
        allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent[0]);
    } else {
        allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary[0]);
    }
    igSmartPointer<InternedStringList> list(igStringRefList_Create(allocator));
    for (i = 0; i < count; i++) {
        int text = names[i];
        StringRef name(text);
        StringList_AppendRetained(list.get(), &name);
    }
    FUN_00235370((ViewerOptions *)self, (igStringRefList *)list.get());
}

/* Command-line parser of an Alchemy model-viewer style application. Each recognised '--option
 * value' is parsed into `opts` and echoed into the block `opts->applied` points at. '--help'
 * prints the usage text and exits, '--' or '-n' ends the option scan, any other '-x' token is
 * reported as unrecognised. The second loop collects the remaining tokens as model files, each
 * with its '-n N' repeat count. */
void FUN_00235370(ViewerOptions *opts, igStringRefList *args)
{
    StringRef modelFile;
    int repeat;
    int index;
    /* Each smart-pointer temporary of the original has its own stack slot. */
    char *helpRef;
    char *optionRef;
    char *printRef;
    char *helpRef2;
    char *currentRef;
    int argc;
    ViewerOptions *applied;
    int slot;
    IntList *repeats;

    repeat = 1;
    argc = args->_count;
    index = 1;

    while (index < argc) {
        if (FUN_00234470(args, &index, "--help")) {
            StringList_CopyRetained(&helpRef, args, 0);
            FUN_00233c10(helpRef);
            ReleaseString(helpRef);
            ReleaseObject(opts->intList);
            opts->intList = 0;
            ReleaseObject(opts->stringList);
            opts->stringList = 0;
            exit(0);
        } else if (FUN_002346c0(args, &index, 0, (void **)&opts->modelName)) {
            char *name;
            name = opts->modelName;
            applied = opts->applied;
            if (name != 0) {
                ((int *)name)[-1]++;
            }
            ReleaseString(applied->modelName);
            applied->modelName = opts->modelName;
        } else if (FUN_00234770(args, &index, "--show-bbox", &opts->showBbox)) {
            opts->applied->showBbox = opts->showBbox;
        } else if (FUN_00234770(args, &index, "--show-normals", &opts->showNormals)) {
            opts->applied->showNormals = opts->showNormals;
        } else if (FUN_002348b0(args, &index, "--normals-color", &opts->normalsColor[0])) {
            applied = opts->applied;
            applied->normalsColor[0] = opts->normalsColor[0];
            applied->normalsColor[1] = opts->normalsColor[1];
            applied->normalsColor[2] = opts->normalsColor[2];
            applied->normalsColor[3] = opts->normalsColor[3];
        } else if (FUN_002348b0(args, &index, "--invalid-stored-normals-color", &opts->invalidStoredNormalsColor[0])) {
            applied = opts->applied;
            applied->invalidStoredNormalsColor[0] = opts->invalidStoredNormalsColor[0];
            applied->invalidStoredNormalsColor[1] = opts->invalidStoredNormalsColor[1];
            applied->invalidStoredNormalsColor[2] = opts->invalidStoredNormalsColor[2];
            applied->invalidStoredNormalsColor[3] = opts->invalidStoredNormalsColor[3];
        } else if (FUN_002348b0(args, &index, "--scaled-normals-color", &opts->scaledNormalsColor[0])) {
            applied = opts->applied;
            applied->scaledNormalsColor[0] = opts->scaledNormalsColor[0];
            applied->scaledNormalsColor[1] = opts->scaledNormalsColor[1];
            applied->scaledNormalsColor[2] = opts->scaledNormalsColor[2];
            applied->scaledNormalsColor[3] = opts->scaledNormalsColor[3];
        } else if (FUN_00234810(args, &index, "--invalid-normals-precision", &opts->invalidNormalsPrecision)) {
            opts->applied->invalidNormalsPrecision = opts->invalidNormalsPrecision;
        } else if (FUN_00234770(args, &index, "--auto-select-camera", &opts->autoSelectCamera)) {
            opts->applied->autoSelectCamera = opts->autoSelectCamera;
        } else if (FUN_00234810(args, &index, "--hfov", &opts->hfov)) {
            opts->applied->hfov = opts->hfov;
        } else if (FUN_00234770(args, &index, "--auto-planes", &opts->autoPlanes)) {
            opts->applied->autoPlanes = opts->autoPlanes;
        } else if (FUN_00234810(args, &index, "--near-plane", &opts->nearPlane)) {
            opts->applied->nearPlane = opts->nearPlane;
        } else if (FUN_00234810(args, &index, "--far-plane", &opts->farPlane)) {
            opts->applied->farPlane = opts->farPlane;
        } else if (FUN_00234860(args, &index, "--up-vector", &opts->upVector[0])) {
            applied = opts->applied;
            applied->upVector[0] = opts->upVector[0];
            applied->upVector[1] = opts->upVector[1];
            applied->upVector[2] = opts->upVector[2];
        } else if (FUN_00234770(args, &index, "--auto-scene-lights", &opts->autoSceneLights)) {
            opts->applied->autoSceneLights = opts->autoSceneLights;
        } else if (FUN_00234770(args, &index, "--auto-head-light", &opts->autoHeadLight)) {
            opts->applied->autoHeadLight = opts->autoHeadLight;
        } else if (FUN_00234770(args, &index, "--use-scene-lights", &opts->useSceneLights)) {
            opts->applied->useSceneLights = opts->useSceneLights;
        } else if (FUN_00234770(args, &index, "--use-head-light", &opts->useHeadLight)) {
            opts->applied->useHeadLight = opts->useHeadLight;
        } else if (FUN_00234770(args, &index, "--use-head-light-specular", &opts->useHeadLightSpecular)) {
            opts->applied->useHeadLightSpecular = opts->useHeadLightSpecular;
        } else if (FUN_002348b0(args, &index, "--head-light-diffuse", &opts->headLightDiffuse[0])) {
            applied = opts->applied;
            applied->headLightDiffuse[0] = opts->headLightDiffuse[0];
            applied->headLightDiffuse[1] = opts->headLightDiffuse[1];
            applied->headLightDiffuse[2] = opts->headLightDiffuse[2];
            applied->headLightDiffuse[3] = opts->headLightDiffuse[3];
        } else if (FUN_002348b0(args, &index, "--head-light-specular", &opts->headLightSpecular[0])) {
            applied = opts->applied;
            applied->headLightSpecular[0] = opts->headLightSpecular[0];
            applied->headLightSpecular[1] = opts->headLightSpecular[1];
            applied->headLightSpecular[2] = opts->headLightSpecular[2];
            applied->headLightSpecular[3] = opts->headLightSpecular[3];
        } else if (FUN_002348b0(args, &index, "--head-light-ambient", &opts->headLightAmbient[0])) {
            applied = opts->applied;
            applied->headLightAmbient[0] = opts->headLightAmbient[0];
            applied->headLightAmbient[1] = opts->headLightAmbient[1];
            applied->headLightAmbient[2] = opts->headLightAmbient[2];
            applied->headLightAmbient[3] = opts->headLightAmbient[3];
        } else if (FUN_002348b0(args, &index, "--clear-color", &opts->clearColor[0])) {
            applied = opts->applied;
            applied->clearColor[0] = opts->clearColor[0];
            applied->clearColor[1] = opts->clearColor[1];
            applied->clearColor[2] = opts->clearColor[2];
            applied->clearColor[3] = opts->clearColor[3];
        } else if (FUN_00234770(args, &index, "--wireframe-mode", &opts->wireframeMode)) {
            opts->applied->wireframeMode = opts->wireframeMode;
        } else if (FUN_00234770(args, &index, "--force-wireframe", &opts->forceWireframe)) {
            opts->applied->forceWireframe = opts->forceWireframe;
        } else if (FUN_00234770(args, &index, "--backface-culling-mode", &opts->backfaceCullingMode)) {
            opts->applied->backfaceCullingMode = opts->backfaceCullingMode;
        } else if (FUN_00234770(args, &index, "--force-backface-culling", &opts->forceBackfaceCulling)) {
            opts->applied->forceBackfaceCulling = opts->forceBackfaceCulling;
        } else if (FUN_00234770(args, &index, "--alpha-test", &opts->alphaTest)) {
            opts->applied->alphaTest = opts->alphaTest;
        } else if (FUN_00234770(args, &index, "--force-alpha-test", &opts->forceAlphaTest)) {
            opts->applied->forceAlphaTest = opts->forceAlphaTest;
        } else if (FUN_00234810(args, &index, "--alpha-test-reference", &opts->alphaTestReference)) {
            opts->applied->alphaTestReference = opts->alphaTestReference;
        } else if (FUN_00234810(args, &index, "--maximum-frame-rate", &opts->maximumFrameRate)) {
            opts->applied->maximumFrameRate = opts->maximumFrameRate;
        } else if (FUN_00234770(args, &index, "--optimize-textures", &opts->optimizeTextures)) {
            opts->applied->optimizeTextures = opts->optimizeTextures;
        } else if (FUN_00234770(args, &index, "--half-buffer", &opts->halfBuffer)) {
            opts->applied->halfBuffer = opts->halfBuffer;
        } else if (FUN_00234770(args, &index, "--pal-video-mode", &opts->palVideoMode)) {
            opts->applied->palVideoMode = opts->palVideoMode;
        } else if (thunk_FUN_00234510(args, &index, "--width", &opts->width)) {
            opts->applied->width = opts->width;
        } else if (thunk_FUN_00234510(args, &index, "--height", &opts->height)) {
            opts->applied->height = opts->height;
        } else if (thunk_FUN_00234510(args, &index, "--swap-interval", &opts->swapInterval)) {
            opts->applied->swapInterval = opts->swapInterval;
        } else if (thunk_FUN_00234510(args, &index, "--color-bits", &opts->colorBits)) {
            opts->applied->colorBits = opts->colorBits;
        } else if (thunk_FUN_00234510(args, &index, "--alpha-bits", &opts->alphaBits)) {
            opts->applied->alphaBits = opts->alphaBits;
        } else if (thunk_FUN_00234510(args, &index, "--depth-bits", &opts->depthBits)) {
            opts->applied->depthBits = opts->depthBits;
        } else if (thunk_FUN_00234510(args, &index, "--stencil-bits", &opts->stencilBits)) {
            opts->applied->stencilBits = opts->stencilBits;
        } else if (FUN_00234770(args, &index, "--report-video-format", &opts->reportVideoFormat)) {
            opts->applied->reportVideoFormat = opts->reportVideoFormat;
        } else if (FUN_00234770(args, &index, "--show-logo", &opts->showLogo)) {
            opts->applied->showLogo = opts->showLogo;
        } else if (FUN_00234770(args, &index, "--show-ui", &opts->showUi)) {
            opts->applied->showUi = opts->showUi;
        } else if (FUN_00234770(args, &index, "--enable-maya-controls", &opts->enableMayaControls)) {
            opts->applied->enableMayaControls = opts->enableMayaControls;
        } else if (FUN_00234770(args, &index, "--benchmark", &opts->benchmark)) {
            opts->applied->benchmark = opts->benchmark;
        } else if (thunk_FUN_00234510(args, &index, "--benchmark-skip-frames", &opts->benchmarkSkipFrames)) {
            opts->applied->benchmarkSkipFrames = opts->benchmarkSkipFrames;
        } else if (thunk_FUN_00234510(args, &index, "--benchmark-frames", &opts->benchmarkFrames)) {
            opts->applied->benchmarkFrames = opts->benchmarkFrames;
        } else if (FUN_00234770(args, &index, "--column-statistics", &opts->columnStatistics)) {
            opts->applied->columnStatistics = opts->columnStatistics;
        } else if (FUN_00234770(args, &index, "--allocate-visual-context-in-scratchpad", &opts->allocateVisualContextInScratchpad)) {
            opts->applied->allocateVisualContextInScratchpad = opts->allocateVisualContextInScratchpad;
        } else if (FUN_00234470(args, &index, "-n")) {
            index = index - 1;
            break;
        } else if (FUN_00234470(args, &index, "--")) {
            break;
        } else {
            int isOption;
            StringList_CopyRetained(&optionRef, args, index);
            isOption = optionRef[0] == '-';
            ReleaseString(optionRef);
            if (!isOption) {
                break;
            }
            StringList_CopyRetained(&printRef, args, index);
            printf("Unrecognized option : %s\n", printRef);
            ReleaseString(printRef);
            StringList_CopyRetained(&helpRef2, args, 0);
            FUN_00233c10(helpRef2);
            ReleaseString(helpRef2);
            ReleaseObject(opts->intList);
            opts->intList = 0;
            ReleaseObject(opts->stringList);
            opts->stringList = 0;
            exit(0);
        }
    }

    while (index < argc) {
        if (!FUN_00234510(args, &index, "-n", &repeat)) {
            StringList_CopyRetained(&currentRef, args, index);
            if (currentRef != 0) {
                ((int *)currentRef)[-1]++;
            }
            ReleaseString(modelFile.p);
            modelFile.p = currentRef;
            ReleaseString(currentRef);
            {
                StringRef argument(modelFile);
                StringList_AppendRetained((igStringRefList *)opts->stringList, &argument.p);
            }
            repeats = (IntList *)opts->intList;
            slot = repeats->count;
            if (slot < repeats->capacity) {
                repeats->count = countOf(repeats) + 1;
            } else {
                List_Resize(repeats, slot + 1, 4);
            }
            repeats->data[slot] = repeat;
            repeat = 1;
            index = index + 1;
        }
    }
}

void Gap__Insight__igFlushRenderer__vfunc_26(igFlushRendererView *self)
{
    self->_visualContext->vfunc_173();
}

static inline int internedPool(void) {
    if (g_stringPool[0] == 0) {
        int v = StringPool_Allocate(0x10);
        if (v != 0) { v = StringPool_Construct(v); }
        g_stringPool[0] = v;
    }
    return g_stringPool[0];
}

void FUN_00236140(void) {
    igSmartPointer<NamedObject> r(igFolder_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem[0])));
    NamedObject *s0 = r.get();
    int *s1 = (int *)StringPool_Intern(internedPool(), "plugins");
    int *old = (int *)s0->name;
    if (old != 0) {
        int *hdr = old - 2;
        int c = old[-1] - 1;
        old[-1] = c;
        if (c == 0) {
            StringChunk_ReleaseHeader(*hdr, hdr);
        }
    }
    s0->name = (int)s1;
    igFolder_SetFolderName(r.get(), "insight");
    igPluginHelper_AddRepository(((G *)g_objectSystem[0])->f76, "Insight", r->name, 1);
}

static inline void describe(const igSmartPointer<TextValue> &text, int value) {
    if (value < 0) {
        igStringObj_Set(text.p, "default");
    } else {
        igStringObj_SetInt(text.p, value, "%d");
    }
}

static inline const char *textOf(const TextValue *value) {
    const char *s = value->text;
    s = (s == 0) ? g_stringObjEmptyText[0] : s;
    return s;
}

FrameBufferFormat ViewerOptions_GetRequestedFormat(ViewerOptions_2382e0 *options) {
    igSmartPointer<TextValue> text(igStringObj_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString[0])));
    FrameBufferFormat format;
    format.enabled = 1;
    format.width = options->width;
    format.height = options->height;
    if (options->reportVideoFormat) {
        printf("Requested format: ");
    }
    describe(text, options->colorBits);
    if (options->reportVideoFormat) {
        printf("color=%s, ", textOf(text.p));
    }
    describe(text, options->alphaBits);
    if (options->reportVideoFormat) {
        printf("alpha=%s, ", textOf(text.p));
    }
    describe(text, options->depthBits);
    if (options->reportVideoFormat) {
        printf("depth=%s, ", textOf(text.p));
    }
    describe(text, options->stencilBits);
    if (options->reportVideoFormat) {
        printf("stencil=%s\n", textOf(text.p));
    }
    format.colorBits = options->colorBits;
    format.alphaBits = options->alphaBits;
    format.depthBits = options->depthBits;
    format.stencilBits = options->stencilBits;
    format.scale = 1.0f;
    return format;
}

unsigned char g_displayErrorIgnored;

/* Creates the display from the shared viewer options: a window and a visual context (in the
 * scratchpad allocator when the options ask for it) set to the NTSC or PAL video mode, with a
 * frame buffer of the requested format and the options' clear colour. A window that cannot be
 * created ends the program. */
igSmartPointer<igWindowView> Viewer_CreateDisplay(int allocator) {
    int windowAllocator;
    int frameBuffer;
    ViewerOptions_2382e0 *options;
    int contextAllocator;
    const igVisualContextView *context;
    int colorBits;
    int alphaBits;
    int depthBits;
    if (allocator == 0) allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent[0]);
    windowAllocator = allocator;
    if (g_viewerOptions == 0) {
        struct FlushShared *shared = __nw__FUi(240);
        if (shared != 0) shared = (struct FlushShared *)ViewerOptions_Construct(shared);
        g_viewerOptions = shared;
    }
    g_viewerOptions->refs++;
    options = (ViewerOptions_2382e0 *)g_viewerOptions;
    igSmartPointer<igWindowView> window(igWindow_CreateInstance(windowAllocator));
    if (window.p == 0) {
        if (g_displayErrorIgnored == 0) {
            int answer = igReportError("Failed to create display. Aborting\n");
            if (answer != 1 && answer == 2) g_displayErrorIgnored = 1;
        }
        exit(1);
    }
    if (options->allocateVisualContextInScratchPad != 0) {
        int scratchpad;
        if (g_useOwnerAllocator != 0) scratchpad = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent[0]);
        else scratchpad = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleFast[0]);
        contextAllocator = scratchpad;
        if (scratchpad == 0) contextAllocator = windowAllocator;
    } else {
        contextAllocator = windowAllocator;
    }
    igSmartPointer<igVisualContextView> visualContext(igVisualContext_CreateInstance(contextAllocator));
    VideoMode mode;
    mode.pal = 0;
    mode.interlace = 0;
    mode.refreshRate = 0.0f;
    mode.swapInterval = 0;
    mode.enable = 1;
    mode.swapInterval = options->swapInterval;
    mode.interlace = 0;
    mode.refreshRate = 59.9399986f;
    mode.outputFormat = 2;
    mode.fullHeight = 1;
    mode.pal = 0;
    mode.interlace = 1;
    if (options->palVideoMode != 0) {
        mode.refreshRate = 50.0f;
        mode.pal = 1;
    }
    if (options->halfBuffer != 0) mode.fullHeight = 0;
    visualContext->setVideoMode(&mode);
    FrameBufferFormat requested = ViewerOptions_GetRequestedFormat(options);
    frameBuffer = visualContext->addFrameBuffer(&requested);
    window->setVisualContext(visualContext);
    if (window->open("", options->width, options->height) == 0) {
        return igSmartPointer<igWindowView>(0, kRetainReference);
    }
    if (options->reportVideoFormat != 0) {
        context = visualContext.p;
        colorBits = context->getColorBits(frameBuffer);
        alphaBits = context->getAlphaBits(frameBuffer);
        depthBits = context->getDepthBits(frameBuffer);
        printf("Actual format: color=%d, alpha=%d, depth=%d, stencil=%d\n", colorBits, alphaBits, depthBits, context->getStencilBits(frameBuffer));
    }
    fflush(_impure_ptr->_stdout);
    visualContext->setClearColor(&options->clearColor);
    visualContext->setCapability0(1);
    releaseSharedOptions();
    return window;
}

