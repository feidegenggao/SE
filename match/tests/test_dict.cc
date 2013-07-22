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
#include    "match/dict.h"
#include    "base/log.h"

using namespace base;

int main()
{
    if (Dict::GetInstance()->IsWord("啊"))
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
