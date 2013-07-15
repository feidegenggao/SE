/*
 * ============================================================================
 *
 *       Filename:  regex.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/15/13 11:44:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/log.h"
#include    "base/regex.h"
using namespace base;

#include    <sys/types.h>
#include    <string.h>

Regex::Regex()
{
    errcode_ = 0;
    memset(errbuf_, 0, sizeof(errbuf_));
    errmsglen_ = 0;
}

Regex::~Regex()
{
    regfree(&preg_);
}

bool Regex::IfMatch(string regex, string dst_text)
{
    if ( (errcode_ = regcomp(&preg_, regex.c_str(), 0)) == 0)
    {
        if ( (errcode_ = regexec(&preg_, dst_text.c_str(), 0, NULL, 0)) == 0)
        {
            return true;
        }
    }

    PrintErrMsg();

    return false;
}

void Regex::PrintErrMsg()
{
    if (errcode_ == REG_NOMATCH) return;

    errmsglen_ = regerror(errcode_, &preg_, errbuf_, sizeof(errbuf_));
    errmsglen_ = errmsglen_ < sizeof(errbuf_) ? (errmsglen_) : (sizeof(errbuf_) - 1);
    errbuf_[errmsglen_] = '\0';

    LOG_ERR << "Regex:" << errbuf_;
}
