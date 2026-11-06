/* The Alchemy viewer's usage / option help printer. Prints the banner ("USAGE: %s [option1 ...")
 * and then one help entry per command-line option: name, description and the option's default
 * value, through five typed helpers (bool, int, float, vec3, vec4) that format the entry with
 * printf. Evidence: the strings at 0x004e87c0..0x004e9590 (data/strings.json), the helper call
 * shapes (FUN_002342b0 prints "true"/"false" from its flag, FUN_002342e0 an int, FUN_00234300 a
 * float, FUN_00234350 a float[3], FUN_002343d0 a float[4]). Each entry is guarded by `if (name)`:
 * retail tests the literal's address against zero, so the guard comes from the option macro, not
 * from the data. Argument: the program name for the USAGE line. Build: default compiler, -O3
 * -Iinclude. */
extern int printf(const char *, ...);
extern void FUN_002342b0(const char *name, const char *help, int defaultValue);   /* bool option */
extern void FUN_002342e0(const char *name, const char *help, int defaultValue);   /* int option */
extern void FUN_00234300(const char *name, const char *help, float defaultValue); /* float option */
extern void FUN_00234350(const char *name, const char *help, float *defaultValue);/* vec3 option */
extern void FUN_002343d0(const char *name, const char *help, float *defaultValue);/* vec4 option */

extern char usage_s_option1_option2_n_number_f[]; /* 'USAGE: %s [option1 [option2 ...]] [[-n number] filename1] [[-n number] filename2 ...]\n\n' */
extern char n_number_loads_n_instances_of_the_[]; /* '-n number\n\tloads n instances of the next file\n\n' */
extern char possible_options_are[]; /* 'Possible options are :\n' */
extern char help_prints_this_message[]; /* '--help\n\tPrints this message.\n\n' */
extern char nologo_removes_the_logo_display[]; /* '--nologo\n\tremoves the logo display\n\n' */
extern char showBbox[]; /* --show-bbox */
extern char show_bounding_box_on_selected_obje[]; /* show bounding box on selected object */
extern char showNormals[]; /* --show-normals */
extern char show_normals_on_selected_object[]; /* show normals on selected object */
extern char normalsColor[]; /* --normals-color */
extern char sets_the_normals_color[]; /* sets the normals color */
extern char invalidStoredNormalsColor[]; /* --invalid-stored-normals-color */
extern char sets_the_non_normalized_stored_nor[]; /* sets the non-normalized stored normals color */
extern char scaledNormalsColor[]; /* --scaled-normals-color */
extern char sets_the_scaled_normals_color[]; /* sets the scaled normals color */
extern char invalidNormalsPrecision[]; /* --invalid-normals-precision */
extern char sets_the_precision_on_the_normals_[]; /* sets the precision on the normals norm */
extern char autoSelectCamera[]; /* --auto-select-camera */
extern char select_the_first_camera_if_any_in_[]; /* select the first camera if any in the scene */
extern char hfov[]; /* --hfov */
extern char sets_the_horizontal_field_of_view[]; /* sets the horizontal field of view */
extern char autoPlanes[]; /* --auto-planes */
extern char find_automatically_near_and_far_cl[]; /* find automatically near and far clipping planes */
extern char nearPlane[]; /* --near-plane */
extern char sets_the_default_near_clipping_pla[]; /* sets the default near clipping plane */
extern char farPlane[]; /* --far-plane */
extern char sets_the_default_far_clipping_plan[]; /* sets the default far clipping plane */
extern char upVector[]; /* --up-vector */
extern char sets_the_default_up_vector_0_0_0_m[]; /* sets the default up vector (<0,0,0> means use scene up vector) */
extern char autoSceneLights[]; /* --auto-scene-lights */
extern char sets_automatic_usage_of_scene_ligh[]; /* sets automatic usage of scene lights */
extern char autoHeadLight[]; /* --auto-head-light */
extern char sets_automatic_usage_of_head_light[]; /* sets automatic usage of head light */
extern char useSceneLights[]; /* --use-scene-lights */
extern char use_scene_lights_if_not_automatic[]; /* use scene lights (if not automatic) */
extern char useHeadLight[]; /* --use-head-light */
extern char enable_head_light_if_not_automatic[]; /* enable head light (if not automatic) */
extern char useHeadLightSpecular[]; /* --use-head-light-specular */
extern char use_specular_head_light[]; /* use specular head light */
extern char headLightDiffuse[]; /* --head-light-diffuse */
extern char sets_the_diffuse_color_for_the_hea[]; /* sets the diffuse color for the head light */
extern char headLightSpecular[]; /* --head-light-specular */
extern char sets_the_specular_color_for_the_he[]; /* sets the specular color for the head light */
extern char headLightAmbient[]; /* --head-light-ambient */
extern char sets_the_ambient_color_for_the_hea[]; /* sets the ambient color for the head light */
extern char clearColor[]; /* --clear-color */
extern char sets_the_clear_color[]; /* sets the clear color */
extern char wireframeMode[]; /* --wireframe-mode */
extern char sets_wireframe_mode[]; /* sets wireframe mode */
extern char forceWireframe[]; /* --force-wireframe */
extern char force_wireframe_on_all_geometries[]; /* force wireframe on all geometries */
extern char backfaceCullingMode[]; /* --backface-culling-mode */
extern char sets_back_face_culling_mode[]; /* sets back-face culling mode */
extern char forceBackfaceCulling[]; /* --force-backface-culling */
extern char force_back_face_culling_on_all_geo[]; /* force back-face culling on all geometries */
extern char alphaTest[]; /* --alpha-test */
extern char sets_alpha_test_state[]; /* sets alpha test state */
extern char forceAlphaTest[]; /* --force-alpha-test */
extern char force_alpha_test_on_all_geometries[]; /* force alpha test on all geometries */
extern char alphaTestReference[]; /* --alpha-test-reference */
extern char sets_alpha_test_reference_value[]; /* sets alpha test reference value */
extern char maximumFrameRate[]; /* --maximum-frame-rate */
extern char sets_the_maximum_frame_rate_0_mean[]; /* sets the maximum frame rate (0 means no maximum) */
extern char optimizeTextures[]; /* --optimize-textures */
extern char share_textures_at_load_time[]; /* share textures at load time */
extern char halfBuffer[]; /* --half-buffer */
extern char sets_psx2_half_buffer_mode[]; /* sets PSX2 half-buffer mode */
extern char palVideoMode[]; /* --pal-video-mode */
extern char sets_pal_video_mode[]; /* sets PAL video mode */
extern char width[]; /* --width */
extern char viewer_window_width[]; /* viewer window width */
extern char height[]; /* --height */
extern char viewer_window_height[]; /* viewer window height */
extern char swapInterval[]; /* --swap-interval */
extern char sets_the_swap_interval_0_means_no_[]; /* sets the swap interval (0 means no vsync) */
extern char colorBits[]; /* --color-bits */
extern char sets_color_buffer_bits_1_means_def[]; /* sets color buffer bits (-1 means default) */
extern char alphaBits[]; /* --alpha-bits */
extern char sets_alpha_buffer_bits_1_means_def[]; /* sets alpha buffer bits (-1 means default) */
extern char depthBits[]; /* --depth-bits */
extern char sets_depth_buffer_bits_1_means_def[]; /* sets depth buffer bits (-1 means default) */
extern char stencilBits[]; /* --stencil-bits */
extern char sets_stencil_buffer_bits_1_means_d[]; /* sets stencil buffer bits (-1 means default) */
extern char reportVideoFormat[]; /* --report-video-format */
extern char if_set_reports_requested_and_actua[]; /* if set, reports requested and actual video format */
extern char showLogo[]; /* --show-logo */
extern char shows_alchemy_logo[]; /* shows Alchemy logo */
extern char showUi[]; /* --show-ui */
extern char sets_initial_gui_visibility[]; /* sets initial GUI visibility */
extern char enableMayaControls[]; /* --enable-maya-controls */
extern char enables_or_disable_maya_controls[]; /* enables or disable maya controls */
extern char benchmark[]; /* --benchmark */
extern char enables_or_disable_the_benchmark_m[]; /* enables or disable the benchmark mode */
extern char benchmarkSkipFrames[]; /* --benchmark-skip-frames */
extern char sets_the_number_of_frames_to_skip_[]; /* sets the number of frames to skip before benchmarking */
extern char benchmarkFrames[]; /* --benchmark-frames */
extern char sets_the_number_of_frames_to_bench[]; /* sets the number of frames to benchmark */
extern char columnStatistics[]; /* --column-statistics */
extern char output_statistics_to_console_in_co[]; /* Output statistics to console in comma-separated column form */
extern char allocateVisualContextInScratchpad[]; /* --allocate-visual-context-in-scratchpad */
extern char allocate_visual_context_from_scrat[]; /* Allocate visual context from scratchpad (effect on PS2 only) */

/* Constant initialisers the compiler emitted into .rodata for the all-zero local vectors of
 * the --up-vector and --head-light-ambient defaults (the other vectors are built with immediates). */
extern const float g_vec3Zero[4];
extern const float g_vec4Zero[4];

/* Small-data float literals the retail code reads through gp (value in the comment). */
extern float GPR_005548c8; /* 0.001f  default --invalid-normals-precision */
extern float GPR_00554948; /* 0.1f    default --near-plane and --alpha-test-reference */
extern float GPR_00554968; /* 0.2f    default --clear-color red/green/blue */

#define OPTION_BOOL(name, help, value)  if (name) FUN_002342b0(name, help, value)
#define OPTION_INT(name, help, value)   if (name) FUN_002342e0(name, help, value)
#define OPTION_FLOAT(name, help, value) if (name) FUN_00234300(name, help, value)

void FUN_00233c10(const char *programName)
{
    /* matching construct: variant search — decl order [7, 6, 5, 4, 3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
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
    OPTION_FLOAT(invalidNormalsPrecision, sets_the_precision_on_the_normals_, GPR_005548c8);
    OPTION_BOOL(autoSelectCamera, select_the_first_camera_if_any_in_, 1);
    OPTION_FLOAT(hfov, sets_the_horizontal_field_of_view, 45.0f);
    OPTION_BOOL(autoPlanes, find_automatically_near_and_far_cl, 1);
    OPTION_FLOAT(nearPlane, sets_the_default_near_clipping_pla, GPR_00554948);
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
        defaultClearColor[0] = GPR_00554968;
        defaultClearColor[1] = GPR_00554968;
        defaultClearColor[2] = GPR_00554968;
        defaultClearColor[3] = 1.0f;
        FUN_002343d0(clearColor, sets_the_clear_color, defaultClearColor);
    }
    OPTION_BOOL(wireframeMode, sets_wireframe_mode, 0.0f);
    OPTION_BOOL(forceWireframe, force_wireframe_on_all_geometries, 0.0f);
    OPTION_BOOL(backfaceCullingMode, sets_back_face_culling_mode, 0.0f);
    OPTION_BOOL(forceBackfaceCulling, force_back_face_culling_on_all_geo, 0.0f);
    OPTION_BOOL(alphaTest, sets_alpha_test_state, 0.0f);
    OPTION_BOOL(forceAlphaTest, force_alpha_test_on_all_geometries, 0.0f);
    OPTION_FLOAT(alphaTestReference, sets_alpha_test_reference_value, GPR_00554948);
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
