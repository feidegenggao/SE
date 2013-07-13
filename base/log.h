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
#include    <iostream>
using std::cerr;

namespace base
{
    namespace log
    {
#define     LOG_ERR     cerr<<"\n"
    }
}

#endif
