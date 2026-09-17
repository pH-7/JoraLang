"""Regression checks using only Python's standard library and a C++ compiler."""
import os
from pathlib import Path
import shlex
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class InterpreterTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.directory = tempfile.TemporaryDirectory(prefix="joralang-tests-")
        cls.addClassCleanup(cls.directory.cleanup)
        cls.workspace = Path(cls.directory.name)
        cls.binary = cls.workspace / "JoraLang"
        cls.parser_check = cls.workspace / "parser-check"
        compiler = ([os.environ.get("CXX", "c++"), "-std=c++11", "-Wall", "-Wextra", "-pedantic"]
                    + shlex.split(os.environ.get("CXXFLAGS", "")))
        subprocess.run(compiler + [str(ROOT / p) for p in
                       ("Core.cpp", "Lexer.cpp", "Parser.cpp", "main.cpp")] +
                       ["-o", str(cls.binary)], check=True)
        subprocess.run(compiler + ["-I", str(ROOT), str(ROOT / "Parser.cpp"),
                       str(ROOT / "tests/parser_checks.cpp"), "-o", str(cls.parser_check)], check=True)

    def run_cli(self, *args, input=""):
        return subprocess.run([str(self.binary), *map(str, args)], input=input,
                              text=True, capture_output=True, timeout=2)

    def test_eof_exits(self):
        self.assertEqual(self.run_cli().returncode, 0)

    def test_shell_say_then_eof(self):
        result = self.run_cli(input="say\n")
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.count("Hello World!"), 1)

    def test_unknown_input_fails_without_hanging(self):
        result = self.run_cli(input="unknown\n")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("Unsupported token: unknown", result.stderr)

    def test_missing_file_fails(self):
        self.assertNotEqual(self.run_cli(self.workspace / "missing.jora").returncode, 0)

    def test_script_handles_comments_whitespace_and_no_final_newline(self):
        script = self.workspace / "sample.jora"
        script.write_text("# first line\n  say # comment\nsay,\tsay", encoding="utf-8")
        result = self.run_cli(script)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.splitlines(), ["Hello World!"] * 3)

    def test_empty_script(self):
        script = self.workspace / "empty.jora"
        script.write_text("", encoding="utf-8")
        result = self.run_cli(script)
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout, "")

    def test_information_flags(self):
        for flag in ("-V", "-version", "-H", "-help", "-license", "-credits"):
            with self.subTest(flag=flag):
                result = self.run_cli(flag)
                self.assertEqual(result.returncode, 0)
                self.assertTrue(result.stdout.strip())

    def test_information_flags_use_unix_line_endings(self):
        for flag in ("-V", "-version", "-H", "-help", "-license", "-credits"):
            with self.subTest(flag=flag):
                self.assertNotIn("\r", self.run_cli(flag).stdout)

    def test_help_documents_every_accepted_flag(self):
        help_text = self.run_cli("-help").stdout
        for flag in ("-V", "-version", "-H", "-help", "-license", "-credits"):
            with self.subTest(flag=flag):
                self.assertIn(flag, help_text)

    def test_unknown_option_is_not_treated_as_a_file(self):
        result = self.run_cli("--help")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("Unknown option '--help'", result.stderr)
        self.assertNotIn("Couldn't open file", result.stderr)

    def test_extra_arguments_are_rejected(self):
        script = self.workspace / "extra.jora"
        script.write_text("say\n", encoding="utf-8")
        result = self.run_cli(script, script)
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(result.stdout, "")
        self.assertIn("at most one argument", result.stderr)

    def test_directory_is_rejected(self):
        result = self.run_cli(ROOT / "tests")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("is a directory", result.stderr)

    def test_script_error_reports_file_and_line(self):
        script = self.workspace / "broken.jora"
        script.write_text("say\n\nbogus\nsay\n", encoding="utf-8")
        result = self.run_cli(script)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("{}:3: Unsupported token: bogus".format(script), result.stderr)
        # Execution stops at the bad line instead of running the rest.
        self.assertEqual(result.stdout.count("Hello World!"), 1)

    def test_shell_output_ends_with_a_newline(self):
        self.assertTrue(self.run_cli(input="say\n").stdout.endswith("\n"))

    def test_parser_boundaries(self):
        subprocess.run([str(self.parser_check)], check=True, timeout=2)


if __name__ == "__main__":
    unittest.main()
