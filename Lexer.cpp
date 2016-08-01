//
//  JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#include "Lexer.hpp"

using namespace std;

namespace JoraLang
{
    string Lexer::LEFT_TAG = "(";
    string Lexer::RIGHT_TAG = ")";

    void Lexer::interpret( Parser& seq )
    {
        bool ok = true; // Default value

        while( ok && !seq.empty() ) {
            while ( (seq.cur() == "#" && !seq.isNext("\n")) ) seq.next(); // Ignore comments
            if(seq.cur() == "say") {
              cout << "Hello World!" << endl;
              return;
            } else if( seq.cur()== "=" && !seq.isNext( LEFT_TAG ) ) {
                // nothing now
            }

        }
    }
}
