/*
 * ============================================================================
 *
 *       Filename:  regex.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/15/13 11:35:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     BASE_REGEX_HEADER
#define     BASE_REGEX_HEADER
#include    "base/singleton.h"

#include    <string>
using std::string;

#include    <regex.h>
namespace base
{
    class Regex : public Singleton<Regex>
    {
        public:
            Regex();
            ~Regex();
            bool IfMatch(string regex, string dst_text);

        private:
            regex_t preg_;
            int errcode_;
            char errbuf_[1024];
            size_t errmsglen_;

            void PrintErrMsg();
    };
}
#endif
