	.set	noreorder

	.text
	.align	2

	.globl	RFU000_FullReset
	.ent	RFU000_FullReset
RFU000_FullReset:
	li	$3,0
	syscall
	jr	$31
	nop
	.end	RFU000_FullReset

	.globl	ResetEE
	.ent	ResetEE
ResetEE:
	li	$3,1
	syscall
	jr	$31
	nop
	.end	ResetEE

	.globl	SetGsCrt
	.ent	SetGsCrt
SetGsCrt:
	li	$3,2
	syscall
	jr	$31
	nop
	.end	SetGsCrt

	.globl	RFU003
	.ent	RFU003
RFU003:
	li	$3,3
	syscall
	jr	$31
	nop
	.end	RFU003

	.globl	_Exit
	.ent	_Exit
_Exit:
	li	$3,4
	syscall
	jr	$31
	nop
	.end	_Exit

	.globl	RFU005
	.ent	RFU005
RFU005:
	li	$3,5
	syscall
	jr	$31
	nop
	.end	RFU005

	.globl	_LoadExecPS2
	.ent	_LoadExecPS2
_LoadExecPS2:
	li	$3,6
	syscall
	jr	$31
	nop
	.end	_LoadExecPS2

	.globl	_ExecPS2
	.ent	_ExecPS2
_ExecPS2:
	li	$3,7
	syscall
	jr	$31
	nop
	.end	_ExecPS2

	.globl	RFU008
	.ent	RFU008
RFU008:
	li	$3,8
	syscall
	jr	$31
	nop
	.end	RFU008

	.globl	RFU009
	.ent	RFU009
RFU009:
	li	$3,9
	syscall
	jr	$31
	nop
	.end	RFU009

	.globl	AddSbusIntcHandler
	.ent	AddSbusIntcHandler
AddSbusIntcHandler:
	li	$3,10
	syscall
	jr	$31
	nop
	.end	AddSbusIntcHandler

	.globl	RemoveSbusIntcHandler
	.ent	RemoveSbusIntcHandler
RemoveSbusIntcHandler:
	li	$3,11
	syscall
	jr	$31
	nop
	.end	RemoveSbusIntcHandler

	.globl	Interrupt2Iop
	.ent	Interrupt2Iop
Interrupt2Iop:
	li	$3,12
	syscall
	jr	$31
	nop
	.end	Interrupt2Iop

	.globl	SetVTLBRefillHandler
	.ent	SetVTLBRefillHandler
SetVTLBRefillHandler:
	li	$3,13
	syscall
	jr	$31
	nop
	.end	SetVTLBRefillHandler

	.globl	SetVCommonHandler
	.ent	SetVCommonHandler
SetVCommonHandler:
	li	$3,14
	syscall
	jr	$31
	nop
	.end	SetVCommonHandler

	.globl	SetVInterruptHandler
	.ent	SetVInterruptHandler
SetVInterruptHandler:
	li	$3,15
	syscall
	jr	$31
	nop
	.end	SetVInterruptHandler

	.globl	AddIntcHandler
	.ent	AddIntcHandler
AddIntcHandler:
	li	$3,16
	syscall
	jr	$31
	nop
	.end	AddIntcHandler

	.globl	AddIntcHandler2
	.ent	AddIntcHandler2
AddIntcHandler2:
	li	$3,16
	syscall
	jr	$31
	nop
	.end	AddIntcHandler2

	.globl	RemoveIntcHandler
	.ent	RemoveIntcHandler
RemoveIntcHandler:
	li	$3,17
	syscall
	jr	$31
	nop
	.end	RemoveIntcHandler

	.globl	AddDmacHandler
	.ent	AddDmacHandler
AddDmacHandler:
	li	$3,18
	syscall
	jr	$31
	nop
	.end	AddDmacHandler

	.globl	AddDmacHandler2
	.ent	AddDmacHandler2
AddDmacHandler2:
	li	$3,18
	syscall
	jr	$31
	nop
	.end	AddDmacHandler2

	.globl	RemoveDmacHandler
	.ent	RemoveDmacHandler
RemoveDmacHandler:
	li	$3,19
	syscall
	jr	$31
	nop
	.end	RemoveDmacHandler

	.globl	_EnableIntc
	.ent	_EnableIntc
_EnableIntc:
	li	$3,20
	syscall
	jr	$31
	nop
	.end	_EnableIntc

	.globl	_DisableIntc
	.ent	_DisableIntc
_DisableIntc:
	li	$3,21
	syscall
	jr	$31
	nop
	.end	_DisableIntc

	.globl	_EnableDmac
	.ent	_EnableDmac
_EnableDmac:
	li	$3,22
	syscall
	jr	$31
	nop
	.end	_EnableDmac

	.globl	_DisableDmac
	.ent	_DisableDmac
_DisableDmac:
	li	$3,23
	syscall
	jr	$31
	nop
	.end	_DisableDmac

	.globl	SetAlarm
	.ent	SetAlarm
SetAlarm:
	li	$3,252
	syscall
	jr	$31
	nop
	.end	SetAlarm

	.globl	ReleaseAlarm
	.ent	ReleaseAlarm
ReleaseAlarm:
	li	$3,253
	syscall
	jr	$31
	nop
	.end	ReleaseAlarm

	.globl	_iEnableIntc
	.ent	_iEnableIntc
_iEnableIntc:
	li	$3,-26
	syscall
	jr	$31
	nop
	.end	_iEnableIntc

	.globl	_iDisableIntc
	.ent	_iDisableIntc
_iDisableIntc:
	li	$3,-27
	syscall
	jr	$31
	nop
	.end	_iDisableIntc

	.globl	_iEnableDmac
	.ent	_iEnableDmac
_iEnableDmac:
	li	$3,-28
	syscall
	jr	$31
	nop
	.end	_iEnableDmac

	.globl	_iDisableDmac
	.ent	_iDisableDmac
_iDisableDmac:
	li	$3,-29
	syscall
	jr	$31
	nop
	.end	_iDisableDmac

	.globl	iSetAlarm
	.ent	iSetAlarm
iSetAlarm:
	li	$3,-254
	syscall
	jr	$31
	nop
	.end	iSetAlarm

	.globl	iReleaseAlarm
	.ent	iReleaseAlarm
iReleaseAlarm:
	li	$3,-255
	syscall
	jr	$31
	nop
	.end	iReleaseAlarm

	.globl	CreateThread
	.ent	CreateThread
CreateThread:
	li	$3,32
	syscall
	jr	$31
	nop
	.end	CreateThread

	.globl	DeleteThread
	.ent	DeleteThread
DeleteThread:
	li	$3,33
	syscall
	jr	$31
	nop
	.end	DeleteThread

	.globl	_StartThread
	.ent	_StartThread
_StartThread:
	li	$3,34
	syscall
	jr	$31
	nop
	.end	_StartThread

	.globl	ExitThread
	.ent	ExitThread
ExitThread:
	li	$3,35
	syscall
	jr	$31
	nop
	.end	ExitThread

	.globl	ExitDeleteThread
	.ent	ExitDeleteThread
ExitDeleteThread:
	li	$3,36
	syscall
	jr	$31
	nop
	.end	ExitDeleteThread

	.globl	TerminateThread
	.ent	TerminateThread
TerminateThread:
	li	$3,37
	syscall
	jr	$31
	nop
	.end	TerminateThread

	.globl	iTerminateThread
	.ent	iTerminateThread
iTerminateThread:
	li	$3,-38
	syscall
	jr	$31
	nop
	.end	iTerminateThread

	.globl	DisableDispatchThread
	.ent	DisableDispatchThread
DisableDispatchThread:
	li	$3,39
	syscall
	jr	$31
	nop
	.end	DisableDispatchThread

	.globl	EnableDispatchThread
	.ent	EnableDispatchThread
EnableDispatchThread:
	li	$3,40
	syscall
	jr	$31
	nop
	.end	EnableDispatchThread

	.globl	ChangeThreadPriority
	.ent	ChangeThreadPriority
ChangeThreadPriority:
	li	$3,41
	syscall
	jr	$31
	nop
	.end	ChangeThreadPriority

	.globl	iChangeThreadPriority
	.ent	iChangeThreadPriority
iChangeThreadPriority:
	li	$3,-42
	syscall
	jr	$31
	nop
	.end	iChangeThreadPriority

	.globl	RotateThreadReadyQueue
	.ent	RotateThreadReadyQueue
RotateThreadReadyQueue:
	li	$3,43
	syscall
	jr	$31
	nop
	.end	RotateThreadReadyQueue

	.globl	_iRotateThreadReadyQueue
	.ent	_iRotateThreadReadyQueue
_iRotateThreadReadyQueue:
	li	$3,-44
	syscall
	jr	$31
	nop
	.end	_iRotateThreadReadyQueue

	.globl	ReleaseWaitThread
	.ent	ReleaseWaitThread
ReleaseWaitThread:
	li	$3,45
	syscall
	jr	$31
	nop
	.end	ReleaseWaitThread

	.globl	iReleaseWaitThread
	.ent	iReleaseWaitThread
iReleaseWaitThread:
	li	$3,-46
	syscall
	jr	$31
	nop
	.end	iReleaseWaitThread

	.globl	GetThreadId
	.ent	GetThreadId
GetThreadId:
	li	$3,47
	syscall
	jr	$31
	nop
	.end	GetThreadId

	.globl	ReferThreadStatus
	.ent	ReferThreadStatus
ReferThreadStatus:
	li	$3,48
	syscall
	jr	$31
	nop
	.end	ReferThreadStatus

	.globl	iReferThreadStatus
	.ent	iReferThreadStatus
iReferThreadStatus:
	li	$3,-49
	syscall
	jr	$31
	nop
	.end	iReferThreadStatus

	.globl	SleepThread
	.ent	SleepThread
SleepThread:
	li	$3,50
	syscall
	jr	$31
	nop
	.end	SleepThread

	.globl	WakeupThread
	.ent	WakeupThread
WakeupThread:
	li	$3,51
	syscall
	jr	$31
	nop
	.end	WakeupThread

	.globl	_iWakeupThread
	.ent	_iWakeupThread
_iWakeupThread:
	li	$3,-52
	syscall
	jr	$31
	nop
	.end	_iWakeupThread

	.globl	CancelWakeupThread
	.ent	CancelWakeupThread
CancelWakeupThread:
	li	$3,53
	syscall
	jr	$31
	nop
	.end	CancelWakeupThread

	.globl	iCancelWakeupThread
	.ent	iCancelWakeupThread
iCancelWakeupThread:
	li	$3,-54
	syscall
	jr	$31
	nop
	.end	iCancelWakeupThread

	.globl	SuspendThread
	.ent	SuspendThread
SuspendThread:
	li	$3,55
	syscall
	jr	$31
	nop
	.end	SuspendThread

	.globl	_iSuspendThread
	.ent	_iSuspendThread
_iSuspendThread:
	li	$3,-56
	syscall
	jr	$31
	nop
	.end	_iSuspendThread

	.globl	ResumeThread
	.ent	ResumeThread
ResumeThread:
	li	$3,57
	syscall
	jr	$31
	nop
	.end	ResumeThread

	.globl	iResumeThread
	.ent	iResumeThread
iResumeThread:
	li	$3,-58
	syscall
	jr	$31
	nop
	.end	iResumeThread

	.globl	JoinThread
	.ent	JoinThread
JoinThread:
	li	$3,59
	syscall
	jr	$31
	nop
	.end	JoinThread

	.globl	RFU060
	.ent	RFU060
RFU060:
	li	$3,60
	syscall
	jr	$31
	nop
	.end	RFU060

	.globl	RFU061
	.ent	RFU061
RFU061:
	li	$3,61
	syscall
	jr	$31
	nop
	.end	RFU061

	.globl	EndOfHeap
	.ent	EndOfHeap
EndOfHeap:
	li	$3,62
	syscall
	jr	$31
	nop
	.end	EndOfHeap

	.globl	RFU063
	.ent	RFU063
RFU063:
	li	$3,63
	syscall
	jr	$31
	nop
	.end	RFU063

	.globl	CreateSema
	.ent	CreateSema
CreateSema:
	li	$3,64
	syscall
	jr	$31
	nop
	.end	CreateSema

	.globl	DeleteSema
	.ent	DeleteSema
DeleteSema:
	li	$3,65
	syscall
	jr	$31
	nop
	.end	DeleteSema

	.globl	SignalSema
	.ent	SignalSema
SignalSema:
	li	$3,66
	syscall
	jr	$31
	nop
	.end	SignalSema

	.globl	iSignalSema
	.ent	iSignalSema
iSignalSema:
	li	$3,-67
	syscall
	jr	$31
	nop
	.end	iSignalSema

	.globl	WaitSema
	.ent	WaitSema
WaitSema:
	li	$3,68
	syscall
	jr	$31
	nop
	.end	WaitSema

	.globl	PollSema
	.ent	PollSema
PollSema:
	li	$3,69
	syscall
	jr	$31
	nop
	.end	PollSema

	.globl	iPollSema
	.ent	iPollSema
iPollSema:
	li	$3,-70
	syscall
	jr	$31
	nop
	.end	iPollSema

	.globl	ReferSemaStatus
	.ent	ReferSemaStatus
ReferSemaStatus:
	li	$3,71
	syscall
	jr	$31
	nop
	.end	ReferSemaStatus

	.globl	iReferSemaStatus
	.ent	iReferSemaStatus
iReferSemaStatus:
	li	$3,-72
	syscall
	jr	$31
	nop
	.end	iReferSemaStatus

	.globl	RFU073
	.ent	RFU073
RFU073:
	li	$3,73
	syscall
	jr	$31
	nop
	.end	RFU073

	.globl	SetOsdConfigParam
	.ent	SetOsdConfigParam
SetOsdConfigParam:
	li	$3,74
	syscall
	jr	$31
	nop
	.end	SetOsdConfigParam

	.globl	GetOsdConfigParam
	.ent	GetOsdConfigParam
GetOsdConfigParam:
	li	$3,75
	syscall
	jr	$31
	nop
	.end	GetOsdConfigParam

	.globl	GetGsHParam
	.ent	GetGsHParam
GetGsHParam:
	li	$3,76
	syscall
	jr	$31
	nop
	.end	GetGsHParam

	.globl	GetGsVParam
	.ent	GetGsVParam
GetGsVParam:
	li	$3,77
	syscall
	jr	$31
	nop
	.end	GetGsVParam

	.globl	SetGsHParam
	.ent	SetGsHParam
SetGsHParam:
	li	$3,78
	syscall
	jr	$31
	nop
	.end	SetGsHParam

	.globl	SetGsVParam
	.ent	SetGsVParam
SetGsVParam:
	li	$3,79
	syscall
	jr	$31
	nop
	.end	SetGsVParam

	.globl	RFU080_CreateEventFlag
	.ent	RFU080_CreateEventFlag
RFU080_CreateEventFlag:
	li	$3,80
	syscall
	jr	$31
	nop
	.end	RFU080_CreateEventFlag

	.globl	RFU081_DeleteEventFlag
	.ent	RFU081_DeleteEventFlag
RFU081_DeleteEventFlag:
	li	$3,81
	syscall
	jr	$31
	nop
	.end	RFU081_DeleteEventFlag

	.globl	RFU082_SetEventFlag
	.ent	RFU082_SetEventFlag
RFU082_SetEventFlag:
	li	$3,82
	syscall
	jr	$31
	nop
	.end	RFU082_SetEventFlag

	.globl	RFU083_iSetEventFlag
	.ent	RFU083_iSetEventFlag
RFU083_iSetEventFlag:
	li	$3,-83
	syscall
	jr	$31
	nop
	.end	RFU083_iSetEventFlag

	.globl	RFU084_ClearEventFlag
	.ent	RFU084_ClearEventFlag
RFU084_ClearEventFlag:
	li	$3,84
	syscall
	jr	$31
	nop
	.end	RFU084_ClearEventFlag

	.globl	RFU085_iClearEventFlag
	.ent	RFU085_iClearEventFlag
RFU085_iClearEventFlag:
	li	$3,-85
	syscall
	jr	$31
	nop
	.end	RFU085_iClearEventFlag

	.globl	RFU086_WaitEvnetFlag
	.ent	RFU086_WaitEvnetFlag
RFU086_WaitEvnetFlag:
	li	$3,86
	syscall
	jr	$31
	nop
	.end	RFU086_WaitEvnetFlag

	.globl	RFU087_PollEvnetFlag
	.ent	RFU087_PollEvnetFlag
RFU087_PollEvnetFlag:
	li	$3,87
	syscall
	jr	$31
	nop
	.end	RFU087_PollEvnetFlag

	.globl	RFU088_iPollEvnetFlag
	.ent	RFU088_iPollEvnetFlag
RFU088_iPollEvnetFlag:
	li	$3,-88
	syscall
	jr	$31
	nop
	.end	RFU088_iPollEvnetFlag

	.globl	RFU089_ReferEventFlagStatus
	.ent	RFU089_ReferEventFlagStatus
RFU089_ReferEventFlagStatus:
	li	$3,89
	syscall
	jr	$31
	nop
	.end	RFU089_ReferEventFlagStatus

	.globl	RFU090_iReferEventFlagStatus
	.ent	RFU090_iReferEventFlagStatus
RFU090_iReferEventFlagStatus:
	li	$3,-90
	syscall
	jr	$31
	nop
	.end	RFU090_iReferEventFlagStatus

	.globl	RFU091
	.ent	RFU091
RFU091:
	li	$3,91
	syscall
	jr	$31
	nop
	.end	RFU091

	.globl	EnableIntcHandler
	.ent	EnableIntcHandler
EnableIntcHandler:
	li	$3,92
	syscall
	jr	$31
	nop
	.end	EnableIntcHandler

	.globl	iEnableIntcHandler
	.ent	iEnableIntcHandler
iEnableIntcHandler:
	li	$3,-92
	syscall
	jr	$31
	nop
	.end	iEnableIntcHandler

	.globl	DisableIntcHandler
	.ent	DisableIntcHandler
DisableIntcHandler:
	li	$3,93
	syscall
	jr	$31
	nop
	.end	DisableIntcHandler

	.globl	iDisableIntcHandler
	.ent	iDisableIntcHandler
iDisableIntcHandler:
	li	$3,-93
	syscall
	jr	$31
	nop
	.end	iDisableIntcHandler

	.globl	EnableDmacHandler
	.ent	EnableDmacHandler
EnableDmacHandler:
	li	$3,94
	syscall
	jr	$31
	nop
	.end	EnableDmacHandler

	.globl	iEnableDmacHandler
	.ent	iEnableDmacHandler
iEnableDmacHandler:
	li	$3,-94
	syscall
	jr	$31
	nop
	.end	iEnableDmacHandler

	.globl	DisableDmacHandler
	.ent	DisableDmacHandler
DisableDmacHandler:
	li	$3,95
	syscall
	jr	$31
	nop
	.end	DisableDmacHandler

	.globl	iDisableDmacHandler
	.ent	iDisableDmacHandler
iDisableDmacHandler:
	li	$3,-95
	syscall
	jr	$31
	nop
	.end	iDisableDmacHandler

	.globl	KSeg0
	.ent	KSeg0
KSeg0:
	li	$3,96
	syscall
	jr	$31
	nop
	.end	KSeg0

	.globl	EnableCache
	.ent	EnableCache
EnableCache:
	li	$3,97
	syscall
	jr	$31
	nop
	.end	EnableCache

	.globl	DisableCache
	.ent	DisableCache
DisableCache:
	li	$3,98
	syscall
	jr	$31
	nop
	.end	DisableCache

	.globl	GetCop0
	.ent	GetCop0
GetCop0:
	li	$3,99
	syscall
	jr	$31
	nop
	.end	GetCop0

	.globl	FlushCache
	.ent	FlushCache
FlushCache:
	li	$3,100
	syscall
	jr	$31
	nop
	.end	FlushCache

	.globl	CpuConfig
	.ent	CpuConfig
CpuConfig:
	li	$3,102
	syscall
	jr	$31
	nop
	.end	CpuConfig

	.globl	iGetCop0
	.ent	iGetCop0
iGetCop0:
	li	$3,-103
	syscall
	jr	$31
	nop
	.end	iGetCop0

	.globl	iFlushCache
	.ent	iFlushCache
iFlushCache:
	li	$3,-104
	syscall
	jr	$31
	nop
	.end	iFlushCache

	.globl	iCpuConfig
	.ent	iCpuConfig
iCpuConfig:
	li	$3,-106
	syscall
	jr	$31
	nop
	.end	iCpuConfig

	.globl	sceSifStopDma
	.ent	sceSifStopDma
sceSifStopDma:
	li	$3,107
	syscall
	jr	$31
	nop
	.end	sceSifStopDma

	.globl	SetCPUTimerHandler
	.ent	SetCPUTimerHandler
SetCPUTimerHandler:
	li	$3,108
	syscall
	jr	$31
	nop
	.end	SetCPUTimerHandler

	.globl	SetCPUTimer
	.ent	SetCPUTimer
SetCPUTimer:
	li	$3,109
	syscall
	jr	$31
	nop
	.end	SetCPUTimer

	.globl	SetOsdConfigParam2
	.ent	SetOsdConfigParam2
SetOsdConfigParam2:
	li	$3,110
	syscall
	jr	$31
	nop
	.end	SetOsdConfigParam2

	.globl	GetOsdConfigParam2
	.ent	GetOsdConfigParam2
GetOsdConfigParam2:
	li	$3,111
	syscall
	jr	$31
	nop
	.end	GetOsdConfigParam2

	.globl	GsGetIMR
	.ent	GsGetIMR
GsGetIMR:
	li	$3,112
	syscall
	jr	$31
	nop
	.end	GsGetIMR

	.globl	iGsGetIMR
	.ent	iGsGetIMR
iGsGetIMR:
	li	$3,-112
	syscall
	jr	$31
	nop
	.end	iGsGetIMR

	.globl	GsPutIMR
	.ent	GsPutIMR
GsPutIMR:
	li	$3,113
	syscall
	jr	$31
	nop
	.end	GsPutIMR

	.globl	iGsPutIMR
	.ent	iGsPutIMR
iGsPutIMR:
	li	$3,-113
	syscall
	jr	$31
	nop
	.end	iGsPutIMR

	.globl	SetPgifHandler
	.ent	SetPgifHandler
SetPgifHandler:
	li	$3,114
	syscall
	jr	$31
	nop
	.end	SetPgifHandler

	.globl	SetVSyncFlag
	.ent	SetVSyncFlag
SetVSyncFlag:
	li	$3,115
	syscall
	jr	$31
	nop
	.end	SetVSyncFlag

	.globl	RFU116
	.ent	RFU116
RFU116:
	li	$3,116
	syscall
	jr	$31
	nop
	.end	RFU116

	.globl	_print
	.ent	_print
_print:
	li	$3,117
	syscall
	jr	$31
	nop
	.end	_print

	.globl	sceSifDmaStat
	.ent	sceSifDmaStat
sceSifDmaStat:
	li	$3,118
	syscall
	jr	$31
	nop
	.end	sceSifDmaStat

	.globl	isceSifDmaStat
	.ent	isceSifDmaStat
isceSifDmaStat:
	li	$3,-118
	syscall
	jr	$31
	nop
	.end	isceSifDmaStat

	.globl	sceSifSetDma
	.ent	sceSifSetDma
sceSifSetDma:
	li	$3,119
	syscall
	jr	$31
	nop
	.end	sceSifSetDma

	.globl	isceSifSetDma
	.ent	isceSifSetDma
isceSifSetDma:
	li	$3,-119
	syscall
	jr	$31
	nop
	.end	isceSifSetDma

	.globl	sceSifSetDChain
	.ent	sceSifSetDChain
sceSifSetDChain:
	li	$3,120
	syscall
	jr	$31
	nop
	.end	sceSifSetDChain

	.globl	isceSifSetDChain
	.ent	isceSifSetDChain
isceSifSetDChain:
	li	$3,-120
	syscall
	jr	$31
	nop
	.end	isceSifSetDChain

	.globl	sceSifSetReg
	.ent	sceSifSetReg
sceSifSetReg:
	li	$3,121
	syscall
	jr	$31
	nop
	.end	sceSifSetReg

	.globl	sceSifGetReg
	.ent	sceSifGetReg
sceSifGetReg:
	li	$3,122
	syscall
	jr	$31
	nop
	.end	sceSifGetReg

	.globl	_ExecOSD
	.ent	_ExecOSD
_ExecOSD:
	li	$3,123
	syscall
	jr	$31
	nop
	.end	_ExecOSD

	.globl	Deci2Call
	.ent	Deci2Call
Deci2Call:
	li	$3,124
	syscall
	jr	$31
	nop
	.end	Deci2Call

	.globl	PSMode
	.ent	PSMode
PSMode:
	li	$3,125
	syscall
	jr	$31
	nop
	.end	PSMode

	.globl	MachineType
	.ent	MachineType
MachineType:
	li	$3,126
	syscall
	jr	$31
	nop
	.end	MachineType

	.globl	GetMemorySize
	.ent	GetMemorySize
GetMemorySize:
	li	$3,127
	syscall
	jr	$31
	nop
	.end	GetMemorySize

	.globl	_InitTLB
	.ent	_InitTLB
_InitTLB:
	li	$3,130
	syscall
	jr	$31
	nop
	.end	_InitTLB
