#!/usr/bin/env python3
"""Run the vendored `m2c` with the pipeline's compatibility guard applied.

`m2c.main` is normally invoked in-process (`tools/m2c_batch.run_m2c`), which imports
`tools/m2c_compat.py` and applies the shift-crash and signed-category guards.
A *subprocess* invocation (`tools/m2c_one.py`) cannot inherit those patches, so
it runs this wrapper instead, applying the guards before invoking m2c.
The optional --materialize-calls flag retains nonvoid call results as temporaries.
"""
import contextlib
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m2c_compat  # noqa: E402,F401  (patches m2c and puts it on sys.path)

from m2c.main import main  # noqa: E402

if __name__ == "__main__":
    materialize = "--materialize-calls" in sys.argv[1:]
    boundaries = "--materialize-boundaries" in sys.argv[1:]
    if materialize and boundaries:
        sys.exit("--materialize-calls and --materialize-boundaries are mutually exclusive")
    if materialize or boundaries:
        sys.argv[1:] = [arg for arg in sys.argv[1:]
                        if arg not in ("--materialize-calls", "--materialize-boundaries")]
    projection = (m2c_compat.materialize_function_calls(direct_only=boundaries,
                                                      remainders=boundaries)
                  if materialize or boundaries else contextlib.nullcontext())
    with projection:
        sys.exit(main())
