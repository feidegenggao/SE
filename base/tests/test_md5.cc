/*
 * ============================================================================
 *
 *       Filename:  test_md5.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/13 21:35:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/log.h"
#include    "base/md5.h"

using namespace base;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        LOG_ERROR << "Usage:" << argv[0] << "PlainText";
        return -1;
    }

    LOG_INFO << MD5(string(argv[1]));

    LOG_END;
    return 0;
}
