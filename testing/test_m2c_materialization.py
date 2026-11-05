"""Scoped call-result projection: ordering, void calls and subprocess parity."""
from pathlib import Path
import re
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import m2c_compat


@unittest.skipIf(m2c_compat._evaluate is None, "private m2c dependency required")
class CallMaterialization(unittest.TestCase):
    ASSEMBLY = """glabel materialize_sample
addiu $sp, $sp, -16
sd $ra, 0($sp)
jal produce
nop
move $a0, $v0
jal consume
nop
ld $ra, 0($sp)
jr $ra
addiu $sp, $sp, 16
"""
    CONTEXT = "int materialize_sample(void); int produce(void); int consume(int);"

    def run_sample(self, directory, assembly=None, context=None, name="materialize_sample"):
        import m2c_batch
        path = Path(directory)
        (path / "ctx.c").write_text(context or self.CONTEXT)
        return m2c_batch.run_m2c(assembly or self.ASSEMBLY, name,
                                 str(path / "input.s"), context=str(path / "ctx.c"))

    def test_results_are_materialized_once_and_default_is_restored(self):
        with tempfile.TemporaryDirectory() as directory:
            baseline = self.run_sample(directory)
            with m2c_compat.materialize_function_calls() as stats:
                output = self.run_sample(directory)
            restored = self.run_sample(directory)
        self.assertEqual(baseline, restored)
        self.assertIn("return consume(produce());", baseline)
        match = re.search(r"(\w+) = produce\(\);", output)
        self.assertIsNotNone(match)
        self.assertIn("consume(" + match[1] + ");", output)
        self.assertEqual(output.count("produce()"), 1)
        self.assertEqual(output.count("consume("), 1)
        self.assertLess(output.index("produce()"), output.index("consume("))
        self.assertGreater(stats["materialized"], 0)

    def test_boundary_mode_still_materializes_named_calls(self):
        with tempfile.TemporaryDirectory() as directory:
            with m2c_compat.materialize_function_calls(direct_only=True, remainders=True) as stats:
                output = self.run_sample(directory)
        match = re.search(r"(\w+) = produce\(\);", output)
        self.assertIsNotNone(match)
        self.assertIn("consume(" + match[1] + ");", output)
        self.assertEqual(output.count("produce()"), 1)
        self.assertEqual(output.count("consume("), 1)
        self.assertGreater(stats["materialized"], 0)
        self.assertEqual(stats["remainders"], 0)

    def test_void_calls_do_not_create_void_temporaries(self):
        assembly = self.ASSEMBLY.replace("materialize_sample", "materialize_void")
        assembly = assembly.replace("jal produce\nnop\nmove $a0, $v0\njal consume", "jal action")
        context = "void materialize_void(void); void action(void);"
        with tempfile.TemporaryDirectory() as directory:
            baseline = self.run_sample(directory, assembly, context, "materialize_void")
            with m2c_compat.materialize_function_calls() as stats:
                output = self.run_sample(directory, assembly, context, "materialize_void")
        self.assertEqual(output, baseline)
        self.assertIn("action();", output)
        self.assertEqual(stats["materialized"], 0)

    def test_nested_and_exceptional_scopes_restore_the_translator(self):
        from m2c import translate
        original = translate.NodeState._eval_once
        with self.assertRaisesRegex(RuntimeError, "deliberate"):
            with m2c_compat.materialize_function_calls():
                outer = translate.NodeState._eval_once
                self.assertIsNot(outer, original)
                with m2c_compat.materialize_function_calls():
                    self.assertIsNot(translate.NodeState._eval_once, outer)
                self.assertIs(translate.NodeState._eval_once, outer)
                raise RuntimeError("deliberate")
        self.assertIs(translate.NodeState._eval_once, original)

    BOUNDARY_ASSEMBLY = """glabel boundary_sample
addiu $sp, $sp, -16
sd $ra, 0($sp)
lw $t9, 0($a0)
lw $t9, 96($t9)
jalr $t9
nop
li $t0, 10000
divu $zero, $v0, $t0
mfhi $v0
ld $ra, 0($sp)
jr $ra
addiu $sp, $sp, 16
"""
    BOUNDARY_CONTEXT = """typedef struct Table {
char pad[96]; unsigned int (*roll)(void *);
} Table;
typedef struct Random { Table *table; } Random;
unsigned int boundary_sample(Random *);
"""

    def run_boundary(self, directory, assembly=None):
        return self.run_sample(directory, assembly or self.BOUNDARY_ASSEMBLY,
                               self.BOUNDARY_CONTEXT, "boundary_sample")

    def test_boundaries_keep_indirect_call_inside_its_bounded_expression(self):
        with tempfile.TemporaryDirectory() as directory:
            with m2c_compat.materialize_function_calls():
                split = self.run_boundary(directory)
            with m2c_compat.materialize_function_calls(direct_only=True, remainders=True) as stats:
                bounded = self.run_boundary(directory)
        split_call = next(line for line in split.splitlines() if "roll(" in line)
        bounded_call = next(line for line in bounded.splitlines() if "roll(" in line)
        self.assertNotIn("%", split_call)
        self.assertIn("% 10000U", bounded_call)
        self.assertEqual(bounded.count("roll("), 1)
        self.assertEqual(bounded.count("%"), 1)
        self.assertEqual(stats["materialized"], 0)
        self.assertGreater(stats["remainders"], 0)

    def test_unused_hi_is_not_materialized(self):
        assembly = self.BOUNDARY_ASSEMBLY.replace("mfhi $v0", "mflo $v0")
        with tempfile.TemporaryDirectory() as directory:
            with m2c_compat.materialize_function_calls(direct_only=True, remainders=True) as stats:
                output = self.run_boundary(directory, assembly)
        self.assertNotIn("%", output)
        self.assertIn("/ 10000U", output)
        self.assertEqual(stats["remainders"], 0)
        self.assertEqual(output.count("roll("), 1)

    def test_boundary_subprocess_parity_and_conflicting_flags(self):
        with tempfile.TemporaryDirectory() as directory:
            with m2c_compat.materialize_function_calls(direct_only=True, remainders=True):
                expected = self.run_boundary(directory)
            path = Path(directory)
            command = [sys.executable, str(ROOT / "tools/m2c_run.py"), "--materialize-boundaries",
                       "--no-cache", "-t", "mipsee-mwcc-c", "-f", "boundary_sample",
                       "--comment-style", "none", "--context", str(path / "ctx.c"),
                       str(path / "input.s")]
            actual = subprocess.run(command, capture_output=True, text=True, check=True).stdout
            self.assertEqual(actual.strip(), expected.strip())
            conflict = subprocess.run(command + ["--materialize-calls"], capture_output=True, text=True)
            self.assertNotEqual(conflict.returncode, 0)
            self.assertIn("mutually exclusive", conflict.stderr)
        conflict = subprocess.run([sys.executable, str(ROOT / "tools/m2c_one.py"), "0x3fca10",
                                   "--materialize-calls", "--materialize-boundaries"],
                                  capture_output=True, text=True)
        self.assertNotEqual(conflict.returncode, 0)
        self.assertEqual(conflict.stdout, "")

    def test_subprocess_flag_matches_scoped_inprocess_output(self):
        with tempfile.TemporaryDirectory() as directory:
            with m2c_compat.materialize_function_calls():
                expected = self.run_sample(directory)
            path = Path(directory)
            command = [sys.executable, str(ROOT / "tools/m2c_run.py"), "--materialize-calls",
                       "--no-cache", "-t", "mipsee-mwcc-c", "-f", "materialize_sample",
                       "--comment-style", "none", "--context", str(path / "ctx.c"),
                       str(path / "input.s")]
            actual = subprocess.run(command, capture_output=True, text=True, check=True).stdout
        self.assertEqual(actual.strip(), expected.strip())


if __name__ == "__main__":
    unittest.main()
