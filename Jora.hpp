//
//  Jora.hpp
//  Simple Project C++
//
//  Created by PH Soria on 31/07/2016.
//  Copyright © 2016 PH Soria. All rights reserved.
//

#ifndef Jora_hpp
#define Jora_hpp

#include <stdio.h>

#pragma once

class line_editor {
private:
    vector<string> line_table;
    vector<string>::iterator iterator;
    long current_line;
public:
    line_editor() : current_line(-1) { };
    void command(string command);
};

#endif

