/*
 * ============================================================================
 *
 *       Filename:  search.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/29/13 10:36:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     SEARCH_HEADER
#define     SEARCH_HEADER
#include    <string>
#include    <stdint.h>

const uint16_t SEARCH_LISTEN_PORT = 19999;

//open listen port and ready for search
void StartSearch();
//query key_words
void Query(const std::string &key_word);
#endif
