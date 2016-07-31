#!/bin/sh

#  compile.sh
#  JoraLang
#
#  Created by Pierre-Henry Soria on 31/07/2016.
#  Copyright © 2016 Pierre-Henry Soria. All rights reserved.

g++ -c *.cpp JoraLang/*.cpp
g++ *.o -o GoYaExe