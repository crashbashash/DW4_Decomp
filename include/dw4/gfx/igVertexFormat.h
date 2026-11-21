#ifndef DW4_IGVERTEXFORMAT_H
#define DW4_IGVERTEXFORMAT_H

#ifdef __cplusplus
/* The kit's vertex format (alchemy-kit_202309 include/igGfx/igVertexArray.h): one flags word saying which
 * components each vertex of an array holds. Bits 0-2 positions, normals and colours; bits 4-7 the blend weights
 * per vertex, 8-11 the blend matrix indices, 16-19 the texture coordinate sets, 20-21 the point-sprite size
 * components (2 with a height, 1 with a width only); bits 22 and 23 binormals and tangents, bit 24 a rotating
 * sprite. */
class igVertexFormat {
    friend class igVertexComponentFilter;

public:
    inline igVertexFormat() : _flags(0) {}
    inline igVertexFormat(unsigned int flags) : _flags(flags) {}
    inline igVertexFormat(const igVertexFormat &vertexFormat) { _flags = vertexFormat._flags; }

    inline unsigned int getFlags() const { return _flags; }
    inline bool operator==(const igVertexFormat &v) const { return _flags == v._flags; }
    inline bool operator!=(const igVertexFormat &v) const { return _flags != v._flags; }
    bool empty() { return _flags == 0; }

    inline void setHasPositions(bool hasPosition)
    {
        const unsigned int mask = POSITION_MASK;
        if (hasPosition) {
            _flags |= (1 << POSITION_SHIFT);
        } else {
            _flags &= ~mask;
        }
    }
    inline bool hasPositions() const { return (_flags & POSITION_MASK) != 0; }
    inline void setHasNormals(bool hasNormals)
    {
        const unsigned int mask = NORMAL_MASK;
        if (hasNormals) {
            _flags |= (1 << NORMAL_SHIFT);
        } else {
            _flags &= ~mask;
        }
    }
    inline bool hasNormals() const { return (_flags & NORMAL_MASK) != 0; }
    inline void setHasVertexColors(bool hasVertexColors)
    {
        const unsigned int mask = COLOR_MASK;
        if (hasVertexColors) {
            _flags |= (1 << COLOR_SHIFT);
        } else {
            _flags &= ~mask;
        }
    }
    inline bool hasVertexColors() const { return (_flags & COLOR_MASK) != 0; }
    inline void setTextureCoordCount(unsigned char textureCoordCountParam)
    {
        const unsigned int mask = TEXTURE_COORD_MASK;
        _flags &= ~mask;
        _flags |= (unsigned int)(textureCoordCountParam << TEXTURE_COORD_SHIFT);
    }
    inline unsigned char getTextureCoordCount() const
    {
        return (unsigned char)((_flags & TEXTURE_COORD_MASK) >> TEXTURE_COORD_SHIFT);
    }
    inline void setBlendWeightCount(unsigned char blendWeightCountParam)
    {
        const unsigned int mask = BLEND_WEIGHT_MASK;
        _flags &= ~mask;
        _flags |= (unsigned int)(blendWeightCountParam << BLEND_WEIGHT_SHIFT);
    }
    inline unsigned char getBlendWeightCount() const
    {
        return (unsigned char)((_flags & BLEND_WEIGHT_MASK) >> BLEND_WEIGHT_SHIFT);
    }
    inline void setBlendIndexCount(unsigned char blendMatricesCountParam)
    {
        const unsigned int mask = BLEND_INDEX_MASK;
        _flags &= ~mask;
        _flags |= (unsigned int)(blendMatricesCountParam << BLEND_INDEX_SHIFT);
    }
    inline unsigned char getBlendIndexCount() const
    {
        return (unsigned char)((_flags & BLEND_INDEX_MASK) >> BLEND_INDEX_SHIFT);
    }
    inline void setPointSpriteCoordCount(unsigned char coordCount)
    {
        const unsigned int mask = POINT_SPRITE_SIZE_MASK;
        if (coordCount) {
            _flags &= ~mask;
            _flags |= (unsigned int)(coordCount << POINT_SPRITE_SIZE_SHIFT);
        } else {
            _flags &= ~mask;
        }
    }
    inline unsigned char getPointSpriteCoordCount() const
    {
        return (unsigned char)((_flags & POINT_SPRITE_SIZE_MASK) >> POINT_SPRITE_SIZE_SHIFT);
    }
    inline void setHasBinormals(bool hasBinormals)
    {
        const unsigned int mask = BINORMAL_MASK;
        if (hasBinormals) {
            _flags |= (1 << BINORMAL_SHIFT);
        } else {
            _flags &= ~mask;
        }
    }
    inline bool hasBinormals() const { return (_flags & BINORMAL_MASK) != 0; }
    inline void setHasTangents(bool hasTangents)
    {
        const unsigned int mask = TANGENT_MASK;
        if (hasTangents) {
            _flags |= (1 << TANGENT_SHIFT);
        } else {
            _flags &= ~mask;
        }
    }
    inline bool hasTangents() const { return (_flags & TANGENT_MASK) != 0; }
    inline void setHasSpriteRadians(bool hasRotations)
    {
        const unsigned int mask = ROTATION_MASK;
        if (hasRotations) {
            _flags |= (1 << ROTATION_SHIFT);
        } else {
            _flags &= ~mask;
        }
    }
    inline bool hasSpriteRadians() const { return (_flags & ROTATION_MASK) != 0; }
    inline void clear() { _flags = 0; }

    igVertexFormat operator&(const igVertexFormat &vertexFormat) const;
    igVertexFormat operator|(const igVertexFormat &vertexFormat) const;

private:
    unsigned int _flags;

protected:
    enum BIT_SHIFTS {
        POSITION_SHIFT = 0,
        NORMAL_SHIFT = 1,
        COLOR_SHIFT = 2,
        BLEND_WEIGHT_SHIFT = 4,
        BLEND_INDEX_SHIFT = 8,
        TEXTURE_COORD_SHIFT = 16,
        POINT_SPRITE_SIZE_SHIFT = 20,
        BINORMAL_SHIFT = 22,
        TANGENT_SHIFT = 23,
        ROTATION_SHIFT = 24
    };
    enum BIT_MASKS {
        POSITION_MASK = 0x00000001,
        NORMAL_MASK = 0x00000002,
        COLOR_MASK = 0x00000004,
        BLEND_WEIGHT_MASK = 0x000000F0,
        BLEND_INDEX_MASK = 0x00000F00,
        TEXTURE_COORD_MASK = 0x000F0000,
        POINT_SPRITE_SIZE_MASK = 0x00300000,
        BINORMAL_MASK = 0x00400000,
        TANGENT_MASK = 0x00800000,
        ROTATION_MASK = 0x01000000
    };
};
#endif

#endif
