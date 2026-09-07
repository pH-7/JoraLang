#!/bin/sh

#  compile.sh
#  JoraLang
#
#  Created by Pierre-Henry Soria on 01/08/2016.
#  Copyright © 2016 Pierre-Henry Soria. All rights reserved.

set -eu
cd "$(dirname "$0")"
"${CXX:-c++}" -std=c++11 -Wall -Wextra -pedantic \
    Core.cpp Lexer.cpp Parser.cpp main.cpp -o JoraLang
