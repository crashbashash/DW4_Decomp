# Alias-pool retained binding and accounting controls

The complete contiguous method block **2d0560..2d06b8** contains
nine bodies / **304 bytes**: the setter
at 2d0560 (**152 bytes**) and the eight following methods. With factory2cd170
these are ten bodies /464 bytes. They make up the binding/accounting block, not the alias allocator.

The setter, in [igAliasMemoryPool_tail.inc](../../src/engine/core/igAliasMemoryPool_tail.inc), uses a narrow ABI
view to preserve the original byte load/store and virtual slot376 dispatch. The
view must not be instantiated. C mode selected v0 for the indirect call, whereas
the original C++ virtual dispatch uses t9; explicit width and the virtual-call
view produce the exact 152 bytes. No padding instructions are inserted.

## Original factory

Factory2cd170 tests the object-system active byte. The active path calls the
class registration wrapper, then re-reads metadata5869b0 and creates through
igMetaObject_CreateInstance with the requested allocator. The bootstrap path
requests184 bytes with allocation argument0, conditionally runs constructor1540
with argument1, then invokes virtual slots44 and36 (argument0) in that order.
The constructor's returned pointer is retained. Retail does not guard the later
virtual dereference after a null allocation; the source adds no guard.

Active-byte values1 and255 both take the active path; only0 takes bootstrap.
Metadata is re-read after registration, so a registration-time change is observed.
The factory is in [igAliasMemoryPool.inc](../../src/engine/core/igAliasMemoryPool.inc).

## Binding lifetime

Alias assignment (raw vtable5313a0 slot400) retains the incoming object before
capturing/releasing the previous +180 alias. Release decrements the full reference
word and destroys when its low23 bits become zero. It then publishes the captured
incoming alias and queries that alias's slot376, passing the alias and owner.
The low byte of the result becomes owner+113. Null alias clears that byte.

Assigning the same alias is not an early return: it still retains, releases,
publishes and queries. The retain prevents a one-reference same-object assignment
from destroying the object. A destruction callback can change owner state; the
subsequent publication still writes the captured incoming alias. Query observes
the published alias and the completed reference-count changes.

## Accounting control block

| Entry | Original effect |
| --- | --- |
| 2d0600 / slot120 | Zero 64-bit +128 and +160, words +136/+140/+168, then set +112 to one |
| 2d0620 / slot124 | Same five counter clears; retain +112 |
| 2d0640 / slot128 | Call receiver slot124, then clear +112 |
| 2d0670 / slot132 | Return unsigned byte +112 |
| 2d0680, 2d06a0, 2d06b0 | Return integer zero |
| 2d0690 | Write the current word at4fb418 through the output-first argument |

The +128/+160 and +136/+140/+168 interpretation follows the existing allocation
backend trace: current bytes, byte high-water, allocation/free counts and live
allocation high-water. The original order and widths remain explicit. The reset
callback precedes disable; a callback-written +112 is still cleared afterward.
The status word is read from retail data, not assigned an invented enum value.

## Evidence and verification

```sh
python3 tools/check.py --function 0x2d0550 --cand src/engine/core/CoreLibrary.cpp
make check
make typed-check
make link
```

Ghidra output was checked against retail objdump. The allocator backend and
hardware locking are outside these ten bodies.

The [alias-pool runtime](alias-pool-runtime.md) composes init1500/constructor1540,
factory, lock/event services and backend2d1210, and classifies the vtable
targets listed in the [alias pool backend trace](allocator-builder.md#alias-pool-backend-trace).
It covers54 bodies and carries their matching status.
The [hub recovery objective](../systems/hub-recovery.md) remains open.
