/*
 * ============================================================================
 *
 *       Filename:  test_file.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/31/13 10:20:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/file.h"
#include    "base/log.h"
using namespace base;

#include    <string>
using namespace std;

int main()
{
    File temp_file("./test_file.cc");

    string read_line;

    do 
    {
        read_line = temp_file.GetLine();
        if (read_line.length() == 0)
            break;
        else
            LOG_DEBUG << "read_line:" << read_line;
    }while(true);

    LOG_END;

    return 0;
}
