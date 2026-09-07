//
// JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#include <cstdlib> // C library
#include <cstring> // C library

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Core.hpp"
#include "Parser.hpp"
#include "Lexer.hpp"

using namespace std;
using namespace JoraLang;

// Main program entry point
int main(int argc, char *argv[]) {
    try
    {
        Parser seq;
        string input;

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
            else
            {
                ifstream iFile( argv[1] );
                if( iFile.is_open() )
                {
                    while (getline(iFile, input))
                    {
                        Parser sequence( seq.get(input) );
                        Lexer::interpret(sequence);
                    }
                    if (iFile.bad()) {
                        cerr << "Failed to read input file" << endl;
                        return EXIT_FAILURE;
                    }
                }
                else
                {
                    cerr << "Couldn't open file '" + (string)argv[1] + "'" << endl;
                    return EXIT_FAILURE;
                }
                iFile.close();
            }
        }
        else
        {
            cout << Core::softwareInfo();
            while (cout << ">>> " && getline(cin, input))
            {
                Parser sequence( seq.get(input) );
                Lexer::interpret(sequence);
                cout << endl;
            }
            if (cin.bad()) {
                cerr << "Failed to read standard input" << endl;
                return EXIT_FAILURE;
            }
        }
        return EXIT_SUCCESS;
    }
    catch (string const& text)
    {
        cerr << text << endl;
    }
    catch (int digit)
    {
        cerr << "Integer Exception: " << digit << endl;
    }
    catch (double digit)
    {
        cerr << "Double Exception: " << digit << endl;
    }
    catch (runtime_error const& e)
    {
        cerr << "Exception during runtime: " << e.what() << endl;
    }
    catch (exception const& e)
    {
        cerr << e.what() << endl;
    }
    return EXIT_FAILURE;
}
