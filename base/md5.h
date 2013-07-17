/*
 * ============================================================================
 *
 *       Filename:  md5.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/13 21:28:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     BASE_MD5_HEADER
#define     BASE_MD5_HEADER
#include    <string>
//YOU SHOULD COMPLIE WITH -lcrypto TO LOAD LIB
namespace base
{
    std::string MD5(const std::string &plain_text);
}
#endif
