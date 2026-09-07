//
//  JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#include "Lexer.hpp"
#include <stdexcept>

using namespace std;

namespace JoraLang
{
    string Lexer::LEFT_TAG = "(";
    string Lexer::RIGHT_TAG = ")";

    void Lexer::interpret( Parser& seq )
    {
        while (!seq.empty()) {
            const string token = seq.cur();
            seq.next();
            if (token == "say") {
                cout << "Hello World!" << endl;
            } else {
                throw runtime_error("Unsupported token: " + token);
            }
        }
    }
}
