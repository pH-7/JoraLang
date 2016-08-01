//
//  Parser.cpp
// JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#include "Parser.hpp"

using namespace std;

namespace JoraLang
{
    // Initialize static member
    set<char> Parser::m_specialTokens;

    Parser::Parser() {}

    Parser::Parser( const tokenList& l )
    {
        append(l);
    }

    void Parser::parse()
    {

    }

    tokenList Parser::get(string src)
    {
        tokenList toks;
        string work;

        for( unsigned int i=0; i<src.length(); i++ )
        {
            if( src[i] == ',' ) {
                if( !work.empty() ) {
                    toks.push_back(work);
                    work = "";
                }
            } else if( m_specialTokens.count(src[i]) ) {
                if( !work.empty() ) {
                    toks.push_back(work);
                    work = "";
                }
                work.append(1, src[i]);
                toks.push_back(work);
                work = "";
            } else {
                work.append(1, src[i]);
            }
        }

        if( !work.empty() )
            toks.push_back(work);

        return toks;
    }

    void Parser::append(const tokenList& l)
    {
        m_tokens.insert(m_tokens.end(), l.begin(), l.end());
    }

    void Parser::append(string tok)
    {
        m_tokens.push_back(tok);
    }

    void Parser::clear()
    {
        m_tokens.clear();
    }

    bool Parser::empty() const
    {
        return m_tokens.empty();
    }

    string Parser::cur() const
    {
        return m_tokens.front();
    }

    bool Parser::next()
    {
        if (!empty()) m_tokens.pop_front();
        return !empty();
    }

    bool Parser::find(const string& str)
    {
        list<string>::iterator findIter = ::find(m_tokens.begin(), m_tokens.end(), str);
        return (*findIter == str);
    }

    bool Parser::isFront(string t) const
    {
        return (!checkSize()) ? false : t == *(--m_tokens.end());
    }

    bool Parser::isNext(string t) const
    {
        return (!checkSize()) ? false : t == *(++m_tokens.begin());
    }

    bool Parser::checkSize() const
    {
        return (m_tokens.size() > 1);
    }

}
