"""Decode the observed MW PS2 destroy-only exception-table subset.

Bounds and unsupported records fail closed. Compact widths 1..3, header save
counts/base, range triples and action tags 02/82 were checked against controlled
compiler objects. Four-byte integers, catch actions and other header flags are
intentionally unsupported. No input files are modified.
"""
from pathlib import Path
import argparse
import json
import struct

class DecodeError(ValueError):
    pass

def number(data, pos):
    if not 0 <= pos < len(data):
        raise DecodeError('truncated compact number')
    first = data[pos]
    if first & 1 == 0:
        width, high = 1, first >> 1
    elif first & 3 == 1:
        width, high = 2, first >> 2
    elif first & 7 == 3:
        width, high = 3, first >> 3
    else:
        raise DecodeError('unsupported compact-number prefix: '+hex(first))
    if pos + width > len(data):
        raise DecodeError('truncated compact number')
    return (high << (8*(width-1))) | int.from_bytes(data[pos+1:pos+width], 'big'), pos+width

def decode(data, func, size, table=0):
    if not data or size <= 0 or size % 4 or func < 0 or func % 4 or func+size > 0x100000000:
        raise DecodeError('empty table/function')
    header = data[0]
    # Observed header: six-bit GPR count, 0x40 marks additional FPR count.
    if header & 0x80 or (header & 0x3f) > 9:
        raise DecodeError('unsupported header')
    gprs = header & 0x3f
    frame, pos = number(data, 1)
    save_base, pos = number(data, pos)
    fprs = 0
    if header & 0x40:
        fprs, pos = number(data, pos)
        if not 1 <= fprs <= 12:
            raise DecodeError('unsupported FPR count')
    if not frame or frame % 16 or save_base % 16 or save_base >= frame:
        raise DecodeError('invalid frame/save area')
    return_save = save_base + ((4*fprs + 15) // 16)*16 + 16*gprs
    if return_save + 8 > frame:
        raise DecodeError('register save area exceeds frame')
    rows, last_end = [], 0
    while True:
        if pos >= len(data):
            raise DecodeError('missing range terminator')
        if data[pos] == 0:
            pos += 1
            break
        at = pos
        delta, pos = number(data, pos)
        length, pos = number(data, pos)
        action, pos = number(data, pos)
        start = last_end + delta
        end = start + length
        if not delta or end >= size or start % 4 or end % 4:
            raise DecodeError('invalid/out-of-function PC range')
        rows.append(dict(record_offset=at, delta=delta, length=length,
                         action_offset=action, start=func+start, end_inclusive=func+end))
        last_end = end
    range_end = pos
    actions = {}
    for row in rows:
        pos = row['action_offset']
        if not range_end <= pos < len(data):
            raise DecodeError('action outside action area')
        chain = []
        while True:
            if pos >= len(data):
                raise DecodeError('missing final cleanup')
            at = pos
            tag = data[pos]
            pos += 1
            if tag not in (2, 0x82):
                raise DecodeError('unsupported action '+hex(tag))
            offset, pos = number(data, pos)
            if pos+4 > len(data):
                raise DecodeError('truncated destructor pointer')
            destructor = int.from_bytes(data[pos:pos+4], 'little')
            pos += 4
            if offset >= frame or offset % 4:
                raise DecodeError('invalid cleanup stack offset')
            item = dict(offset=at, tag=tag, stack_offset=offset, destructor=destructor,
                        final=bool(tag & 0x80), end_offset=pos)
            if at in actions and actions[at] != item:
                raise DecodeError('inconsistent shared action')
            actions[at] = item
            chain.append(item)
            if tag & 0x80:
                break
        row['cleanup_chain'] = chain
    if not actions:
        raise DecodeError('no cleanup actions')
    ordered = sorted(actions.values(), key=lambda item:item['offset'])
    cursor = range_end
    for item in ordered:
        if item['offset'] != cursor:
            raise DecodeError('unreferenced/overlapping action bytes')
        cursor = item['end_offset']
    if len(data)-cursor > 3 or any(data[cursor:]):
        raise DecodeError('unowned trailing bytes (only alignment padding supported)')
    return dict(function=func, size=size, table=table, header=header, frame=frame,
                save_area_base=save_base, saved_gprs=gprs, saved_fprs=fprs,
                return_save_offset=return_save, range_end=range_end, ranges=rows, actions=ordered,
                referenced_end=cursor, padding=len(data)-cursor)



class Image:
    """Read file-backed virtual addresses from an ELF32 little-endian MIPS image."""
    def __init__(self, data):
        self.data = data
        if (len(data) < 52 or data[:6] != b'\x7fELF\x01\x01'
                or struct.unpack_from('<H', data, 18)[0] != 8):
            raise DecodeError('expected ELF32 little-endian MIPS input')
        phoff = struct.unpack_from('<I', data, 28)[0]
        stride, count = struct.unpack_from('<HH', data, 42)
        if not count or stride < 32 or phoff + count*stride > len(data):
            raise DecodeError('invalid ELF program headers')
        self.segments = []
        for i in range(count):
            kind, off, va, _pa, filesz, memsz, flags, _align = struct.unpack_from(
                '<8I', data, phoff+i*stride)
            if kind != 1 or not filesz:
                continue
            if off+filesz > len(data) or filesz > memsz or va+filesz > 0x100000000:
                raise DecodeError('invalid file-backed ELF segment')
            self.segments.append((va, va+filesz, off, flags))
        if not self.segments:
            raise DecodeError('no file-backed LOAD segment')

    def read(self, va, size):
        spans = [(off+va-lo, flags) for lo, hi, off, flags in self.segments
                 if 0 <= va and 0 <= size and lo <= va and va+size <= hi]
        if len(spans) != 1:
            raise DecodeError('virtual address is outside one unambiguous file-backed segment')
        off, _flags = spans[0]
        return self.data[off:off+size]

    def executable(self, va, size=4):
        self.read(va, size)
        return any(lo <= va and va+size <= hi and flags & 1
                   for lo, hi, _off, flags in self.segments)


def inventory(image):
    """Decode only the two independently verified retail GAMERAM index anchors."""
    for va, expected in [(0x553b80, (0x3fca10, 0xa388, 0x544fd4)),
                         (0x553bd4, (0x407120, 0x938, 0x545174))]:
        if struct.unpack('<3I', image.read(va, 12)) != expected:
            raise DecodeError('retail combat exception-index anchor differs')
    if not image.executable(0x3fca10, 0xa388):
        raise DecodeError('callback is not in executable file-backed memory')
    result = decode(image.read(0x544fd4, 0x1a0), 0x3fca10, 0xa388, 0x544fd4)
    for action in result['actions']:
        ptr = action['destructor']
        if not ptr or ptr % 4 or not image.executable(ptr):
            raise DecodeError('cleanup target is not aligned executable memory')
    for row in result['ranges']:
        for pc in (row['start'], row['end_inclusive']):
            instruction = int.from_bytes(image.read(pc-8, 4), 'little')
            if not (instruction >> 26 == 3 or instruction >> 26 == 0 and instruction & 63 == 9):
                raise DecodeError('range endpoint is not a call return PC')
    return result


def main():
    root = Path(__file__).resolve().parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--elf', type=Path, default=root/'orig/SLUS-20836/SLUS_208.36')
    parser.add_argument('--out', type=Path, help='write JSON instead of stdout')
    args = parser.parse_args()
    try:
        result = inventory(Image(args.elf.read_bytes()))
    except (DecodeError, OSError) as error:
        parser.exit(1, str(error)+'\n')
    text = json.dumps(result, indent=2)+'\n'
    if args.out:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(text)
    else:
        print(text, end='')


if __name__ == '__main__':
    main()
