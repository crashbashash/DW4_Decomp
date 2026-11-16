#ifndef DW4_IGMODEL_H
#define DW4_IGMODEL_H

struct igModel;
struct igMetaField;

/* A change record igModel_NotifyViews hands to each of the model's views except `source`: type 2
 * reports that the field `field` changed. */
struct ModelChange {
    int type;
    void *source;
    struct igMetaField *field;
    int reserved;
};

#ifdef __cplusplus
extern "C" {
#endif

void igModel_Register(void);
void igModel_NotifyViews(struct igModel *model, struct ModelChange *change);

#ifdef __cplusplus
}
#endif

#endif
