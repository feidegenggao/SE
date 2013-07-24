/*
 * ============================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/24/13 16:10:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "inverted_index.h"
#include    "base/log.h"
using namespace base;

int main()
{
    InvertedIndex::GetInstance()->Query("hello");
    InvertedIndex::GetInstance()->Query("高校");
    LOG_END;
    return 0;
}
