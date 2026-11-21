#ifndef DW4_IGVERTEXCOMPONENTFILTER_H
#define DW4_IGVERTEXCOMPONENTFILTER_H

#ifdef __cplusplus
/* The kit's vertex component mask (alchemy-kit_202309 include/igGfx/igVertexArray.h): a vertex format's flags,
 * all set by default. igGeometryMaskAttr keeps it as its _mask word; igVisualContext's getVertexMask returns it.
 * The kit wraps the word in an igVertexFormat, whose other members DW4 does not use here. */
class igVertexComponentFilter {
public:
    igVertexComponentFilter() { _vertexFormat._flags = 0xFFFFFFFF; }
    igVertexComponentFilter(unsigned int flags) { _vertexFormat._flags = flags; }
    inline operator unsigned int() { return _vertexFormat._flags; }

protected:
    struct { unsigned int _flags; } _vertexFormat;
};
#endif

#endif
