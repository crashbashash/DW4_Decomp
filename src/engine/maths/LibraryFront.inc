const char *g_igMathSpatialRegionNames[] = {
    "IG_MATH_SPATIAL_REGION_XP_YP_ZP",
    "IG_MATH_SPATIAL_REGION_XP_YP_ZN",
    "IG_MATH_SPATIAL_REGION_XP_YN_ZP",
    "IG_MATH_SPATIAL_REGION_XP_YN_ZN",
    "IG_MATH_SPATIAL_REGION_XN_YP_ZP",
    "IG_MATH_SPATIAL_REGION_XN_YP_ZN",
    "IG_MATH_SPATIAL_REGION_XN_YN_ZP",
    "IG_MATH_SPATIAL_REGION_XN_YN_ZN",
};

int g_igMathSpatialRegionValues[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

igMetaEnum *g_igMathSpatialRegionMetaEnum;

igMetaEnum *FUN_001869e0(void) {
    if (g_igMathSpatialRegionMetaEnum == 0) {
        g_igMathSpatialRegionMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_MATH_SPATIAL_REGION", g_igMathSpatialRegionNames, g_igMathSpatialRegionValues, 8);
    }
    return g_igMathSpatialRegionMetaEnum;
}
