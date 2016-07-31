//
//  Operator.cpp
// JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#include <iostream>
#include "Operator.hpp"
#include "Parser.hpp"

using namespace std;

namespace JoraLang
{

/**
 * Variable assignment.
 */
bool Operator::opAssignment( Parser& seq )
{
    if( !seq.next() ) {
        cout << "ERROR: Assignment incomplete." << endl;
        return false;
    }
    if( !isVariable(seq.cur()) ) {
        cout << "ERROR: Assignment to non-variable." << endl;
        return false;
    }
    setVariable(seq.cur(), m_numBuffer);
    seq.next();
    return true;
}

/**
 * Ternary operator.
 */
bool Operator::opElse( Parser& seq )
{
    bool found = false;
    while( seq.next() && !found )
        found = (seq.cur() == "?");
    return found;
}

bool Operator::opThen( Parser& seq )
{
    if( m_numBuffer == 0 )
    {
        bool done=false;
        while( !done && seq.next() )
            done = (seq.cur() == "?") || (seq.cur() == "else");
        
        if( !done )
        {
            cout << "ERROR: Conditional incomplete." << endl;
            return false;
        }
    }
    
    seq.next(); // Go to next if "then" condition is true, "else" or "?" otherwise
    return true;
}