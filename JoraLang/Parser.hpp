//
//  JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#ifndef JORA_PARSER_H_INCLUDED
#define JORA_PARSER_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <list>
#include "Lexer.hpp"
#include "Operator.hpp"


namespace JoraLang
{
    typedef std::list<std::string> tokenList;
    
    class Parser {
        public:
        Parser();
        Parser( const tokenList& );
        void parse();
        tokenList get(std::string);
        void append( const tokenList& );
        void append( std::string tok );
        void clear();
        bool empty() const;
        std::string cur() const;
        bool next();
        bool find(const std::string&);
        bool isFront( std::string ) const;
        bool isNext( std::string ) const;
        
        protected:
        bool checkSize() const;
        static std::set<char> m_specialTokens;
        
        private:
        tokenList m_tokens;
    };
}

#endif // JORA_PARSER_H_INCLUDED