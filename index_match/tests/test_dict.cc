/*
 * ============================================================================
 *
 *       Filename:  test_dict.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/22/13 16:30:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "index_match/dict.h"
#include    "base/log.h"

using namespace base;

int main()
{
    string src_str("电子科");
    LOG_DEBUG << "src_str's length:" << src_str.length();
    if (Dict::GetInstance()->IsWord(src_str))
    {
        LOG_DEBUG << "match ";
    }
    else
    {
        LOG_DEBUG << "NOT match";
    }

    LOG_END;
    return 0;
}
