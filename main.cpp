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
#include "JoraLang/Core.hpp"
#include "JoraLang/Parser.hpp"
#include "JoraLang/Lexer.hpp"

using namespace std;
using namespace JoraLang;

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
                    while( !iFile.eof() )
                    {
                        getline(iFile, input);
                        Parser sequence( seq.get(input) );
                        Lexer::interpret(sequence);
                    }
                }
                else
                {
                    cerr << "Couldn't open file '" + (string)argv[1] + "'" << endl;
                }
                iFile.close();
            }
        }
        else
        {
            cout << Core::softwareInfo();
            while(1)
            {
                cout << ">>> ";
                getline(cin, input);
                Parser sequence( seq.get(input) );
                Lexer::interpret(sequence);
                cout << endl;
            }
        }
        return 0;
    }
    catch (string const& text)
    {
        cerr << text << endl;
    }
    catch (int const& digit)
    {
        cerr << "Integer Exception: " << digit << endl;
    }
    catch (double const& digit)
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
}
