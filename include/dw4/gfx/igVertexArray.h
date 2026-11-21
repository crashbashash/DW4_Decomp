#ifndef DW4_IGVERTEXARRAY_H
#define DW4_IGVERTEXARRAY_H

struct igMetaObject;
struct igVertexArray;
class igVertexFormat;
struct igVec2f;
struct igVec3f;
struct igVec4f;

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "dw4/core/igSmartPointer.h"

/* igVertexArray's per-vertex accessors (vtable slots 29-56): each array has a setter and, one slot later, a getter. */
class igVertexArrayAccess : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23();
    /* Allocates the arrays `format` names for `vertexCount` vertices from `pool`. */
    virtual void configure(igVertexFormat *format, unsigned int vertexCount, unsigned int count2, int pool);
    virtual void d25(); virtual void d26();
    virtual void d27(); virtual void d28();
    virtual void setPosition(unsigned int index, igVec3f *position);
    virtual void getPosition(unsigned int index, igVec3f *position);
    virtual void d31();
    virtual void setNormal(unsigned int index, igVec3f *normal);
    virtual void getNormal(unsigned int index, igVec3f *normal);
    virtual void d34();
    virtual void v35(unsigned int index, igVec4f *value);
    virtual void v36(unsigned int index, igVec4f *value);
    virtual void d37();
    virtual void v38(unsigned int index, igVec4f *value);
    virtual void v39(unsigned int index, igVec4f *value);
    virtual void d40();
    virtual void setColor(unsigned int index, unsigned int color);
    virtual void d42();
    virtual unsigned int getColor(unsigned int index);
    virtual void d44();
    virtual void setWeight(unsigned int weight, unsigned int index, float value);
    virtual float getWeight(unsigned int weight, unsigned int index);
    virtual void d47();
    virtual void setBlendIndex(unsigned int blend, unsigned int index, unsigned char value);
    virtual int getBlendIndex(unsigned int blend, unsigned int index);
    virtual void setTextureCoord(unsigned int set, unsigned int index, igVec2f *coord);
    virtual void getTextureCoord(unsigned int set, unsigned int index, igVec2f *coord);
    virtual void d52();
    virtual void setPointSize(unsigned int index, float size);
    virtual float getPointSize(unsigned int index);
    virtual void setPointSize2(unsigned int index, igVec2f size);
    virtual void getPointSize2(unsigned int index, igVec2f *size);
};
#endif

#endif
