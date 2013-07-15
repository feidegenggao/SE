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

    string regex("http://www..*.com");
    string dst_text("http://www.taobao.com");
    string dst_text_2("http://ww.taobao.com");

    CheckIt(regex, dst_text);
    CheckIt(regex, dst_text_2);

    return 0;
}
