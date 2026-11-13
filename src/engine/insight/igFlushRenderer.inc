igMetaObject *FUN_00233a40(void) {
    if (g_igFlushRenderer_metaObject[0] == 0) {
        g_igFlushRenderer_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igFlushRenderer_metaObject[0];
}

/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
igMetaObject *igFlushRenderer_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igFlushRenderer_metaObject[0] != 0) {
        ready = (g_igFlushRenderer_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00233b80();
done:
    return g_igFlushRenderer_metaObject[0];
}

int igFlushRenderer_GetVTable(void) {
    union U_233a90 u;
    int temp_s0;
    S_ref *q1;


    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0052d060[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_0052ca80[0]);
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
        g_igFlushRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igFlushRenderer_GetMetaObject,
        igFlushRenderer_className,
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
    printf(usage_s_option1_option2_n_number_f, programName);
    printf(n_number_loads_n_instances_of_the_);
    printf(possible_options_are);
    printf(help_prints_this_message);
    printf(nologo_removes_the_logo_display);
    OPTION_BOOL(showBbox, show_bounding_box_on_selected_obje, 1);
    OPTION_BOOL(showNormals, show_normals_on_selected_object, 0.0f);
    if (normalsColor) {
        defaultNormalsColor[0] = 0.0f;
        defaultNormalsColor[1] = 1.0f;
        defaultNormalsColor[2] = 0.0f;
        defaultNormalsColor[3] = 1.0f;
        FUN_002343d0(normalsColor, sets_the_normals_color, defaultNormalsColor);
    }
    if (invalidStoredNormalsColor) {
        defaultInvalidNormalsColor[0] = 1.0f;
        defaultInvalidNormalsColor[1] = 0.5f;
        defaultInvalidNormalsColor[2] = 0.0f;
        defaultInvalidNormalsColor[3] = 1.0f;
        FUN_002343d0(invalidStoredNormalsColor, sets_the_non_normalized_stored_nor, defaultInvalidNormalsColor);
    }
    if (scaledNormalsColor) {
        defaultScaledNormalsColor[0] = 1.0f;
        defaultScaledNormalsColor[1] = 0.0f;
        defaultScaledNormalsColor[2] = 0.0f;
        defaultScaledNormalsColor[3] = 1.0f;
        FUN_002343d0(scaledNormalsColor, sets_the_scaled_normals_color, defaultScaledNormalsColor);
    }
    OPTION_FLOAT(invalidNormalsPrecision, sets_the_precision_on_the_normals_, 0.00100000005f);
    OPTION_BOOL(autoSelectCamera, select_the_first_camera_if_any_in_, 1);
    OPTION_FLOAT(hfov, sets_the_horizontal_field_of_view, 45.0f);
    OPTION_BOOL(autoPlanes, find_automatically_near_and_far_cl, 1);
    OPTION_FLOAT(nearPlane, sets_the_default_near_clipping_pla, 0.100000001f);
    OPTION_FLOAT(farPlane, sets_the_default_far_clipping_plan, 1000.0f);
    if (upVector) {
        defaultUpVector[0] = g_vec3Zero[0];
        defaultUpVector[1] = g_vec3Zero[1];
        defaultUpVector[2] = g_vec3Zero[2];
        FUN_00234350(upVector, sets_the_default_up_vector_0_0_0_m, defaultUpVector);
    }
    OPTION_BOOL(autoSceneLights, sets_automatic_usage_of_scene_ligh, 1);
    OPTION_BOOL(autoHeadLight, sets_automatic_usage_of_head_light, 0.0f);
    OPTION_BOOL(useSceneLights, use_scene_lights_if_not_automatic, 0.0f);
    OPTION_BOOL(useHeadLight, enable_head_light_if_not_automatic, 0.0f);
    OPTION_BOOL(useHeadLightSpecular, use_specular_head_light, 0.0f);
    if (headLightDiffuse) {
        defaultHeadLightDiffuse[0] = 1.0f;
        defaultHeadLightDiffuse[1] = 1.0f;
        defaultHeadLightDiffuse[2] = 1.0f;
        defaultHeadLightDiffuse[3] = 1.0f;
        FUN_002343d0(headLightDiffuse, sets_the_diffuse_color_for_the_hea, defaultHeadLightDiffuse);
    }
    if (headLightSpecular) {
        defaultHeadLightSpecular[0] = 1.0f;
        defaultHeadLightSpecular[1] = 1.0f;
        defaultHeadLightSpecular[2] = 1.0f;
        defaultHeadLightSpecular[3] = 1.0f;
        FUN_002343d0(headLightSpecular, sets_the_specular_color_for_the_he, defaultHeadLightSpecular);
    }
    if (headLightAmbient) {
        defaultHeadLightAmbient[0] = g_vec4Zero[0];
        defaultHeadLightAmbient[1] = g_vec4Zero[1];
        defaultHeadLightAmbient[2] = g_vec4Zero[2];
        defaultHeadLightAmbient[3] = g_vec4Zero[3];
        FUN_002343d0(headLightAmbient, sets_the_ambient_color_for_the_hea, defaultHeadLightAmbient);
    }
    if (clearColor) {
        defaultClearColor[0] = 0.200000003f;
        defaultClearColor[1] = 0.200000003f;
        defaultClearColor[2] = 0.200000003f;
        defaultClearColor[3] = 1.0f;
        FUN_002343d0(clearColor, sets_the_clear_color, defaultClearColor);
    }
    OPTION_BOOL(wireframeMode, sets_wireframe_mode, 0.0f);
    OPTION_BOOL(forceWireframe, force_wireframe_on_all_geometries, 0.0f);
    OPTION_BOOL(backfaceCullingMode, sets_back_face_culling_mode, 0.0f);
    OPTION_BOOL(forceBackfaceCulling, force_back_face_culling_on_all_geo, 0.0f);
    OPTION_BOOL(alphaTest, sets_alpha_test_state, 0.0f);
    OPTION_BOOL(forceAlphaTest, force_alpha_test_on_all_geometries, 0.0f);
    OPTION_FLOAT(alphaTestReference, sets_alpha_test_reference_value, 0.100000001f);
    OPTION_FLOAT(maximumFrameRate, sets_the_maximum_frame_rate_0_mean, 0.0f);
    OPTION_BOOL(optimizeTextures, share_textures_at_load_time, 1);
    OPTION_BOOL(halfBuffer, sets_psx2_half_buffer_mode, 0.0f);
    OPTION_BOOL(palVideoMode, sets_pal_video_mode, 0.0f);
    OPTION_INT(width, viewer_window_width, 640);
    OPTION_INT(height, viewer_window_height, 448);
    OPTION_INT(swapInterval, sets_the_swap_interval_0_means_no_, 0.0f);
    OPTION_INT(colorBits, sets_color_buffer_bits_1_means_def, -1);
    OPTION_INT(alphaBits, sets_alpha_buffer_bits_1_means_def, -1);
    OPTION_INT(depthBits, sets_depth_buffer_bits_1_means_def, -1);
    OPTION_INT(stencilBits, sets_stencil_buffer_bits_1_means_d, -1);
    OPTION_BOOL(reportVideoFormat, if_set_reports_requested_and_actua, 1);
    OPTION_BOOL(showLogo, shows_alchemy_logo, 1);
    OPTION_BOOL(showUi, sets_initial_gui_visibility, 1);
    OPTION_BOOL(enableMayaControls, enables_or_disable_maya_controls, 0.0f);
    OPTION_BOOL(benchmark, enables_or_disable_the_benchmark_m, 0.0f);
    OPTION_INT(benchmarkSkipFrames, sets_the_number_of_frames_to_skip_, 5);
    OPTION_INT(benchmarkFrames, sets_the_number_of_frames_to_bench, 30);
    OPTION_BOOL(columnStatistics, output_statistics_to_console_in_co, 0.0f);
    OPTION_BOOL(allocateVisualContextInScratchpad, allocate_visual_context_from_scrat, 0.0f);
}

void FUN_002342b0(const char *arg0, const char *arg1, int arg2) {
    int *var_a3;

    if (arg2 != 0) {
        var_a3 = &DAT_004e95f8[0];
    } else {
        var_a3 = &DAT_004e9600[0];
    }
    printf(&DAT_004e95d0[0], arg0, arg1, var_a3);
}

void FUN_002342e0(const char *arg0, const char *arg1, int arg2) {
    printf(&DAT_004e9610[0], arg0, arg1, arg2);
}

void FUN_00234300(const char *arg0, const char *arg1, float arg2) {
    printf(&DAT_004e9630[0], arg0, arg1, fptodp(arg2));
}

void FUN_00234350(const char *arg0, const char *arg1, float *arg2) {
    /* matching construct: variant search — declaration order of the locals; b52 gives the last-declared local s0 */
    int temp_s1;
    int temp_s0;

    temp_s1 = fptodp(arg2[0]);
    temp_s0 = fptodp(arg2[1]);
    printf(&DAT_004e9650[0], arg0, arg1, temp_s1, temp_s0, fptodp(arg2[2]));
}

void FUN_002343d0(const char *arg0, const char *arg1, float *arg2) {
    /* matching construct: variant search — declaration order of the locals; b52 gives the last-declared local s0 */
    int temp_s2;
    int temp_s1;
    int temp_s0;
    temp_s2 = fptodp(*(float *)((char *)(arg2) + 0));
    temp_s1 = fptodp(*(float *)((char *)(arg2) + 4));
    temp_s0 = fptodp(*(float *)((char *)(arg2) + 12));
    printf(&DAT_004e9680[0], arg0, arg1, temp_s2, temp_s1, temp_s0, fptodp(*(float *)((char *)(arg2) + 8)));
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
    if (strcmp(sp2C, &DAT_004e96b0[0]) == 0) {
        *arg3 = 1;
    } else if (strcmp(sp2C, &DAT_004e95f8[0]) == 0) {
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
        return Vec3f_FromString(sp2C, arg3, &DAT_004e96c0[0]);
    }
    return 0;
}

int FUN_002348b0(igStringRefList *arg0, int *arg1, const char *arg2, float *arg3) {
    void *sp2C;
    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) != 0) {
        return FUN_001e6d80(sp2C, arg3, &DAT_004e96e0[0]);
    }
    return 0;
}

static inline int renderAllocator(void) {
    if (GPR_00554c14) {
        return Memory_GetAllocatorBySelector(DAT_00587028[0]);
    }
    return Memory_GetAllocatorBySelector(g_temporaryAllocatorSelector[0]);
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
    s->f236 = FUN_002b90e0(renderAllocator());
    if (DAT_0056dc50[0] == 0) {
        struct FlushShared *shared = FUN_001007e0(240);
        if (shared) {
            shared = (struct FlushShared *)FUN_00238110(shared);
        }
        DAT_0056dc50[0] = shared;
    }
    DAT_0056dc50[0]->refs++;
    s->shared = DAT_0056dc50[0];
    FUN_00234ee0(s, s->shared->f0);
    return s;
}

void *FUN_00234b90(struct App *arg0, short arg1) {
    igObject *p;
    void *q;
    int *h;
    int rc;

    if (arg0 != 0) {
        FUN_00234ca0();
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00234ca0(void) {
    struct FlushShared *f;
    void *p;
    int *h;
    int rc;

    if (DAT_0056dc50[0] != 0) {
        if (--DAT_0056dc50[0]->refs <= 0) {
            f = DAT_0056dc50[0];
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
                FUN_00100610(f);
            }
            DAT_0056dc50[0] = 0;
        }
    }
}

void FUN_00234d70(int self, int count, int *names) {
    int allocator;
    int i;
    if (GPR_00554c14 != 0) {
        allocator = Memory_GetAllocatorBySelector(DAT_00587028[0]);
    } else {
        allocator = Memory_GetAllocatorBySelector(g_temporaryAllocatorSelector[0]);
    }
    igSmartPointer<InternedStringList> list(FUN_002b90e0(allocator));
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
        if (FUN_00234470(args, &index, help)) {
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
        } else if (FUN_00234770(args, &index, showBbox, &opts->showBbox)) {
            opts->applied->showBbox = opts->showBbox;
        } else if (FUN_00234770(args, &index, showNormals, &opts->showNormals)) {
            opts->applied->showNormals = opts->showNormals;
        } else if (FUN_002348b0(args, &index, normalsColor, &opts->normalsColor[0])) {
            applied = opts->applied;
            applied->normalsColor[0] = opts->normalsColor[0];
            applied->normalsColor[1] = opts->normalsColor[1];
            applied->normalsColor[2] = opts->normalsColor[2];
            applied->normalsColor[3] = opts->normalsColor[3];
        } else if (FUN_002348b0(args, &index, invalidStoredNormalsColor, &opts->invalidStoredNormalsColor[0])) {
            applied = opts->applied;
            applied->invalidStoredNormalsColor[0] = opts->invalidStoredNormalsColor[0];
            applied->invalidStoredNormalsColor[1] = opts->invalidStoredNormalsColor[1];
            applied->invalidStoredNormalsColor[2] = opts->invalidStoredNormalsColor[2];
            applied->invalidStoredNormalsColor[3] = opts->invalidStoredNormalsColor[3];
        } else if (FUN_002348b0(args, &index, scaledNormalsColor, &opts->scaledNormalsColor[0])) {
            applied = opts->applied;
            applied->scaledNormalsColor[0] = opts->scaledNormalsColor[0];
            applied->scaledNormalsColor[1] = opts->scaledNormalsColor[1];
            applied->scaledNormalsColor[2] = opts->scaledNormalsColor[2];
            applied->scaledNormalsColor[3] = opts->scaledNormalsColor[3];
        } else if (FUN_00234810(args, &index, invalidNormalsPrecision, &opts->invalidNormalsPrecision)) {
            opts->applied->invalidNormalsPrecision = opts->invalidNormalsPrecision;
        } else if (FUN_00234770(args, &index, autoSelectCamera, &opts->autoSelectCamera)) {
            opts->applied->autoSelectCamera = opts->autoSelectCamera;
        } else if (FUN_00234810(args, &index, hfov, &opts->hfov)) {
            opts->applied->hfov = opts->hfov;
        } else if (FUN_00234770(args, &index, autoPlanes, &opts->autoPlanes)) {
            opts->applied->autoPlanes = opts->autoPlanes;
        } else if (FUN_00234810(args, &index, nearPlane, &opts->nearPlane)) {
            opts->applied->nearPlane = opts->nearPlane;
        } else if (FUN_00234810(args, &index, farPlane, &opts->farPlane)) {
            opts->applied->farPlane = opts->farPlane;
        } else if (FUN_00234860(args, &index, upVector, &opts->upVector[0])) {
            applied = opts->applied;
            applied->upVector[0] = opts->upVector[0];
            applied->upVector[1] = opts->upVector[1];
            applied->upVector[2] = opts->upVector[2];
        } else if (FUN_00234770(args, &index, autoSceneLights, &opts->autoSceneLights)) {
            opts->applied->autoSceneLights = opts->autoSceneLights;
        } else if (FUN_00234770(args, &index, autoHeadLight, &opts->autoHeadLight)) {
            opts->applied->autoHeadLight = opts->autoHeadLight;
        } else if (FUN_00234770(args, &index, useSceneLights, &opts->useSceneLights)) {
            opts->applied->useSceneLights = opts->useSceneLights;
        } else if (FUN_00234770(args, &index, useHeadLight, &opts->useHeadLight)) {
            opts->applied->useHeadLight = opts->useHeadLight;
        } else if (FUN_00234770(args, &index, useHeadLightSpecular, &opts->useHeadLightSpecular)) {
            opts->applied->useHeadLightSpecular = opts->useHeadLightSpecular;
        } else if (FUN_002348b0(args, &index, headLightDiffuse, &opts->headLightDiffuse[0])) {
            applied = opts->applied;
            applied->headLightDiffuse[0] = opts->headLightDiffuse[0];
            applied->headLightDiffuse[1] = opts->headLightDiffuse[1];
            applied->headLightDiffuse[2] = opts->headLightDiffuse[2];
            applied->headLightDiffuse[3] = opts->headLightDiffuse[3];
        } else if (FUN_002348b0(args, &index, headLightSpecular, &opts->headLightSpecular[0])) {
            applied = opts->applied;
            applied->headLightSpecular[0] = opts->headLightSpecular[0];
            applied->headLightSpecular[1] = opts->headLightSpecular[1];
            applied->headLightSpecular[2] = opts->headLightSpecular[2];
            applied->headLightSpecular[3] = opts->headLightSpecular[3];
        } else if (FUN_002348b0(args, &index, headLightAmbient, &opts->headLightAmbient[0])) {
            applied = opts->applied;
            applied->headLightAmbient[0] = opts->headLightAmbient[0];
            applied->headLightAmbient[1] = opts->headLightAmbient[1];
            applied->headLightAmbient[2] = opts->headLightAmbient[2];
            applied->headLightAmbient[3] = opts->headLightAmbient[3];
        } else if (FUN_002348b0(args, &index, clearColor, &opts->clearColor[0])) {
            applied = opts->applied;
            applied->clearColor[0] = opts->clearColor[0];
            applied->clearColor[1] = opts->clearColor[1];
            applied->clearColor[2] = opts->clearColor[2];
            applied->clearColor[3] = opts->clearColor[3];
        } else if (FUN_00234770(args, &index, wireframeMode, &opts->wireframeMode)) {
            opts->applied->wireframeMode = opts->wireframeMode;
        } else if (FUN_00234770(args, &index, forceWireframe, &opts->forceWireframe)) {
            opts->applied->forceWireframe = opts->forceWireframe;
        } else if (FUN_00234770(args, &index, backfaceCullingMode, &opts->backfaceCullingMode)) {
            opts->applied->backfaceCullingMode = opts->backfaceCullingMode;
        } else if (FUN_00234770(args, &index, forceBackfaceCulling, &opts->forceBackfaceCulling)) {
            opts->applied->forceBackfaceCulling = opts->forceBackfaceCulling;
        } else if (FUN_00234770(args, &index, alphaTest, &opts->alphaTest)) {
            opts->applied->alphaTest = opts->alphaTest;
        } else if (FUN_00234770(args, &index, forceAlphaTest, &opts->forceAlphaTest)) {
            opts->applied->forceAlphaTest = opts->forceAlphaTest;
        } else if (FUN_00234810(args, &index, alphaTestReference, &opts->alphaTestReference)) {
            opts->applied->alphaTestReference = opts->alphaTestReference;
        } else if (FUN_00234810(args, &index, maximumFrameRate, &opts->maximumFrameRate)) {
            opts->applied->maximumFrameRate = opts->maximumFrameRate;
        } else if (FUN_00234770(args, &index, optimizeTextures, &opts->optimizeTextures)) {
            opts->applied->optimizeTextures = opts->optimizeTextures;
        } else if (FUN_00234770(args, &index, halfBuffer, &opts->halfBuffer)) {
            opts->applied->halfBuffer = opts->halfBuffer;
        } else if (FUN_00234770(args, &index, palVideoMode, &opts->palVideoMode)) {
            opts->applied->palVideoMode = opts->palVideoMode;
        } else if (thunk_FUN_00234510(args, &index, width, &opts->width)) {
            opts->applied->width = opts->width;
        } else if (thunk_FUN_00234510(args, &index, height, &opts->height)) {
            opts->applied->height = opts->height;
        } else if (thunk_FUN_00234510(args, &index, swapInterval, &opts->swapInterval)) {
            opts->applied->swapInterval = opts->swapInterval;
        } else if (thunk_FUN_00234510(args, &index, colorBits, &opts->colorBits)) {
            opts->applied->colorBits = opts->colorBits;
        } else if (thunk_FUN_00234510(args, &index, alphaBits, &opts->alphaBits)) {
            opts->applied->alphaBits = opts->alphaBits;
        } else if (thunk_FUN_00234510(args, &index, depthBits, &opts->depthBits)) {
            opts->applied->depthBits = opts->depthBits;
        } else if (thunk_FUN_00234510(args, &index, stencilBits, &opts->stencilBits)) {
            opts->applied->stencilBits = opts->stencilBits;
        } else if (FUN_00234770(args, &index, reportVideoFormat, &opts->reportVideoFormat)) {
            opts->applied->reportVideoFormat = opts->reportVideoFormat;
        } else if (FUN_00234770(args, &index, showLogo, &opts->showLogo)) {
            opts->applied->showLogo = opts->showLogo;
        } else if (FUN_00234770(args, &index, showUi, &opts->showUi)) {
            opts->applied->showUi = opts->showUi;
        } else if (FUN_00234770(args, &index, enableMayaControls, &opts->enableMayaControls)) {
            opts->applied->enableMayaControls = opts->enableMayaControls;
        } else if (FUN_00234770(args, &index, benchmark, &opts->benchmark)) {
            opts->applied->benchmark = opts->benchmark;
        } else if (thunk_FUN_00234510(args, &index, benchmarkSkipFrames, &opts->benchmarkSkipFrames)) {
            opts->applied->benchmarkSkipFrames = opts->benchmarkSkipFrames;
        } else if (thunk_FUN_00234510(args, &index, benchmarkFrames, &opts->benchmarkFrames)) {
            opts->applied->benchmarkFrames = opts->benchmarkFrames;
        } else if (FUN_00234770(args, &index, columnStatistics, &opts->columnStatistics)) {
            opts->applied->columnStatistics = opts->columnStatistics;
        } else if (FUN_00234770(args, &index, allocateVisualContextInScratchpad, &opts->allocateVisualContextInScratchpad)) {
            opts->applied->allocateVisualContextInScratchpad = opts->allocateVisualContextInScratchpad;
        } else if (FUN_00234470(args, &index, n)) {
            index = index - 1;
            break;
        } else if (FUN_00234470(args, &index, dashdash)) {
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
            printf(unrecognized, printRef);
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
        if (!FUN_00234510(args, &index, n, &repeat)) {
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
    igSmartPointer<NamedObject> r(FUN_002c43b0(Memory_GetAllocatorBySelector(DAT_00587038[0])));
    NamedObject *s0 = r.get();
    int *s1 = (int *)StringPool_Intern(internedPool(), &DAT_004e9740[0]);
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
    FUN_002e3850(r.get(), &DAT_004e9748[0]);
    FUN_00304720(((G *)g_objectSystem[0])->f76, &DAT_004e9750[0], r->name, 1);
}

static inline void describe(const igSmartPointer<TextValue> &text, int value) {
    if (value < 0) {
        FUN_0030b3c0(text.p, DAT_004e9778);
    } else {
        FUN_0030b720(text.p, value, DAT_004e9780);
    }
}

static inline const char *textOf(const TextValue *value) {
    const char *s = value->text;
    s = (s == 0) ? DAT_004c22f0[0] : s;
    return s;
}

ShadowSettings FUN_00236260(ShadowConfig *config) {
    igSmartPointer<TextValue> text(FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0])));
    ShadowSettings settings;
    settings.enabled = 1;
    settings.width = config->width;
    settings.height = config->height;
    if (config->verbose) {
        printf(DAT_004e9760);
    }
    describe(text, config->left);
    if (config->verbose) {
        printf(DAT_004e9788, textOf(text.p));
    }
    describe(text, config->top);
    if (config->verbose) {
        printf(DAT_004e9798, textOf(text.p));
    }
    describe(text, config->right);
    if (config->verbose) {
        printf(DAT_004e97a8, textOf(text.p));
    }
    describe(text, config->bottom);
    if (config->verbose) {
        printf(DAT_004e97b8, textOf(text.p));
    }
    settings.left = config->left;
    settings.top = config->top;
    settings.right = config->right;
    settings.bottom = config->bottom;
    settings.scale = 1.0f;
    return settings;
}

