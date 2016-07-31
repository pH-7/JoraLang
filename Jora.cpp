#ifndef __LINE_EDITOR_INCLUDED__
#define __LINE_EDITOR_INCLUDED__

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
