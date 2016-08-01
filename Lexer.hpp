//
//  JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#ifndef JORA_LEXER_H_INCLUDED
#define JORA_LEXER_H_INCLUDED

#include <string>
#include <iostream>
#include "Parser.hpp"

namespace JoraLang
{
    class Lexer
    {
        public:
        static void interpret(Parser&);

        static std::string LEFT_TAG;
        static std::string RIGHT_TAG;
    };
}

#endif // JORA_LEXER_H_INCLUDED
