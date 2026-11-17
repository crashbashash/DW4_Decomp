#ifndef DW4_BENDMWLOADCTRL2_H
#define DW4_BENDMWLOADCTRL2_H

/* One row of the player-model table: the model name and the open and face sequences its face
 * window plays. */
struct PlayerModelRow {
    const char *model;
    const char *openSequence;
    const char *faceSequence;
};
struct beNDMWLoadCtrl2;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWLoadCtrl2_metaObject;
extern PlayerModelRow g_playerModelRow[17];
beNDMWLoadCtrl2 *beNDMWLoadCtrl2_CreateInstance(int allocator);
}

#endif
