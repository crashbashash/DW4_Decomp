igMetaObject *g_igPsx2Image_metaObject;

void igPsx2Image_GetMetaObjectFunction(void) {
    igPsx2Image_GetMetaObject();
}

void thunk_FUN_00156300(void) {
    FUN_00156300();
}

static const char *g_igPsx2Image_contextTrackableNames[] = {
    "TRACK_PROJECTION_MODELVIEW", "TRACK_PROJECTION", "TRACK_MODELVIEW", "TRACK_TEXTURE_0",
    "TRACK_TEXTURE_1", "TRACK_TEXTURE_2", "TRACK_TEXTURE_3", "TRACK_TEXTURE_4",
    "TRACK_TEXTURE_5", "TRACK_TEXTURE_6", "TRACK_TEXTURE_7", "TRACK_VERTEX_BLEND_0",
    "TRACK_VERTEX_BLEND_1", "TRACK_VERTEX_BLEND_2", "TRACK_VERTEX_BLEND_3", "TRACK_VERTEX_BLEND_MATRICES",
    "TRACK_DIRECTIONAL_LIGHT_BUNDLE", "TRACK_POINT_LIGHT_BUNDLE", "TRACK_AMBIENT_LIGHT", "TRACK_DIRECTIONAL_LIGHT_BUNDLE_WORLD",
    "TRACK_POINT_LIGHT_BUNDLE_WORLD", "TRACK_TRACKABLE_COUNT",
};
static int g_igPsx2Image_contextTrackableValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
};
igMetaEnum *g_igPsx2Image_contextTrackableMetaEnum;

int CONTEXT_TRACKABLE_GetMetaEnum(void) {
    if (g_igPsx2Image_contextTrackableMetaEnum == 0) {
        g_igPsx2Image_contextTrackableMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("CONTEXT_TRACKABLE", g_igPsx2Image_contextTrackableNames, g_igPsx2Image_contextTrackableValues, 22);
    }
    return (int)g_igPsx2Image_contextTrackableMetaEnum;
}

