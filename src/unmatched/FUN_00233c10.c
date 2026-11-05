/* 0x00233c10 - FUN_00233c10: the Alchemy viewer's usage / option help printer.
 * Prints the banner ("USAGE: %s [option1 ...") and then one help entry per command-line option:
 * name, description and the option's default value, through five typed helpers (bool, int, float,
 * vec3, vec4) that format the entry with printf.
 * Evidence: the strings at 0x004e87c0..0x004e9590 (data/strings.json), the helper call shapes
 * (FUN_002342b0 prints "true"/"false" from its flag, FUN_002342e0 an int, FUN_00234300 a float,
 * FUN_00234350 a float[3], FUN_002343d0 a float[4]).
 * Each entry is guarded by `if (name)`: retail tests the literal's address against zero, so the
 * guard comes from the option macro, not from the data.
 * Argument: the program name for the USAGE line.
 * Build: default compiler, -O3 -Iinclude (verified MATCH). */
extern int printf(const char *, ...);
extern void FUN_002342b0(const char *name, const char *help, int defaultValue);   /* bool option */
extern void FUN_002342e0(const char *name, const char *help, int defaultValue);   /* int option */
extern void FUN_00234300(const char *name, const char *help, float defaultValue); /* float option */
extern void FUN_00234350(const char *name, const char *help, float *defaultValue);/* vec3 option */
extern void FUN_002343d0(const char *name, const char *help, float *defaultValue);/* vec4 option */

extern char s_usage_s_option1_option2_n_number_f_004e87c0[]; /* 'USAGE: %s [option1 [option2 ...]] [[-n number] filename1] [[-n number] filename2 ...]\n\n' */
extern char s_n_number_loads_n_instances_of_the__004e8820[]; /* '-n number\n\tloads n instances of the next file\n\n' */
extern char s_possible_options_are_004e8850[]; /* 'Possible options are :\n' */
extern char s_help_prints_this_message_004e8870[]; /* '--help\n\tPrints this message.\n\n' */
extern char s_nologo_removes_the_logo_display_004e8890[]; /* '--nologo\n\tremoves the logo display\n\n' */
extern char s_show_bbox_004e88b8[]; /* --show-bbox */
extern char s_show_bounding_box_on_selected_obje_004e88d0[]; /* show bounding box on selected object */
extern char s_show_normals_004e88f8[]; /* --show-normals */
extern char s_show_normals_on_selected_object_004e8910[]; /* show normals on selected object */
extern char s_normals_color_004e8930[]; /* --normals-color */
extern char s_sets_the_normals_color_004e8940[]; /* sets the normals color */
extern char s_invalid_stored_normals_color_004e8960[]; /* --invalid-stored-normals-color */
extern char s_sets_the_non_normalized_stored_nor_004e8980[]; /* sets the non-normalized stored normals color */
extern char s_scaled_normals_color_004e89b0[]; /* --scaled-normals-color */
extern char s_sets_the_scaled_normals_color_004e89d0[]; /* sets the scaled normals color */
extern char s_invalid_normals_precision_004e89f0[]; /* --invalid-normals-precision */
extern char s_sets_the_precision_on_the_normals__004e8a10[]; /* sets the precision on the normals norm */
extern char s_auto_select_camera_004e8a40[]; /* --auto-select-camera */
extern char s_select_the_first_camera_if_any_in__004e8a60[]; /* select the first camera if any in the scene */
extern char s_hfov_004e8a90[]; /* --hfov */
extern char s_sets_the_horizontal_field_of_view_004e8aa0[]; /* sets the horizontal field of view */
extern char s_auto_planes_004e8ac8[]; /* --auto-planes */
extern char s_find_automatically_near_and_far_cl_004e8ae0[]; /* find automatically near and far clipping planes */
extern char s_near_plane_004e8b10[]; /* --near-plane */
extern char s_sets_the_default_near_clipping_pla_004e8b20[]; /* sets the default near clipping plane */
extern char s_far_plane_004e8b48[]; /* --far-plane */
extern char s_sets_the_default_far_clipping_plan_004e8b60[]; /* sets the default far clipping plane */
extern char s_up_vector_004e8b88[]; /* --up-vector */
extern char s_sets_the_default_up_vector_0_0_0_m_004e8ba0[]; /* sets the default up vector (<0,0,0> means use scene up vector) */
extern char s_auto_scene_lights_004e8be0[]; /* --auto-scene-lights */
extern char s_sets_automatic_usage_of_scene_ligh_004e8c00[]; /* sets automatic usage of scene lights */
extern char s_auto_head_light_004e8c30[]; /* --auto-head-light */
extern char s_sets_automatic_usage_of_head_light_004e8c50[]; /* sets automatic usage of head light */
extern char s_use_scene_lights_004e8c80[]; /* --use-scene-lights */
extern char s_use_scene_lights_if_not_automatic_004e8ca0[]; /* use scene lights (if not automatic) */
extern char s_use_head_light_004e8cd0[]; /* --use-head-light */
extern char s_enable_head_light_if_not_automatic_004e8cf0[]; /* enable head light (if not automatic) */
extern char s_use_head_light_specular_004e8d20[]; /* --use-head-light-specular */
extern char s_use_specular_head_light_004e8d40[]; /* use specular head light */
extern char s_head_light_diffuse_004e8d60[]; /* --head-light-diffuse */
extern char s_sets_the_diffuse_color_for_the_hea_004e8d80[]; /* sets the diffuse color for the head light */
extern char s_head_light_specular_004e8db0[]; /* --head-light-specular */
extern char s_sets_the_specular_color_for_the_he_004e8dd0[]; /* sets the specular color for the head light */
extern char s_head_light_ambient_004e8e00[]; /* --head-light-ambient */
extern char s_sets_the_ambient_color_for_the_hea_004e8e20[]; /* sets the ambient color for the head light */
extern char s_clear_color_004e8e50[]; /* --clear-color */
extern char s_sets_the_clear_color_004e8e60[]; /* sets the clear color */
extern char s_wireframe_mode_004e8e80[]; /* --wireframe-mode */
extern char s_sets_wireframe_mode_004e8ea0[]; /* sets wireframe mode */
extern char s_force_wireframe_004e8ec0[]; /* --force-wireframe */
extern char s_force_wireframe_on_all_geometries_004e8ee0[]; /* force wireframe on all geometries */
extern char s_backface_culling_mode_004e8f10[]; /* --backface-culling-mode */
extern char s_sets_back_face_culling_mode_004e8f30[]; /* sets back-face culling mode */
extern char s_force_backface_culling_004e8f50[]; /* --force-backface-culling */
extern char s_force_back_face_culling_on_all_geo_004e8f70[]; /* force back-face culling on all geometries */
extern char s_alpha_test_004e8fa0[]; /* --alpha-test */
extern char s_sets_alpha_test_state_004e8fb0[]; /* sets alpha test state */
extern char s_force_alpha_test_004e8fd0[]; /* --force-alpha-test */
extern char s_force_alpha_test_on_all_geometries_004e8ff0[]; /* force alpha test on all geometries */
extern char s_alpha_test_reference_004e9020[]; /* --alpha-test-reference */
extern char s_sets_alpha_test_reference_value_004e9040[]; /* sets alpha test reference value */
extern char s_maximum_frame_rate_004e9060[]; /* --maximum-frame-rate */
extern char s_sets_the_maximum_frame_rate_0_mean_004e9080[]; /* sets the maximum frame rate (0 means no maximum) */
extern char s_optimize_textures_004e90c0[]; /* --optimize-textures */
extern char s_share_textures_at_load_time_004e90e0[]; /* share textures at load time */
extern char s_half_buffer_004e9100[]; /* --half-buffer */
extern char s_sets_psx2_half_buffer_mode_004e9110[]; /* sets PSX2 half-buffer mode */
extern char s_pal_video_mode_004e9130[]; /* --pal-video-mode */
extern char s_sets_pal_video_mode_004e9150[]; /* sets PAL video mode */
extern char s_width_004e9168[]; /* --width */
extern char s_viewer_window_width_004e9170[]; /* viewer window width */
extern char s_height_004e9188[]; /* --height */
extern char s_viewer_window_height_004e91a0[]; /* viewer window height */
extern char s_swap_interval_004e91c0[]; /* --swap-interval */
extern char s_sets_the_swap_interval_0_means_no__004e91d0[]; /* sets the swap interval (0 means no vsync) */
extern char s_color_bits_004e9200[]; /* --color-bits */
extern char s_sets_color_buffer_bits_1_means_def_004e9210[]; /* sets color buffer bits (-1 means default) */
extern char s_alpha_bits_004e9240[]; /* --alpha-bits */
extern char s_sets_alpha_buffer_bits_1_means_def_004e9250[]; /* sets alpha buffer bits (-1 means default) */
extern char s_depth_bits_004e9280[]; /* --depth-bits */
extern char s_sets_depth_buffer_bits_1_means_def_004e9290[]; /* sets depth buffer bits (-1 means default) */
extern char s_stencil_bits_004e92c0[]; /* --stencil-bits */
extern char s_sets_stencil_buffer_bits_1_means_d_004e92d0[]; /* sets stencil buffer bits (-1 means default) */
extern char s_report_video_format_004e9300[]; /* --report-video-format */
extern char s_if_set_reports_requested_and_actua_004e9320[]; /* if set, reports requested and actual video format */
extern char s_show_logo_004e9358[]; /* --show-logo */
extern char s_shows_alchemy_logo_004e9370[]; /* shows Alchemy logo */
extern char s_show_ui_004e9388[]; /* --show-ui */
extern char s_sets_initial_gui_visibility_004e93a0[]; /* sets initial GUI visibility */
extern char s_enable_maya_controls_004e93c0[]; /* --enable-maya-controls */
extern char s_enables_or_disable_maya_controls_004e93e0[]; /* enables or disable maya controls */
extern char s_benchmark_004e9408[]; /* --benchmark */
extern char s_enables_or_disable_the_benchmark_m_004e9420[]; /* enables or disable the benchmark mode */
extern char s_benchmark_skip_frames_004e9450[]; /* --benchmark-skip-frames */
extern char s_sets_the_number_of_frames_to_skip__004e9470[]; /* sets the number of frames to skip before benchmarking */
extern char s_benchmark_frames_004e94b0[]; /* --benchmark-frames */
extern char s_sets_the_number_of_frames_to_bench_004e94d0[]; /* sets the number of frames to benchmark */
extern char s_column_statistics_004e9500[]; /* --column-statistics */
extern char s_output_statistics_to_console_in_co_004e9520[]; /* Output statistics to console in comma-separated column form */
extern char s_allocate_visual_context_in_scratch_004e9560[]; /* --allocate-visual-context-in-scratchpad */
extern char s_allocate_visual_context_from_scrat_004e9590[]; /* Allocate visual context from scratchpad (effect on PS2 only) */

/* Constant initialisers the compiler emitted into .rodata for the all-zero local vectors of
 * the --up-vector and --head-light-ambient defaults (the other vectors are built with immediates). */
extern const float g_vec3Zero_004e1058[4];
extern const float g_vec4Zero_004e1170[4];

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
    float upVector[3];
    float normalsColor[4];
    float invalidNormalsColor[4];
    float scaledNormalsColor[4];
    float headLightDiffuse[4];
    float headLightSpecular[4];
    float headLightAmbient[4];
    float clearColor[4];
    printf(s_usage_s_option1_option2_n_number_f_004e87c0, programName);
    printf(s_n_number_loads_n_instances_of_the__004e8820);
    printf(s_possible_options_are_004e8850);
    printf(s_help_prints_this_message_004e8870);
    printf(s_nologo_removes_the_logo_display_004e8890);
    OPTION_BOOL(s_show_bbox_004e88b8, s_show_bounding_box_on_selected_obje_004e88d0, 1);
    OPTION_BOOL(s_show_normals_004e88f8, s_show_normals_on_selected_object_004e8910, 0.0f);
    if (s_normals_color_004e8930) {
        normalsColor[0] = 0.0f;
        normalsColor[1] = 1.0f;
        normalsColor[2] = 0.0f;
        normalsColor[3] = 1.0f;
        FUN_002343d0(s_normals_color_004e8930, s_sets_the_normals_color_004e8940, normalsColor);
    }
    if (s_invalid_stored_normals_color_004e8960) {
        invalidNormalsColor[0] = 1.0f;
        invalidNormalsColor[1] = 0.5f;
        invalidNormalsColor[2] = 0.0f;
        invalidNormalsColor[3] = 1.0f;
        FUN_002343d0(s_invalid_stored_normals_color_004e8960, s_sets_the_non_normalized_stored_nor_004e8980, invalidNormalsColor);
    }
    if (s_scaled_normals_color_004e89b0) {
        scaledNormalsColor[0] = 1.0f;
        scaledNormalsColor[1] = 0.0f;
        scaledNormalsColor[2] = 0.0f;
        scaledNormalsColor[3] = 1.0f;
        FUN_002343d0(s_scaled_normals_color_004e89b0, s_sets_the_scaled_normals_color_004e89d0, scaledNormalsColor);
    }
    OPTION_FLOAT(s_invalid_normals_precision_004e89f0, s_sets_the_precision_on_the_normals__004e8a10, GPR_005548c8);
    OPTION_BOOL(s_auto_select_camera_004e8a40, s_select_the_first_camera_if_any_in__004e8a60, 1);
    OPTION_FLOAT(s_hfov_004e8a90, s_sets_the_horizontal_field_of_view_004e8aa0, 45.0f);
    OPTION_BOOL(s_auto_planes_004e8ac8, s_find_automatically_near_and_far_cl_004e8ae0, 1);
    OPTION_FLOAT(s_near_plane_004e8b10, s_sets_the_default_near_clipping_pla_004e8b20, GPR_00554948);
    OPTION_FLOAT(s_far_plane_004e8b48, s_sets_the_default_far_clipping_plan_004e8b60, 1000.0f);
    if (s_up_vector_004e8b88) {
        upVector[0] = g_vec3Zero_004e1058[0];
        upVector[1] = g_vec3Zero_004e1058[1];
        upVector[2] = g_vec3Zero_004e1058[2];
        FUN_00234350(s_up_vector_004e8b88, s_sets_the_default_up_vector_0_0_0_m_004e8ba0, upVector);
    }
    OPTION_BOOL(s_auto_scene_lights_004e8be0, s_sets_automatic_usage_of_scene_ligh_004e8c00, 1);
    OPTION_BOOL(s_auto_head_light_004e8c30, s_sets_automatic_usage_of_head_light_004e8c50, 0.0f);
    OPTION_BOOL(s_use_scene_lights_004e8c80, s_use_scene_lights_if_not_automatic_004e8ca0, 0.0f);
    OPTION_BOOL(s_use_head_light_004e8cd0, s_enable_head_light_if_not_automatic_004e8cf0, 0.0f);
    OPTION_BOOL(s_use_head_light_specular_004e8d20, s_use_specular_head_light_004e8d40, 0.0f);
    if (s_head_light_diffuse_004e8d60) {
        headLightDiffuse[0] = 1.0f;
        headLightDiffuse[1] = 1.0f;
        headLightDiffuse[2] = 1.0f;
        headLightDiffuse[3] = 1.0f;
        FUN_002343d0(s_head_light_diffuse_004e8d60, s_sets_the_diffuse_color_for_the_hea_004e8d80, headLightDiffuse);
    }
    if (s_head_light_specular_004e8db0) {
        headLightSpecular[0] = 1.0f;
        headLightSpecular[1] = 1.0f;
        headLightSpecular[2] = 1.0f;
        headLightSpecular[3] = 1.0f;
        FUN_002343d0(s_head_light_specular_004e8db0, s_sets_the_specular_color_for_the_he_004e8dd0, headLightSpecular);
    }
    if (s_head_light_ambient_004e8e00) {
        headLightAmbient[0] = g_vec4Zero_004e1170[0];
        headLightAmbient[1] = g_vec4Zero_004e1170[1];
        headLightAmbient[2] = g_vec4Zero_004e1170[2];
        headLightAmbient[3] = g_vec4Zero_004e1170[3];
        FUN_002343d0(s_head_light_ambient_004e8e00, s_sets_the_ambient_color_for_the_hea_004e8e20, headLightAmbient);
    }
    if (s_clear_color_004e8e50) {
        clearColor[0] = GPR_00554968;
        clearColor[1] = GPR_00554968;
        clearColor[2] = GPR_00554968;
        clearColor[3] = 1.0f;
        FUN_002343d0(s_clear_color_004e8e50, s_sets_the_clear_color_004e8e60, clearColor);
    }
    OPTION_BOOL(s_wireframe_mode_004e8e80, s_sets_wireframe_mode_004e8ea0, 0.0f);
    OPTION_BOOL(s_force_wireframe_004e8ec0, s_force_wireframe_on_all_geometries_004e8ee0, 0.0f);
    OPTION_BOOL(s_backface_culling_mode_004e8f10, s_sets_back_face_culling_mode_004e8f30, 0.0f);
    OPTION_BOOL(s_force_backface_culling_004e8f50, s_force_back_face_culling_on_all_geo_004e8f70, 0.0f);
    OPTION_BOOL(s_alpha_test_004e8fa0, s_sets_alpha_test_state_004e8fb0, 0.0f);
    OPTION_BOOL(s_force_alpha_test_004e8fd0, s_force_alpha_test_on_all_geometries_004e8ff0, 0.0f);
    OPTION_FLOAT(s_alpha_test_reference_004e9020, s_sets_alpha_test_reference_value_004e9040, GPR_00554948);
    OPTION_FLOAT(s_maximum_frame_rate_004e9060, s_sets_the_maximum_frame_rate_0_mean_004e9080, 0.0f);
    OPTION_BOOL(s_optimize_textures_004e90c0, s_share_textures_at_load_time_004e90e0, 1);
    OPTION_BOOL(s_half_buffer_004e9100, s_sets_psx2_half_buffer_mode_004e9110, 0.0f);
    OPTION_BOOL(s_pal_video_mode_004e9130, s_sets_pal_video_mode_004e9150, 0.0f);
    OPTION_INT(s_width_004e9168, s_viewer_window_width_004e9170, 640);
    OPTION_INT(s_height_004e9188, s_viewer_window_height_004e91a0, 448);
    OPTION_INT(s_swap_interval_004e91c0, s_sets_the_swap_interval_0_means_no__004e91d0, 0.0f);
    OPTION_INT(s_color_bits_004e9200, s_sets_color_buffer_bits_1_means_def_004e9210, -1);
    OPTION_INT(s_alpha_bits_004e9240, s_sets_alpha_buffer_bits_1_means_def_004e9250, -1);
    OPTION_INT(s_depth_bits_004e9280, s_sets_depth_buffer_bits_1_means_def_004e9290, -1);
    OPTION_INT(s_stencil_bits_004e92c0, s_sets_stencil_buffer_bits_1_means_d_004e92d0, -1);
    OPTION_BOOL(s_report_video_format_004e9300, s_if_set_reports_requested_and_actua_004e9320, 1);
    OPTION_BOOL(s_show_logo_004e9358, s_shows_alchemy_logo_004e9370, 1);
    OPTION_BOOL(s_show_ui_004e9388, s_sets_initial_gui_visibility_004e93a0, 1);
    OPTION_BOOL(s_enable_maya_controls_004e93c0, s_enables_or_disable_maya_controls_004e93e0, 0.0f);
    OPTION_BOOL(s_benchmark_004e9408, s_enables_or_disable_the_benchmark_m_004e9420, 0.0f);
    OPTION_INT(s_benchmark_skip_frames_004e9450, s_sets_the_number_of_frames_to_skip__004e9470, 5);
    OPTION_INT(s_benchmark_frames_004e94b0, s_sets_the_number_of_frames_to_bench_004e94d0, 30);
    OPTION_BOOL(s_column_statistics_004e9500, s_output_statistics_to_console_in_co_004e9520, 0.0f);
    OPTION_BOOL(s_allocate_visual_context_in_scratch_004e9560, s_allocate_visual_context_from_scrat_004e9590, 0.0f);
}
