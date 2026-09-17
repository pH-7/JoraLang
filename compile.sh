#!/bin/sh

#  compile.sh
#  JoraLang
#
#  Created by Pierre-Henry Soria on 01/08/2016.
#  Copyright © 2016 Pierre-Henry Soria. All rights reserved.

set -eu
cd "$(dirname "$0")"
# CXXFLAGS is intentionally unquoted so callers can pass several flags.
"${CXX:-c++}" -std=c++11 -Wall -Wextra -pedantic ${CXXFLAGS:-} \
    Core.cpp Lexer.cpp Parser.cpp main.cpp -o JoraLang
