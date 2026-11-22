#ifndef DW4_IGCOMPONENTEDITINFO2_H
#define DW4_IGCOMPONENTEDITINFO2_H

/* The colour layouts a locked colour component can be in (alchemy-kit_202309 igMath/igMath.h). */
enum IG_MATH_COLORSPACE_FORMAT {
    IG_MATH_COLORSPACE_FORMAT_ABGR,
    IG_MATH_COLORSPACE_FORMAT_RGBA,
    IG_MATH_COLORSPACE_FORMAT_ARGB,
    IG_MATH_COLORSPACE_FORMAT_BGR,
    IG_MATH_COLORSPACE_FORMAT_RGB,
    IG_MATH_COLORSPACE_FORMAT_HSV,
    IG_MATH_COLORSPACE_FORMAT_BGRA
};

/* One component of a vertex stream locked for editing (alchemy-kit_202309 igGfx/igVertexArray2.h, igVertexStream's
 * getEditableComponent): the caller names the component type, the first vertex, the component index and the vertex
 * count, and the stream fills in the data pointer and stride. DW4's record is the kit's first seven fields. */
struct igComponentEditInfo2 {
    int _componentType;
    unsigned int _startIndex;
    unsigned int _numComponents;
    unsigned int _componentIndex;
    void *_componentData;
    unsigned int _stride;
    IG_MATH_COLORSPACE_FORMAT _colorFormat;
};

#endif
