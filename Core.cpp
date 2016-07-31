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
    const char* Core::VERSION = "1.0";
    const string Core::NAME = "JoraLang";
    
    
    string Core::softwareInfo()
    {
        string text;
        text = "Welcome to the \"" + NAME + " Language!\"\r\n";
        text += "Copyright (c) 2016, Pierre-Henry Soria. All Rights Reserved.\r\n";
        text += "Type \"-help\", \"-version\", \"-license\" or \"-credits\" to get more information.\r\n\r\n";
        
        return text;
    }
    
    string Core::softwareVersion()
    {
        return NAME + " " + VERSION + "\r\n";
    }
    
    string Core::showHelp()
    {
        string text;
        text = "----- " + NAME + " HELP -----\r\n";
        text += "Usage: <PROGRAMM EXE> <file>\r\n";
        text += "-V, -version     : The number version\r\n";
        text += "-H, -help        : Help about " + NAME + "\r\n";
        
        return text;
    }
    
    string Core::showLicense()
    {
        return "See here: https://github.com/pH-7/JoraLang/blob/master/LICENSE\r\n";
    }
    
    string Core::showCredits()
    {
        string text;
        text = "----- Credits -----\r\n";
        text += "Author: Pierre-Henry Soria\r\n";
        text += "<https://github.com/pH-7/>\r\n";
        
        return text;
    }
}