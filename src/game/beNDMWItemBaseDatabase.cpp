/* The selector's empty assembler directive keeps JAL/return rather than a tail transfer without
 * emitting a word (matching construct). */
#include "dw4/reflected.h"
extern "C" {
extern char DATABASE_2[], GETDATABASE_2[], abChip[];
void beMessenger_SendNamed(void *, const char *, const char *, int, const char *);
void *beMessenger_GetObject(void *, int);
long long beDataBase_GetRecordInt(beDataBase *, int, const char *);
unsigned long long beDataBase_GetRecordBool(beDataBase *, int, const char *);
char *beDataBase_GetRecordString(beDataBase *, int, const char *);
beDataBase *beNDMWItemBase_RequestDataBase(beNDMWItemBase *, beNDMWStatus *, const char *);
long long beNDMWItemBase_GetRecordInt(beNDMWItemBase *, beNDMWStatus *, const char *);
unsigned long long beNDMWItemBase_GetRecordBool(beNDMWItemBase *, beNDMWStatus *, const char *);
char *beNDMWItemBase_GetRecordString(beNDMWItemBase *, beNDMWStatus *, const char *);
beDataBase *Gap__Bec__beNDMWItemAbilityChip__vfunc_21(beNDMWItemAbilityChip *, beNDMWStatus *);
}
/* Dispatch-only ABI projection. MW's two-word vtable prefix plus 21 slots gives 92. */
class ItemDatabaseDispatch {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual beDataBase *databaseForStatus(beNDMWStatus *);
};

/* Send "DATABASE <name>" / "GETDATABASE" to the status messenger and return the database object it
 * answers with. */
beDataBase *beNDMWItemBase_RequestDataBase(beNDMWItemBase *self, beNDMWStatus *status,
                                           const char *name) {
    void *messenger = (void *)status->_messenger;
    beMessenger_SendNamed(messenger, DATABASE_2, name, 0, GETDATABASE_2);
    return (beDataBase *)beMessenger_GetObject(messenger, 0);
}

long long beNDMWItemBase_GetRecordInt(beNDMWItemBase *self, beNDMWStatus *status, const char *key) {
    return beDataBase_GetRecordInt(((ItemDatabaseDispatch *)self)->databaseForStatus(status),
                                   self->_recNo, key);
}

unsigned long long beNDMWItemBase_GetRecordBool(beNDMWItemBase *self, beNDMWStatus *status,
                                                const char *key) {
    return beDataBase_GetRecordBool(((ItemDatabaseDispatch *)self)->databaseForStatus(status),
                                    self->_recNo, key);
}

char *beNDMWItemBase_GetRecordString(beNDMWItemBase *self, beNDMWStatus *status, const char *key) {
    return beDataBase_GetRecordString(((ItemDatabaseDispatch *)self)->databaseForStatus(status),
                                      self->_recNo, key);
}

/* The ability-chip item's database is the "abChip" table. */
beDataBase *Gap__Bec__beNDMWItemAbilityChip__vfunc_21(beNDMWItemAbilityChip *self,
                                                      beNDMWStatus *status) {
    beDataBase *result = beNDMWItemBase_RequestDataBase((beNDMWItemBase *)self, status, abChip);


    return result;
}
