/*
 * ============================================================================
 *
 *       Filename:  log.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 10:13:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     BASE_LOG_HEADER
#define     BASE_LOG_HEADER
#include    "base/time_stamp.h"
#include    <sys/types.h>
#include    <unistd.h>
#include    <string>
#include    <sstream>
#include    <iostream>
using std::cerr;
using std::string;
using std::stringstream;

namespace base
{
    inline string Info()
    {
        string info(Timestamp::now().toFormattedString());
        string pid;
        stringstream temp;
        temp << getpid();
        temp >> pid;

        return info + "  " +  pid;
    }

#define     COMMON_INFO  <<__FILE__<<":"<<__LINE__<< ":\t"
#define     LOG_DEBUG   cerr << "\n" << Info() << "  [DEBUG] "COMMON_INFO
#define     LOG_INFO    cerr << "\n" << Info() << "  [INFO]  "COMMON_INFO
#define     LOG_WARN    cerr << "\n" << Info() << "  [WARN]  "COMMON_INFO
#define     LOG_ERROR     cerr << "\n" << Info() << "  [ERROR]  "COMMON_INFO

}

#endif
