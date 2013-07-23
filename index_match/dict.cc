/*
 * ============================================================================
 *
 *       Filename:  dict.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/22/13 16:21:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    <assert.h>
#include    <string.h>
#include    <fstream>
#include    "base/log.h"
#include    "dict.h"
using namespace std;
using namespace base;

Dict::Dict()
{
    OpenDict();
}

bool Dict::IsWord(const string &src_str)
{
    if (dict_map_.find(src_str) != dict_map_.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Dict::OpenDict()
{
    FILE *fp_dict = fopen(DICT_FILE_NAME.c_str(), "r");
    assert(fp_dict != NULL);

    //int id = 0;
    char word[50] = {0};
    //int freq = 0;

    //while (fscanf(fp_dict, "%d %s %d", &id, word, &freq) != EOF)
    while (fscanf(fp_dict, "%s", word) != EOF)
    {
        //LOG_DEBUG << "Insert into dict:" << word;
        LOG_DEBUG << "word:" << word << "\tword's length:" << strlen(word);
        dict_map_.insert(map<string, int>::value_type(word, 0));
        memset(word, 0, sizeof(word));
    }

    fclose(fp_dict);
}
