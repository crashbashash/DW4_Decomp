"""Export architecture-independent Ghidra function bodies with exact ranges.

Run as a PyGhidra post-script with --out PATH. ``size`` counts occupied body
addresses; ``span_size`` includes any gaps between ranges. Range ends are
exclusive. These are analyzed function bodies, not decompiler-derived extents.

@category Recovery
@runtime PyGhidra
"""
import json
import re
import typing

if typing.TYPE_CHECKING:
    from typing import Any
    currentProgram: Any = None
    getScriptArgs: Any = None


def hex_address(value):
    return '0x%08x' % value


def function_record(function):
    body = function.getBody()
    ranges = []
    occupied = 0
    iterator = body.getAddressRanges(True)
    previous_end = None
    space = str(function.getEntryPoint().getAddressSpace().getName())
    while iterator.hasNext():
        interval = iterator.next()
        first, last = interval.getMinAddress(), interval.getMaxAddress()
        if str(first.getAddressSpace().getName()) != space:
            raise ValueError('function body crosses address spaces: '+function.getName())
        start, end = int(first.getOffset()), int(last.getOffset())+1
        if end <= start or previous_end is not None and start < previous_end:
            raise ValueError('unordered or overlapping function body: '+function.getName())
        ranges.append({'start': hex_address(start), 'end': hex_address(end)})
        occupied += end-start
        previous_end = end
    if occupied != int(body.getNumAddresses()):
        raise ValueError('function range sizes disagree with its body: '+function.getName())
    span = int(ranges[-1]['end'], 16)-int(ranges[0]['start'], 16) if ranges else 0
    return {'address': hex_address(int(function.getEntryPoint().getOffset())),
            'address_space': space, 'name': str(function.getName()),
            'signature': str(function.getPrototypeString(False, False)),
            'size': occupied, 'span_size': span, 'ranges': ranges,
            'thunk': bool(function.isThunk()), 'external': bool(function.isExternal())}


def main():
    arguments = list(getScriptArgs())
    if len(arguments) not in (2, 4) or arguments[0] != '--out' or len(arguments) == 4 and arguments[2] != '--symbols-out':
        raise SystemExit('dump_target_inventory: expected --out PATH [--symbols-out PATH]')
    executable_hash = str(currentProgram.getExecutableSHA256() or '').lower()
    if not re.fullmatch('[0-9a-f]{64}', executable_hash):
        raise ValueError('program has no recorded executable SHA-256; inventory is not input-bound')
    functions = [function_record(function)
                 for function in currentProgram.getFunctionManager().getFunctions(True)]
    functions.sort(key=lambda row: (row['address_space'], int(row['address'], 16)))
    output = {'program': str(currentProgram.getName()),
              'language': str(currentProgram.getLanguageID()), 'count': len(functions),
              'executable_sha256': executable_hash,
              'range_end_convention': 'exclusive', 'functions': functions}
    with open(arguments[1], 'w', encoding='utf-8') as stream:
        json.dump(output, stream, indent=2)
        stream.write('\n')
    fragmented = sum(len(function['ranges']) > 1 for function in functions)
    print('dump_target_inventory: %d functions, %d fragmented bodies' % (len(functions), fragmented))
    if len(arguments) == 4:
        symbols = []
        listing = currentProgram.getListing()
        manager = currentProgram.getFunctionManager()
        for symbol in currentProgram.getSymbolTable().getAllSymbols(True):
            address = symbol.getAddress()
            if address is None or address.getAddressSpace().isOverlaySpace():
                continue
            symbol_type = str(symbol.getSymbolType())
            function = manager.getFunctionAt(address) if symbol_type == 'Function' else None
            data = listing.getDefinedDataAt(address)
            kind = ('func' if symbol_type == 'Function' else 'label' if symbol_type == 'Label'
                    else 'data' if data is not None else symbol_type.lower())
            size = int(function.getBody().getNumAddresses()) if function is not None else int(data.getLength()) if data is not None else 0
            symbols.append({'address': hex_address(int(address.getOffset())),
                            'address_space': str(address.getAddressSpace().getName()),
                            'size': size, 'name': str(symbol.getName(True)), 'kind': kind})
        symbols.sort(key=lambda row: (row['address_space'], int(row['address'], 16), row['name']))
        counts = {}
        for symbol in symbols:
            counts[symbol['kind']] = counts.get(symbol['kind'], 0)+1
        with open(arguments[3], 'w', encoding='utf-8') as stream:
            json.dump({'program': str(currentProgram.getName()),
                       'language': str(currentProgram.getLanguageID()),
                       'executable_sha256': executable_hash,
                       'count': len(symbols), 'counts': counts, 'symbols': symbols}, stream, indent=2)
            stream.write('\n')
        print('dump_target_inventory: %d symbols from the same input-bound program' % len(symbols))


if __name__ == '__main__':
    main()
