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
void CheckIt(string regex, string dst_text)
{
    if (Regex::GetInstance()->IfMatch(regex, dst_text))
    {
        LOG_INFO << dst_text << " matchs " << regex;
    }
    else
    {
        LOG_INFO << dst_text << " does not  match " << regex;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        LOG_INFO << "Usage:" << argv[0];
    }

    string regex("http://.*/?");
    string regex2("http://www..*.com");
    string dst_text("http://www.taobao.com");
    string dst_text_2("http://ww.taobao.com");

    CheckIt(regex, dst_text);
    CheckIt(regex2, dst_text_2);

    string get_str_regex("http://.*/{1}");
    string dst_text_3("http://www.uestc.edu.cn/page?3&&name=lxf");
    string dst_text_4("http://www.gmc.uestc.edu.cn/page?3&&name=lxf&&passwd=123");
    string get_str_regex5("http://.*/");
    string dst_text_5("http://www.gmc.uestc.edu.cn");
    string result;
    result = Regex::GetInstance()->GetFirstMatch(get_str_regex, dst_text_3);
    LOG_INFO << "result:" << result;
    result = Regex::GetInstance()->GetFirstMatch(get_str_regex, dst_text_4);
    LOG_INFO << "result:" << result;
    result = Regex::GetInstance()->GetFirstMatch(get_str_regex5, dst_text_5);
    LOG_INFO << "result:" << result;
    LOG_INFO << "\n";
    return 0;
}
