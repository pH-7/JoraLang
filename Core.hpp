//
//  Core.hpp
//  JoraLang
//
//  Created by Pierre-Henry Soria on 31/07/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//

#ifndef Core_hpp
#define Core_hpp

#include <iostream>

namespace JoraLang
{
    class Core
    {
        public:
        static const char* VERSION;
        static const std::string NAME;
        static std::string softwareInfo();
        static std::string softwareVersion();
        static std::string showHelp();
        static std::string showLicense();
        static std::string showCredits();
    };
}

#endif /* Core_hpp */
