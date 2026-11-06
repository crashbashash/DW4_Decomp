/* Resets a 101-byte stream-information block to its defaults. */

struct Info0028ad38 {
    int f0; /* +0 */
    int f4; /* +4 */
    int f8; /* +8 */
    int f12; /* +12 */
    int f16; /* +16 */
    int f20; /* +20 */
    int f24; /* +24 */
    int f28; /* +28 */
    int f32; /* +32 */
    int f36; /* +36 */
    int f40; /* +40 */
    int f44; /* +44 */
    int f48; /* +48 */
    int f52; /* +52 */
    int f56; /* +56 */
    int f60; /* +60 */
    int f64; /* +64 */
    int f68; /* +68 */
    int f72; /* +72 */
    int f76; /* +76 */
    short f80; /* +80 */
    short f82; /* +82 */
    signed char f84; /* +84 */
    signed char f85; /* +85 */
    signed char f86; /* +86 */
    signed char f87; /* +87 */
    signed char f88; /* +88 */
    signed char f89; /* +89 */
    signed char f90; /* +90 */
    signed char f91; /* +91 */
    signed char f92; /* +92 */
    signed char f93; /* +93 */
    signed char f94; /* +94 */
    signed char f95; /* +95 */
    signed char f96; /* +96 */
    signed char f97; /* +97 */
    signed char f98; /* +98 */
    signed char f99; /* +99 */
    signed char f100; /* +100 */
};

void FUN_0028ad38(struct Info0028ad38 *info) {
    info->f0 = 0;
    info->f4 = 0;
    info->f8 = 0;
    info->f12 = 0;
    info->f16 = 0;
    info->f20 = 0;
    info->f24 = 0;
    info->f28 = 0;
    info->f32 = 0;
    info->f36 = 0;
    info->f40 = 0;
    info->f44 = 0;
    info->f48 = 0;
    info->f52 = 0;
    info->f56 = 3;
    info->f60 = 1;
    info->f64 = 0;
    info->f68 = 1;
    info->f72 = 0;
    info->f76 = 0;
    info->f80 = -1;
    info->f82 = -1;
    info->f84 = 0;
    info->f85 = 1;
    info->f86 = 0;
    info->f87 = 0;
    info->f88 = 0;
    info->f89 = 1;
    info->f90 = 0;
    info->f91 = 0;
    info->f92 = 0;
    info->f93 = -1;
    info->f94 = 0;
    info->f95 = -1;
    info->f96 = -1;
    info->f97 = 0;
    info->f98 = -1;
    info->f99 = -1;
    info->f100 = -1;
}
