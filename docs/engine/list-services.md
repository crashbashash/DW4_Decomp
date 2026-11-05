# Shared list growth, mutation, search and reference bridges

The twelve-body shared primitive run at `0x2d6670..0x2d6e60` (1,956 code bytes)
and four retained-reference bridges (584 bytes) now have complete readable
[behavioral C](../../recovered/engine/list-services.c). All sixteen bodies are
compared with original instructions, including their nested calls to each other.
Three matched bodies are folded in [matching source](../../src/engine/list-services.c);
the pre-existing eight-byte -1 default remains under its generic name. Twelve
bodies retain assembly pending compiler recovery. Finding [#864](../findings/findings-0751-1000.md#f864) records this work.

## Primitive contracts

Every list exposes signed count at +8, signed capacity at +12 and a four-byte
buffer reference at +16. The [semantic name generator](../../scripts/seed_names_list_services.py)
names verified operations without asserting original method spelling or a
particular owning C++ specialization. The shared `0x2d6670` default returns -1;
its role remains unresolved and it is deliberately not given a guessed role name.

| Address | Operation |
| --- | --- |
| `0x2d6680` | Reserve capacity with descriptor-driven buffer allocation |
| `0x2d6790` | Grow/reserve and publish requested count |
| `0x2d6810` / `0x2d6900` | Insert / append a byte range with caller-supplied element stride |
| `0x2d69a0` | Remove one element with caller-supplied stride |
| `0x2d6a20` | Comparator-driven binary search with caller-supplied stride |
| `0x2d6b20` | Append one four-byte word without retaining it |
| `0x2d6b80` / `0x2d6c60` | Insert / append a four-byte word range |
| `0x2d6cf0` / `0x2d6d70` | Remove / binary-search four-byte words |
| `0x1c64e0` | Copy an indexed string token to an output and retain it |
| `0x1ca620` | Grow string list and append a retained input cell |
| `0x301e30` | Retain an object before appending its reference |
| `0x30cdf0` | Grow/zero or shrink/release string-list cells |

Reserve zero frees the old buffer, nulls its reference and publishes capacity
zero without changing count. A nonzero reserve gets metadata through the list's
virtual slot +88, looks up a signed field tag from `0x5867a0`, invokes the
descriptor's unit getter at virtual slot +100, masks that result to 16 bits and
requests `(capacity * stride) / unit` allocation units. Arithmetic wraps as EE
words. The allocation helper publishes the new data reference. Old storage is
copied for `min(old_capacity, new_capacity) * stride` bytes, including cells
beyond logical count, then freed. Count is not changed by reserve.

Resize starts at `max(current_capacity, 4)`, doubles below 1,024 and adds 1,024
at or above that threshold until capacity reaches the requested count. It calls
reserve even when capacity already suffices, then publishes count. It supplies
no negative-count guard of its own; callers establish their respective admission
rules. Overflow/nontermination behavior is not replaced with a host clamp.

Range insertion permits indices through count, requires a positive range length,
grows if needed, reloads the new buffer, moves the existing tail and copies the
input. Append range follows the same growth rule. Removal validates the index,
moves the tail if needed and decrements the re-read count. Search is retail's
comparator-driven midpoint loop plus final candidate check: it returns an actual
matched index or -1, not an insertion position or a first-duplicate guarantee.

## Reference and temporary ownership

String copy reads an indexed token without a range guard, writes it to the
output, reloads that output and increments a nonnull token's count at -4.
String append first resizes, then reads/retains the incoming cell, releases the
destination's old token and re-reads the incoming cell for publication. These
reads and the retain-before-release order preserve aliases. String resize grows
by zeroing new cells; shrink interns a null token, releases each old token using
the full header count, replaces cells and publishes the requested count. Free
calls carry both allocator and token-header address.

Object append retains at object +4 before either storing in spare capacity or
calling word append. Its retaining semantics are separate from the word append
primitive, which always calls resize. Allocation and interning failure routing
remain their owning services' contracts; the reconstruction preserves the
observed list operations rather than adding new recovery policy.

The reference adapter's allocation scratch is a dedicated four-byte guest
temporary. When composing it with messenger string append, it must not alias
the caller's live string-token temporary. The integration harness now models
those separate retail frames explicitly.

## Verification and remaining work

`python3 testing/test_list_services_retail.py` passes **1,350 whole-function
return/RAM/ordered-call cases** across every body. It covers zero/shrink/grow
reserve, 4/1,024 capacity boundaries, strides 1/4/12/64, descriptor unit masking,
range admission, relocation, tail movement, empty/missing/duplicate searches
and string/object retains/releases. Metadata getters, allocation/free, byte
copy/move/fill, comparator and string-pool operations remain controlled leaves
in this standalone test. The deeper messenger comparison now executes the
[recovered pool/table bodies](string-pool.md), retaining chunk/allocator/byte/
synchronization service boundaries.

The messenger oracle now executes original versus recovered list reserve,
resize, word append and all three retaining/string-resize bridges, alongside
real matrix copying. All **1,178 messenger cases** pass with that deeper
composition. Controlled list results have been replaced by metadata/allocator/
byte/pool boundaries. This does not establish full receiver selection, scene
publication or gameplay behavior.

String copy (52 bytes) and word append (84 bytes) now match the retail compiler,
adding **136 verified code bytes**. Their initial decompiler drafts had invalid
output typing or omitted incoming call arguments. Object append's existing
88-byte match is retained. The remaining compiler drafts stay outside `src/`.
Original Ghidra/objdump exports, candidates and logs are private under
repository-relative `../scratch/lua-engine-recovery/`.

Continue with the allocation/metadata and string-pool service dependencies,
remaining compiler bodies and actual messenger receiver/result production.
Sorted insertion and other list-library routines beyond this primitive span
also remain part of the broader dependency recovery; this page does not claim
the whole list library or Lua-dependent engine is complete.
