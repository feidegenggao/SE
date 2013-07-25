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
#include    "inverted_map.h"
#include    "dict.h"
using namespace std;
const unsigned int WORD_LEN = 3;//Every HanZi use 3 bytes to store(UTF-8)
const unsigned int MAX_WORDS_LEN = 4;//The max length of sentence

int Min(int left, int right)
{
    return left < right ? left : right;
}


vector<string> Participle(string src_str)
{
    vector<string> participled_str_vector;

    while(src_str.length() != 0)
    {
        int len = Min(src_str.length(), (MAX_WORDS_LEN * WORD_LEN));
        string key_word;
        do{
            key_word = string(src_str, 0, len);
            //find it
            if (Dict::GetInstance()->IsWord(key_word))
            {
                participled_str_vector.push_back(key_word);
                break;
            }
            else
            {
                len -= WORD_LEN;
            }

            if (key_word.length() == WORD_LEN)
            {
                participled_str_vector.push_back(key_word);
                if (len == 0) len = WORD_LEN;
                break;
            }
            //not find it
        }while(true);


        src_str.erase(0, len);
    }

    return participled_str_vector;
}

string RemoveNOChinese(const string &dst_str)
{
    //FIXME:
    //We only handle the HanZi, We should handle other language
    string only_chinese_str;
    string null_str;
    for (string::const_iterator it = dst_str.begin(); it != dst_str.end(); it++)
    {
        if (0 == (*it & 0x80))//0000 0000-0000 007F
        {

        }
        else if (0 == (*it & 0x20))//0000 0080-0000 07FF
        {
            it++;
            //If some codes was illegal , we should handle this condition
            if (it == dst_str.end()) return null_str;
        }
        else if (0 == (*it & 0x10))//0000 0800-0000 FFFF
        {
            string temp;
            temp += *it;

            for (int i = 0; i < 2; i++)
            {
                it++;
                //If some codes was illegal , we should handle this condition
                if (it == dst_str.end()) return null_str;
                temp += *it;
            }

            only_chinese_str += temp;
        }
        else if (0 == (*it & 0x08))//0001 0000-0010 FFFF
        {
            for (int i = 0; i < 3; i++)
            {
                it++;
                //If some codes was illegal , we should handle this condition
                if (it == dst_str.end()) return null_str;
            }
        }
    }

    return only_chinese_str;
}
