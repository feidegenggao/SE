/*
 * ============================================================================
 *
 *       Filename:  http.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/13 17:18:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     HTTP_HEADER
#define     HTTP_HEADER
#include    <string>
class Url;
bool GetPage(const Url &server_url, std::string &http_header, std::string &http_data);
#endif
