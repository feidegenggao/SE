/*
 * ============================================================================
 *
 *       Filename:  md5.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/13 21:30:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/md5.h"
using namespace std;

#include    <string.h>
#include    <stdio.h>
#include    <openssl/md5.h>
string base::MD5(const string &plain_text)
{
    string result;
    unsigned char md[17] = {0};
    ::MD5((const unsigned char *)plain_text.c_str(), plain_text.length(), md);

    char buf_temp[3] = {0};
    for (size_t i = 0; i < strlen((const char*)md); i++)
    {
        memset(buf_temp, 0, sizeof(buf_temp));
        sprintf(buf_temp, "%x", md[i]);
        result += buf_temp;
    }

    return result;
}
