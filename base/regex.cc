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
#include    "base/regex.h"

#include    <boost/regex.hpp>
bool base::RegexMatch(const string &s, const string &regex)
{
    boost::regex reg(regex.c_str());
    boost::smatch match_result;

    return boost::regex_match(s, match_result, reg);
}

bool base::RegexSearch(const string &s, const string &regex, RegexSearchResultType &result)
{
    boost::regex reg(regex.c_str());
    boost::smatch search_result;

    result.clear();
    if (boost::regex_search(s, search_result, reg))
    {
        for (size_t i = 1; i != search_result.size(); i++)
        {
            string temp(search_result[i]);
            result.push_back(temp);
        }
        return true;
    }

    return false;
}
