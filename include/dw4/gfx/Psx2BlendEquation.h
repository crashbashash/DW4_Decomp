#ifndef DW4_PSX2BLENDEQUATION_H
#define DW4_PSX2BLENDEQUATION_H

/* One row of the PS2 blend-equation tables igPsx2VisualContext keeps: for a source blend function (the table
 * entry) and a destination blend function (the row), the GS ALPHA register's A, B, C and D selectors and its FIX
 * value, the arguments of p2SetBlendEquation. fix is -1 when the pair has no equation and -2 when it is the
 * blend constant of the stage. */
struct Psx2BlendEquation {
    int a;
    int b;
    int c;
    int d;
    int fix;
};

#endif
