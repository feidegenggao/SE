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
#include    <vector>
#include    <string>

namespace base
{
    //FIXME:Add argument of RegexMatch that show the regex's option
    //such as ignore case 
    typedef std::string RegexSearchElementType;
    typedef std::vector<std::string> RegexSearchResultType;
    typedef RegexSearchResultType::iterator RegexSearchResultItor;
    typedef RegexSearchResultType::const_iterator RegexSearchResultConstItor;
    bool RegexMatch(const std::string &s, const std::string &regex);
    bool RegexSearch(const std::string &s, const std::string &regex, RegexSearchResultType &result);
}
#endif
