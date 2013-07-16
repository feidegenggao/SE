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
            bool IfMatch(const string &regex, const string &dst_text);
            //FIXME:
            //this regex lib has some problems that i have not fixed:
            //HOW to get more than one match string from the dst_text when more
            //than one text matches? For example:
            //regex:"t"
            //dst_text:"http://www.taobao.com/phone=3&username=lxf&&passwd=3"
            //we want to get three positions of 't' from dst_text, but the regexec
            //return only the first position of 't' match to regex.
            //TODO:
            //Currently, we only want to use the position of first match,
            //We may want to use the more position , i should fix this problem
            //
            string GetFirstMatch(const string &regex, const string &dst_text);

        private:
            regex_t preg_;
            int cflags_;
            int eflags_;
            size_t nmatch_;
            regmatch_t *pmatch_;
            int errcode_;
            char errbuf_[1024];
            size_t errmsglen_;

            void PrintErrMsg();
    };
}
#endif
