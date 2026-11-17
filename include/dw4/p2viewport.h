#ifndef DW4_P2VIEWPORT_H
#define DW4_P2VIEWPORT_H

#ifdef __cplusplus
extern "C" {
#endif

void p2SetViewport(int x, int y, int width, int height, float nearZ, float farZ);
void p2SetDepthBias(int bias);
void p2UploadViewport(void);

#ifdef __cplusplus
}
#endif

#endif
