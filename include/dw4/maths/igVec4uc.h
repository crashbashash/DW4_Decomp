#ifndef DW4_IGVEC4UC_H
#define DW4_IGVEC4UC_H

#ifdef __cplusplus
/* Alchemy's four-byte vector: an array of four unsigned chars (Alchemy 5.0 kit, igMath/igVec4uc.h), also a packed
 * colour, the element of igVec4ucList. */
class igVec4uc {
public:
    unsigned char vec[4];

    igVec4uc() {}
    igVec4uc(const igVec4uc &vector) {
        vec[0] = vector.vec[0];
        vec[1] = vector.vec[1];
        vec[2] = vector.vec[2];
        vec[3] = vector.vec[3];
    }
    igVec4uc &operator=(const igVec4uc &vector) {
        vec[0] = vector.vec[0];
        vec[1] = vector.vec[1];
        vec[2] = vector.vec[2];
        vec[3] = vector.vec[3];
        return *this;
    }
    unsigned char &operator[](int idx) { return vec[idx]; }
    const unsigned char &operator[](int idx) const { return vec[idx]; }
};
#endif

#endif
