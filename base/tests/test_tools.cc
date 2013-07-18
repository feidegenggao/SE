/*
 * ============================================================================
 *
 *       Filename:  test_tools.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/18/13 14:47:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/log.h"
#include    "base/tools.h"
using namespace base;

int main()
{
    int src_num = 10;
    string dst_str = Convert<string, int>(src_num);

    LOG_INFO << "dst_str:" << dst_str;

    LOG_END;
    return 0;
}
