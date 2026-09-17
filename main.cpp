//
// JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#include <cstdlib> // C library
#include <cstring> // C library
#include <sys/stat.h> // Tells a directory apart from a script

#include <fstream>
#include <iostream>
#include <string>
#include "Core.hpp"
#include "Parser.hpp"
#include "Lexer.hpp"

#ifndef S_ISDIR
#define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#endif

using namespace std;
using namespace JoraLang;

namespace
{
    // A directory opens as a stream on some platforms and then reads as empty,
    // which would otherwise pass for a successful run of an empty script.
    bool isDirectory(const char* path)
    {
        struct stat info;
        return stat(path, &info) == 0 && S_ISDIR(info.st_mode);
    }

    bool isOption(const char* arg)
    {
        return arg[0] == '-' && arg[1] != '\0';
    }

    int runFile(const char* path)
    {
        if( isDirectory(path) )
        {
            cerr << "'" << path << "' is a directory, not a " << Core::NAME << " script" << endl;
            return EXIT_FAILURE;
        }

        ifstream iFile( path );
        if( !iFile.is_open() )
        {
            cerr << "Couldn't open file '" << path << "'" << endl;
            return EXIT_FAILURE;
        }

        string input;
        unsigned long lineNumber = 0;
        while (getline(iFile, input))
        {
            ++lineNumber;
            try
            {
                Parser sequence( Parser::get(input) );
                Lexer::interpret(sequence);
            }
            catch (exception const& e)
            {
                // Report where the script went wrong, not just what went wrong.
                cerr << path << ":" << lineNumber << ": " << e.what() << endl;
                return EXIT_FAILURE;
            }
        }

        if (iFile.bad()) {
            cerr << "Failed to read input file" << endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    int runShell()
    {
        string input;
        cout << Core::softwareInfo();
        while (cout << ">>> " && getline(cin, input))
        {
            try
            {
                Parser sequence( Parser::get(input) );
                Lexer::interpret(sequence);
            }
            catch (exception const& e)
            {
                cout << endl;
                cerr << e.what() << endl;
                return EXIT_FAILURE;
            }
            cout << endl;
        }
        cout << endl; // Close off the prompt that end of input left dangling.

        if (cin.bad()) {
            cerr << "Failed to read standard input" << endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
}

// Main program entry point
int main(int argc, char *argv[]) {
    try
    {
        if( argc > 2 )
        {
            cerr << Core::NAME << " takes at most one argument. Type \"-help\" for usage." << endl;
            return EXIT_FAILURE;
        }

        if( argc > 1 )
        {

            if (!strcmp(argv[1], "-V") || !strcmp(argv[1], "-version"))
            {
                cout << Core::softwareVersion();
                return EXIT_SUCCESS;
            }
            else if (!strcmp(argv[1], "-H") || !strcmp(argv[1], "-help"))
            {
                cout << Core::showHelp();
                return EXIT_SUCCESS;
            }
            else if (!strcmp(argv[1], "-license"))
            {
                cout << Core::showLicense();
                return EXIT_SUCCESS;
            }
            else if (!strcmp(argv[1], "-credits"))
            {
                cout << Core::showCredits();
                return EXIT_SUCCESS;
            }
            else if (isOption(argv[1]))
            {
                // Without this an unknown flag is mistaken for a file name.
                cerr << "Unknown option '" << argv[1] << "'. Type \"-help\" for usage." << endl;
                return EXIT_FAILURE;
            }
            else
            {
                return runFile(argv[1]);
            }
        }

        return runShell();
    }
    catch (exception const& e)
    {
        cerr << e.what() << endl;
    }
    return EXIT_FAILURE;
}
