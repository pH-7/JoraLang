# JoraLang

## Overview

JoraLang is a small C++ interpreter experiment inspired by my earlier
[GoYa interpreter](https://github.com/pH-7/GoYa). It currently recognises one
instruction: `say`, which prints `Hello World!`. It is not a complete language;
variables, expressions, assignments and quoted strings are not implemented.

## Build and run

A C++11 compiler is required. There are no external library dependencies.

```sh
sh compile.sh
./JoraLang                 # Interactive input; EOF exits (Ctrl-D on Unix)
./JoraLang example.jora    # Execute a text file
./JoraLang -help           # Also -version, -license and -credits
```

The build helper works from any directory and honours `CXX` and `CXXFLAGS` (for
example, `CXX=clang++ sh compile.sh`). It stops when compilation fails.

The bundled `example.jora`:

```text
# Comments continue to the end of the line.
say
say, say
```

Whitespace and commas separate instructions. Empty input is allowed.

Exactly one argument is accepted: either an information flag or a script. A
nonzero exit status is returned for an unknown token, an unrecognised option, a
missing or unreadable file, a directory given in place of a script, more than
one argument, and any other interpreter error. An error in a script reports the
file and line it came from, and stops the run at that point.

## Validation

```sh
python3 -m unittest discover -s tests -v
```

The tests compile into a temporary directory and cover CLI termination, script
input, comments, error locations, argument validation, information flags and
parser boundaries. They honour `CXX` and `CXXFLAGS` as well, so the whole suite
can be run instrumented:

```sh
CXX=clang++ CXXFLAGS="-fsanitize=address,undefined" \
    python3 -m unittest discover -s tests
```

Every push builds and runs the suite on Linux (GCC and Clang) and macOS via
GitHub Actions, and on Codeberg via Woodpecker.


## Author

Pierre-Henry Soria

## Contact

You can contact me at pierrehenrysori {{ AT }} gmail {{ D0T }} com



## License

[BSD License](http://opensource.org/licenses/bsd-license.php)
