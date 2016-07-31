//
//  Function.hpp
//  Simple Project C++
//
//  Created by PH Soria on 31/07/2016.
//  Copyright © 2016 PH Soria. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp

#include <cstdio> // C library
#include <cstdlib> // C library

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include "Parser.hpp"
#include "Stack.hpp"

namespace JoraLang
{
    class Function : public Parser
    {
        public:
        Function();
        Function(std::string, unsigned int, const Parser&);
        Function(const Function&);
        
        Function& operator=(const Function&);
        bool operator<(const Function&) const;
        
        static void system();
        std::string allBufferToStr();
        bool interpStatement( Parser&);
        bool callFunction( std::string, std::vector<double> );
        bool defineFunction( Parser& );
        bool isWhiteSpace( std::string );
        bool isChar( std::string );
        bool isString( std::string );
        int isAlpha( std::string );
        bool isVariable( std::string );
        double variableValue( std::string );
        void setVariable( std::string, double );
        bool isNumber( std::string );
        std::string print();
        int systemCode();
        void cleanVars();
        
        typedef std::set<Function> funcSet;
        
        protected:
        static double m_numBuffer;
        static char m_charBuffer;
        static std::string m_strBuffer;
        
        private:
        static std::vector<Stack> m_scope;
        static funcSet m_definedFunctions;
        unsigned int m_args;
        std::string m_name;
        Parser m_body;
    };
    
}


#endif /* Function_hpp */
