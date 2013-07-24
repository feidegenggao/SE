/*
 * ============================================================================
 *
 *       Filename:  test_inverted_map.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/24/13 15:18:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "index_match/inverted_map.h"
using namespace base;

#include    "base/log.h"

int main()
{
    string key_word("Hello");
    unsigned int doc_id = 2;
    InvertedMap::GetInstance()->Insert(key_word, doc_id);
    InvertedMap::GetInstance()->Insert(key_word, 3);
    InvertedMap::GetInstance()->Insert("Kitty", doc_id);
    InvertedMap::GetInstance()->WriteToFile();

    LOG_END;
    return 0;
}
