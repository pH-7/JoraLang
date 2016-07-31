//
//  Lexer.hpp
//  JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include "Parser.hpp"
#include "Function.hpp"

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

#endif /* Lexer_hpp */
