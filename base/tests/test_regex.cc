/*
 * ============================================================================
 *
 *       Filename:  test_regex.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/15/13 11:55:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/regex.h"
#include    "base/log.h"
using namespace base;

#include    <string>
using namespace std;
void CheckIt(string dst_text, string regex)
{
    if (RegexMatch(dst_text, regex))
    {
        LOG_INFO << dst_text << " matchs " << regex;
    }
    else
    {
        LOG_INFO << dst_text << " does not  match " << regex;
    }
}

void PrintSearchResult(const RegexSearchResultType &result)
{
    for (RegexSearchResultConstItor it = result.begin();
            it != result.end(); it++)
    {
        LOG_INFO << "it:" << *it << endl;
        return;
    }

    LOG_INFO << "result is null" << endl;

}

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        LOG_INFO << "Usage:" << argv[0];
    }

    string regex("http://.*/?");
    string regex2("http://www..*.com");
    string regex3("http:.*/{1,3}");
    string regex4(".*<a.*href=\"([^\"]*)\".*>.*</a>.*");
    string dst_text("http://www.taobao.com");
    string dst_text_2("http://ww.taobao.com");
    string dst_text_3("http://www.uestc.edu.cn/");
    string dst_text_4("                            <td height=\"20\">&nbsp;&nbsp;<img src=\"images/icon_3.jpg\" width=\"3\" height=\"3\" />&nbsp;<span class=\"STYLE1\"><a href=\"http://www.jwc.uestc.edu.cn\" target=\"_blank\">普通本科教学管理（教务处）</a></span></td>" );

    CheckIt(dst_text, regex);
    CheckIt(dst_text_2, regex2);
    CheckIt(dst_text_3, regex3);
    CheckIt(dst_text_4, regex4);

    string search_regex("http://([^/]*)/?");
    string search_str("http://www.uestc.edu.cn/");
    RegexSearchResultType result;

    RegexSearch(search_str, search_regex, result);
    PrintSearchResult(result);

    result.clear();
    RegexSearch(dst_text_4, regex4, result);
    PrintSearchResult(result);


    LOG_END;
    return 0;
}
