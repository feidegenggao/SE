/*
 * ============================================================================
 *
 *       Filename:  participle.h
 *
 *    Description:  The major working in this file is to participle
 *    Input: the html doc
 *    Output: the string that string separte by SEPARATOR 
 *
 *        Version:  1.0
 *        Created:  07/23/13 11:01:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     PARTICIPLE_HEADER
#define     PARTICIPLE_HEADER
#include    <string>
#include    <vector>

const std::string SEPARATOR(" ");
std::vector<std::string> Participle(std::string src_str);
std::string RemoveNOChinese(const std::string &dst_str);
#endif
