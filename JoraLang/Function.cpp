//
//  Function.cpp
//  Simple Project C++
//
//  Created by PH Soria on 31/07/2016.
//  Copyright © 2016 PH Soria. All rights reserved.
//

#include "Function.hpp"

using namespace std;

namespace JoraLang
{
    // Initialize static members
    vector<Stack> Function::m_scope;
    set<Function> Function::m_definedFunctions;
    //double Function::m_currentValue(0.0);
    double Function::m_numBuffer = NULL;
    char Function::m_charBuffer = NULL;
    std::strin Function::m_strBuffer = "";
    
    Function::Function() : m_args(0) {}
    Function::Function(string n, unsigned int a, const Parser& b=Parser()) : m_args(a), m_name(n), m_body(b) {}
    Function::Function(const Function& f) { *this = f; }
    
    Function::Function& Function::Function::operator=(const Function& f)
    {
        m_args = f.m_args;
        m_name = f.m_name;
        m_body = f.m_body;
        return *this;
    }
    
    bool Function::Function::operator<(const Function& f) const
    {
        if( m_name < f.m_name ) return true;
        return (m_name == f.m_name) && (m_args<f.m_args);
    }
    
    template <typename T, typename S>
    T static stream_cast( S const& val )
    {
        stringstream stream(val);
        T rc;
        stream >> rc;
        return rc;
    }
    
    template <typename T>
    string convertToStr( T const& val )
    {
        ostringstream convert;
        convert << val;
        return convert.str();
    }
    
    string Function::allBufferToStr()
    {
        string str;
        
        if( !m_strBuffer.empty() )
            str = m_strBuffer;
        else if( m_charBuffer != NULL )
            str = convertToStr<char>(m_charBuffer);
        else if( m_numBuffer != NULL )
            str = convertToStr<double>(m_numBuffer);
        else
            throw string("ERROR: Empty Output Stream.");
        
        return str;
    }
    
    bool Function::isWhiteSpace( string str )
    {
        return (str  == " ") || (str  == "\t") || (str  == "\r")
        || (str  == "\n") || (str  == "\v");
    }
    
    bool Function::isString( string str )
    {
        return (str.empty() == (str == std::string()));
    }
    
    bool Function::isChar( string str )
    {
        return (isString(str) && str.size() == 1);
    }
    
    /*
     * Returns the number of alphabet letter found. Returns 0 if no letter of the alphabet is found.
     */
    int Function::isAlpha( string str )
    {
        string letters = "qwertyuiopasdfghjklzxcvbnm";
        int static foundCount = 0;
        
        for (string::iterator it = str.begin(); it != str.end(); ++it)
        if(letters.find(*it)) foundCount++;
        
        return foundCount;
    }
    
    bool Function::isNumber( string str )
    {
        unsigned int i = 0;
        if( !str.empty() && (str[i] == '-' || str[i] == '+') ) i++;
        return string::npos == str.find_first_not_of( ".eE0123456789", i );
    }
    
    bool Function::isVariable( string tag )
    {
        return (tag == "x") || (tag == "y") || (tag == "z")
        || (tag == "i") || (tag == "j") || (tag == "k");
    }
    
    string Function::print()
    {
        string output = allBufferToStr();
        cleanVars();
        return output;
    }
    
    int Function::systemCode()
    {
        int ret = ::system(m_strBuffer.c_str());
        cleanVars();
        return ret;
    }
    
    double Function::variableValue( string tag )
    {
        if( tag == "x" ) return m_scope.front().v1;
        if( tag == "y" ) return m_scope.front().v2;
        if( tag == "y" ) return m_scope.front().v3;
        
        if( tag == "i" ) return m_scope.back().v1;
        if( tag == "j" ) return m_scope.back().v2;
        if( tag == "k" ) return m_scope.back().v3;
        
        throw string("WARNING: Invalid variable reference.");
        return 0;
    }
    
    void Function::setVariable( string tag, double val )
    {
        if( tag == "x" ) { m_scope.front().v1 = val; return; }
        if( tag == "y" ) { m_scope.front().v2 = val; return; }
        if( tag == "z" ) { m_scope.front().v3 = val; return; }
        
        if( tag == "i" ) { m_scope.back().v1 = val; return; }
        if( tag == "j" ) { m_scope.back().v2 = val; return; }
        if( tag == "k" ) { m_scope.back().v3 = val; return; }
        
        throw string("WARNING: Invalid variable assignment.");
    }
    
    bool Function::callFunction( string func, vector<double> args )
    {
        string bf;
        
        funcSet::iterator f = m_definedFunctions.find(Function(func,args.size()));
        if( f == m_definedFunctions.end() ) {
            throw string("ERROR: No function '" + func + "' with support for " + convertToStr<double>(args.size()) + " argument(s).");
            return false;
        }
        
        // If nobody code, then let's assume it is a system function
        if( f->m_body.empty() )
        {
            if( f->m_name == "+" )                 m_numBuffer = args[0] + args[1];
            else if( f->m_name == "-" )            m_numBuffer = args[0] - args[1];
            else if( f->m_name == "*" )            m_numBuffer = args[0] * args[1];
            else if( f->m_name == "/" )            m_numBuffer = args[0] / args[1];
            else if( f->m_name == "<" )            m_numBuffer = args[0] < args[1];
            else if( f->m_name == ">" )            m_numBuffer = args[0] > args[1];
            else if( f->m_name == "=" )            m_numBuffer = args[0] == args[1];
            else if( f->m_name == "<=" )           m_numBuffer = args[0] <= args[1];
            else if( f->m_name == ">=" )           m_numBuffer = args[0] >= args[1];
            else if( f->m_name == "nl")            cout << endl; // Nerw Line
            else if( f->m_name == "ends")          cout << ends; // Insert null character (end space \0)
            else if( f->m_name == "ws")            cout << " "; // White Space
            else if( f->m_name == "print")         cout << print();
            else if( f->m_name == "println")       cout << print() << endl;
            else if( f->m_name == "length")        m_numBuffer = print().length();
            else if( f->m_name == "input") {       getline(cin, bf); m_strBuffer = bf; }
            else if( f->m_name == "system")        systemCode();
            else if( f->m_name == "import::module")
        }
        else
        {
            // Setup scopes
            m_scope.push_back( Stack() );
            switch(args.size())
            {
                default:
                    case 3:     m_scope.back().v3 = args[2];
                    case 2:     m_scope.back().v2 = args[1];
                    case 1:     m_scope.back().v1 = args[0];
                    case 0:     break;  // nothing
            }
            
            // Run body function, first make a copy because tokens are consumed
            Parser run = f->m_body;
            Interpreter::Base::interpret(run);
            
            // Trash m_scope
            m_scope.pop_back();
        }
        
        return true;
    }
    
    bool Function::interpStatement( Parser& seq )
    {
        bool ok = true;
        
        if( isVariable(seq.cur()) )
        m_numBuffer = variableValue(seq.cur());
        else if( seq.isNext( Lexer::LEFT_TAG ) ) {
            vector<double> arguments;
            string func = seq.cur();
            seq.next(); // Skip past the function name
            seq.next(); // Causes a skip of Lexer::LEFT_TAG
            
            while( (ok =! seq.empty()) )
            {
                if( seq.cur() == Lexer::RIGHT_TAG ) break; // Note, the 'Lexer::RIGHT_TAG' is removed at the end of this function!
                ok = interpStatement(seq);
                arguments.push_back(m_numBuffer);
            }
            
            if( ok ) {
                ok = callFunction(func, arguments);
            } else {
                throw string("ERROR: Incomplete statement.");
                ok = false;
            }
        }
        else if( isNumber(seq.cur()) )
        m_numBuffer = stream_cast<double>(seq.cur());
        else if ( isChar(seq.cur()) )
        m_charBuffer = stream_cast<char>(seq.cur());
        else if ( isString(seq.cur()) && seq.isNext( Lexer::RIGHT_TAG ))
        m_strBuffer = seq.cur();
        else {
            throw string("ERROR: Unknown token '" + seq.cur() + "'");
            ok = false;
        }
        
        seq.next();
        return ok;
    }
    
    bool Function::defineFunction( Parser& seq )
    {
        // Extract the function name
        if( !seq.next() ) goto badFunc;
        m_name = seq.cur();
        
        // Extract the function arguments
        if( !seq.next() ) goto badFunc;
        m_args = stream_cast<unsigned int>(seq.cur());
        if( m_args > 3 ) goto badFunc;
        
        // Search the end of the function
        while( seq.next() && !seq.isNext("func") ) // Create a user function
        m_body.append( seq.cur() );
        
        // Functions are added to the C++ set container
        m_definedFunctions.insert(*this);
        return true;
        
        badFunc:
        throw string("WARNING: Invalid function definition.");
        if( !m_name.empty() ) cout << " '" << m_name << "'" << endl;
        return false;
    }
    
    void Function::cleanVars()
    {
        m_numBuffer = NULL;
        m_charBuffer = NULL;
        m_strBuffer = "";
    }
    
    /**
     * Default system functions.
     */
    void Function::system()
    {
        m_numBuffer = 0; // Default value
        m_scope.resize(1);
        
        // Adding functions with the C++ set container
        m_definedFunctions.insert( Function(">",2) );
        m_definedFunctions.insert( Function("<",2) );
        m_definedFunctions.insert( Function("=",2) );
        m_definedFunctions.insert( Function(">=",2) );
        m_definedFunctions.insert( Function("<=",2) );
        m_definedFunctions.insert( Function("+",2) );
        m_definedFunctions.insert( Function("-",2) );
        m_definedFunctions.insert( Function("*",2) );
        m_definedFunctions.insert( Function("/",2) );
        m_definedFunctions.insert( Function("nl",0) ); // New Line
        m_definedFunctions.insert( Function("ends",0) ); // End space \0
        m_definedFunctions.insert( Function("ws",0) ); // White Space
        m_definedFunctions.insert( Function("print",1) );
        m_definedFunctions.insert( Function("println",1) ); // Print Line New
        m_definedFunctions.insert( Function("length",1) );
        m_definedFunctions.insert( Function("input",0) );
        m_definedFunctions.insert( Function("system",1) );
        
        m_specialTokens.insert( '=' );
        m_specialTokens.insert( stream_cast<char>(Lexer::LEFT_TAG) );
        m_specialTokens.insert( stream_cast<char>(Lexer::RIGHT_TAG) );
        m_specialTokens.insert( '?' );
    }
}