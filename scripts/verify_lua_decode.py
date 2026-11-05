#!/usr/bin/env python3
"""Check stock signed operands/branches and regenerated original Lua corpus.

Usage: python3 scripts/verify_lua_decode.py --afs ../local/extracted/NDMW.AFS
The fixtures contain only test-owned instructions, never retail bytecode.
"""
import argparse
from pathlib import Path
import struct
from lua_decompile import Decompiler, decompile_function_source, parse_chunk, JMP_ALL, OP
from lua_dump import disasm
import lua_tree


def function(code):
    return dict(code=code, kstr=[], knum=[], kproto=[], numparams=0,
                is_vararg=0, locals=[])


def fixtures():
    # Literal instruction fields independently fixed at the stock zero bias.
    fn = function([0x7fffff86, 0x7fffffc6, 0x80000006, 0x80003bc6, 0])
    d = Decompiler(fn)
    assert [d.decode(i)[2] for i in range(4)] == [-1, 0, 1, 240]
    assert 's=240' in disasm(fn, None)
    fn = function([0x8000002a, 0x7fffffaa, 0]) # JMP +1 / -1
    d = Decompiler(fn)
    assert d._jt(0) == 2 and d._jt(1) == 1
    assert '->pc 2' in disasm(fn, None)
    assert '->pc 1' in disasm(fn, None)
    assert '->pc 2' in disasm(function([43, 0, 0]), None) # PUSHNILJMP
    # Nested loops: FORPREP must pair with its own end, not the first FORLOOP.
    def signed(op, n):
        return op | ((0x1ffffff + n) << 6)
    code = [signed(6, 0), signed(6, 2), signed(6, 1), signed(44, 8),
            signed(6, 0), signed(6, 1), signed(6, 1), signed(44, 1),
            signed(45, -1), signed(6, 42), 19, signed(45, -8), 0]
    fn = function(code)
    fn['kstr'] = ['tail']
    source = decompile_function_source(fn)
    assert 'for local_0 = 0, 2 do' in source
    assert '    for local_3 = 0, 1 do' in source
    assert source.splitlines().count('end') == 1
    assert '    tail = 42' in source


def audit(afs, output):
    data = afs.read_bytes()
    chunks = entries = branches = loops = 0
    for entry in range(struct.unpack_from('<I', data, 4)[0]):
        off, size = struct.unpack_from('<II', data, 8 + entry * 8)
        blob = data[off:off + size]
        cursor = found = 0
        while (pos := blob.find(b'\x1bLua', cursor)) >= 0:
            fn, used = parse_chunk(blob, pos)
            expected = decompile_function_source(fn) + '\n'
            path = Path(lua_tree.chunk_path(entry, found, str(output)))
            assert path.read_text() == expected, path
            pending = [fn]
            while pending:
                proto = pending.pop()
                d = Decompiler(proto)
                for pc, ins in enumerate(proto['code']):
                    op = ins & 63
                    if op in JMP_ALL | {44, 45, 46, 47}:
                        target = d._jt(pc)
                        assert 0 <= target < len(proto['code']), (entry, found, pc, target)
                        branches += 1
                    if op == OP['OP_FORPREP']:
                        ends = [p for p in range(pc + 1, len(proto['code']))
                                if proto['code'][p] & 63 == OP['OP_FORLOOP'] and
                                d._jt(p) == pc + 1]
                        assert len(ends) == 1
                        assert d._jt(pc) > ends[0]
                        loops += 1
                pending.extend(proto['kproto'])
            found += 1
            cursor = pos + used
        entries += bool(found)
        chunks += found
    assert chunks == 5291 and entries == 98, (chunks, entries)
    assert len(list(output.glob('*/*_e*/*.lua'))) == chunks
    print(f'Lua recovery: {chunks} chunks / {entries} entries, {branches} stock branches, {loops} numeric loops; generated text agrees')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--afs', type=Path)
    parser.add_argument('--output', type=Path, default=Path(__file__).resolve().parents[1] / 'lua')
    args = parser.parse_args()
    fixtures()
    print('Lua signed operand, jump, PUSHNILJMP and nested-for fixtures passed')
    if args.afs:
        audit(args.afs, args.output)
