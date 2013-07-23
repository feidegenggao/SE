/*
 * ============================================================================
 *
 *       Filename:  participle.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/23/13 11:05:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/log.h"
using namespace base;
#include    "participle.h"
#include    "dict.h"
using namespace std;
const unsigned int WORD_LEN = 3;//Every HanZi use 3 bytes to store(UTF-8)
const unsigned int MAX_WORDS_LEN = 4;//The max length of sentence

int Min(int left, int right)
{
    return left < right ? left : right;
}

string Participle(string src_str)
{
    string participled_str;

    while(src_str.length() != 0)
    {
        int len = Min(src_str.length(), (MAX_WORDS_LEN * WORD_LEN));
        string key_word;
        do{
            key_word = string(src_str, 0, len);
            //find it
            if (Dict::GetInstance()->IsWord(key_word))
            {
                LOG_DEBUG << "key_word:" << key_word;
                break;
            }
            //not find it
            else len -= WORD_LEN;
        }while(key_word.length() != WORD_LEN);

        LOG_DEBUG << "key_word:" << key_word;

        src_str.erase(0, len);
    }

    return participled_str;
}
