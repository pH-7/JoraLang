//
//  Core.cpp
//  JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#include "Core.hpp"

using namespace std;

namespace JoraLang
{
    const char* const Core::VERSION = "1.0";
    const string Core::NAME = "JoraLang";
    
    
    string Core::softwareInfo()
    {
        string text;
        text = "Welcome to the \"" + NAME + " Language!\"\n";
        text += "Copyright (c) 2016, Pierre-Henry Soria. All Rights Reserved.\n";
        text += "Type \"-help\", \"-version\", \"-license\" or \"-credits\" to get more information.\n\n";
        
        return text;
    }
    
    string Core::softwareVersion()
    {
        return NAME + " " + VERSION + "\n";
    }
    
    string Core::showHelp()
    {
        string text;
        text = "----- " + NAME + " HELP -----\n";
        text += "Usage: " + NAME + " [<file>]\n";
        text += "Without a file, " + NAME + " reads instructions from standard input.\n";
        text += "-V, -version     : The number version\n";
        text += "-H, -help        : Help about " + NAME + "\n";
        text += "-license         : The license " + NAME + " is released under\n";
        text += "-credits         : Who wrote " + NAME + "\n";
        
        return text;
    }
    
    string Core::showLicense()
    {
        return "See here: https://github.com/pH-7/JoraLang/blob/main/LICENSE\n";
    }
    
    string Core::showCredits()
    {
        string text;
        text = "----- Credits -----\n";
        text += "Author: Pierre-Henry Soria\n";
        text += "<https://github.com/pH-7/>\n";
        
        return text;
    }
}