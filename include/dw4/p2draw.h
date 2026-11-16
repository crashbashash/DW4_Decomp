#ifndef DW4_P2DRAW_H
#define DW4_P2DRAW_H

#ifdef __cplusplus
extern "C" {
#endif

void p2DrawIndexedSprites(unsigned int count, unsigned short *indices);
void p2DrawIndexedTriangleFan(unsigned int count, unsigned short *indices);
void p2DrawIndexedTriangleStrip(unsigned int count, unsigned short *indices);
void p2DrawIndexedTriangles(unsigned int count, unsigned short *indices);
void p2DrawLineStrip(unsigned int count);
void p2DrawLines(unsigned int count);
void p2DrawPoints(unsigned int count);
void p2DrawSprites(unsigned int count);
void p2DrawTriangleFan(unsigned int count);
void p2DrawTriangleStrip(unsigned int count);
void p2DrawTriangleStrips(int count, const int *lengths);
void p2DrawTriangles(unsigned int count);
void p2SetTexCoordArray(int unit, const float *texCoords);
void p2SetVertexArrays(const float *positions, const float *normals, const unsigned int *colours, const float *texCoords);

#ifdef __cplusplus
}
#endif

#endif
