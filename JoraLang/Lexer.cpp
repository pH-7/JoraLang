//
//  Lexer.cpp
//  JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#include "Parser.hpp"

using namespace std;

namespace JoraLang
{
    string Lexer::LEFT_TAG = "(";
    string Lexer::RIGHT_TAG = ")";
    
    void Lexer::interpret( Parser& seq )
    {
        Operator *operatorCore;
        operatorCore = new Operator;
        
        Function *func;
        func = new Function;
        
        bool ok = true; // Default value
        
        while( ok && !seq.empty() ) {
            while ( (seq.cur() == "#" && !seq.isNext("\n")) ) seq.next(); // Ignore the comments
            if( seq.cur()== "=" && !seq.isNext( Lex::LEFT_TAG ) )
                ok = operatorCore->opAssignment(seq);
            else if( seq.cur() == "then" )
                ok = operatorCore->opThen(seq);
            else if( seq.cur() == "else" )
                ok = operatorCore->opElse(seq);
            else if( seq.cur() == "?" )   // "?" is ignored since it is a placeholder
                seq.next();
            else
                ok = func->interpStatement(seq);
        }
        
        delete operatorCore;
        delete func;
    }
}