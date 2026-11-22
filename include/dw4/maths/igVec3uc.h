#ifndef DW4_IGVEC3UC_H
#define DW4_IGVEC3UC_H

#ifdef __cplusplus
/* Alchemy's three-byte vector: an array of three unsigned chars (Alchemy 5.0 kit, igMath/igVec3uc.h), the element of
 * igVec3ucList. */
class igVec3uc {
public:
    unsigned char vec[3];

    igVec3uc() {}
    igVec3uc(const igVec3uc &vector) {
        vec[0] = vector.vec[0];
        vec[1] = vector.vec[1];
        vec[2] = vector.vec[2];
    }
    igVec3uc &operator=(const igVec3uc &vector) {
        vec[0] = vector.vec[0];
        vec[1] = vector.vec[1];
        vec[2] = vector.vec[2];
        return *this;
    }
    unsigned char &operator[](int idx) { return vec[idx]; }
    const unsigned char &operator[](int idx) const { return vec[idx]; }
};
#endif

#endif
