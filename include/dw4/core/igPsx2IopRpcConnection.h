#ifndef DW4_IGPSX2IOPRPCCONNECTION_H
#define DW4_IGPSX2IOPRPCCONNECTION_H

#include "dw4/core/igResult.h"

struct igMetaObject;
struct igPsx2IopRpcConnectionView;

extern "C" {

struct igPsx2IopRpcConnectionView *igPsx2IopRpcConnection_Create(int pool);
igMetaObject *igPsx2IopRpcConnection_GetOrCreateMetaObject(void);
void igPsx2IopRpcConnection_EnsureRegistered(void);
igResult igPsx2IopRpcConnection_Bind(struct igPsx2IopRpcConnectionView *self, int serverId);
igResult igPsx2IopRpcConnection_Call(struct igPsx2IopRpcConnectionView *self, int function, void *send, int sendSize, void *receive, int receiveSize, int wait);
igResult igPsx2IopRpcConnection_CallWithData(struct igPsx2IopRpcConnectionView *self, int function, int data, int *reply, int noWait);
igResult igPsx2IopRpcConnection_CallNoData(struct igPsx2IopRpcConnectionView *self, int function, int blocking);

}

#endif
