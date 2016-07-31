//
//  Operator.hpp
// JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#ifndef Operator_hpp
#define Operator_hpp

#include <iostream>
#include "Parser.hpp"
#include "Function.hpp"

namespace JoraLang
{
    class Operator : public Function
    {
        public:
        bool opAssignment( Parser& );
        bool opElse( Parser& );
        bool opThen( Parser& );
    };
}


#endif /* Operator_hpp */
