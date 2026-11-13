	.set	noreorder

	.text
	.align	2

	.globl	SetGsCrt
	.ent	SetGsCrt
SetGsCrt:
	li	$3,2
	syscall
	jr	$31
	nop
	.end	SetGsCrt

	.globl	_Exit
	.ent	_Exit
_Exit:
	li	$3,4
	syscall
	jr	$31
	nop
	.end	_Exit

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

	.globl	SetVTLBRefillHandler
	.ent	SetVTLBRefillHandler
SetVTLBRefillHandler:
	li	$3,13
	syscall
	jr	$31
	nop
	.end	SetVTLBRefillHandler

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

	.globl	AddDmacHandler__0010ac00
	.ent	AddDmacHandler__0010ac00
AddDmacHandler__0010ac00:
	li	$3,18
	syscall
	jr	$31
	nop
	.end	AddDmacHandler__0010ac00

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

	.globl	EndOfHeap
	.ent	EndOfHeap
EndOfHeap:
	li	$3,62
	syscall
	jr	$31
	nop
	.end	EndOfHeap

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

	.globl	EnableCache
	.ent	EnableCache
EnableCache:
	li	$3,97
	syscall
	jr	$31
	nop
	.end	EnableCache

	.globl	FlushCache
	.ent	FlushCache
FlushCache:
	li	$3,100
	syscall
	jr	$31
	nop
	.end	FlushCache

	.globl	iFlushCache
	.ent	iFlushCache
iFlushCache:
	li	$3,-104
	syscall
	jr	$31
	nop
	.end	iFlushCache

	.globl	sceSifStopDma
	.ent	sceSifStopDma
sceSifStopDma:
	li	$3,107
	syscall
	jr	$31
	nop
	.end	sceSifStopDma

	.globl	GsPutIMR
	.ent	GsPutIMR
GsPutIMR:
	li	$3,113
	syscall
	jr	$31
	nop
	.end	GsPutIMR

	.globl	SetVSyncFlag
	.ent	SetVSyncFlag
SetVSyncFlag:
	li	$3,115
	syscall
	jr	$31
	nop
	.end	SetVSyncFlag

	.globl	sceSifDmaStat
	.ent	sceSifDmaStat
sceSifDmaStat:
	li	$3,118
	syscall
	jr	$31
	nop
	.end	sceSifDmaStat

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
