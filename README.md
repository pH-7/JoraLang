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
./JoraLang -help
```

The build helper works from any directory and honours `CXX` (for example,
`CXX=clang++ sh compile.sh`). It stops when compilation fails.

Example `example.jora`:

```text
# Comments continue to the end of the line.
say
say, say
```

Whitespace and commas separate instructions. Unknown tokens, unreadable files
and interpreter errors return a nonzero exit status; empty input is allowed.

## Validation

```sh
python3 -m unittest discover -s tests -v
```

The tests compile into a temporary directory and cover CLI termination,
script input, comments, missing files, information flags and parser boundaries.


## Author

Pierre-Henry Soria

## Contact

You can contact me at pierrehenrysori {{ AT }} gmail {{ D0T }} com



## License

[BSD License](http://opensource.org/licenses/bsd-license.php)
