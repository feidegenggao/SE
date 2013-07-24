/*
 * ============================================================================
 *
 *       Filename:  inverted_index.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/24/13 19:23:07
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
#include    "base/tools.h"
using namespace base;

#include    <assert.h>
#include    <string.h>

const string INVERTED_INDEX_FILE_NAME("../index_match/inverted.index");

InvertedIndex::InvertedIndex()
{
    Init();
}

DocSetT InvertedIndex::Query(const std::string &query_str)
{
    LOG_DEBUG << "You want to query:" << query_str;
    DocSetT result_set = InvertedMap::GetInstance()->Search(query_str);
    for (DocSetT::iterator it = result_set.begin(); it != result_set.end(); ++it)
    {
        LOG_DEBUG << "*it:" << *it;
    }

    return result_set;
}

void InvertedIndex::Init()
{
    OpenInvertedIndexFile(INVERTED_INDEX_FILE_NAME);

    string this_line;
    //traversal every lien of inverted.index
    do
    {
        this_line = GetLine(fp_inverted_index);
        //reach the end of file
        if (0 == this_line.length()) break;
        LOG_DEBUG << "This line:" << this_line << "EOF";

        string::iterator it = this_line.begin();
        //traversal this_line until reach the '\n'
        
            //find the key word

            string::iterator key_word_begin = it;
            while (*it != ' ')
            {
                it++;
            }
            string::iterator key_word_end = it;
            string key_word(key_word_begin, key_word_end);
            LOG_DEBUG << "key_word:" << key_word << "eof";

            while (*it != '\n')
            {
                it++;
                string::iterator doc_id_begin = it;
                while (*it != ' ' and *it != '\n')
                {
                    LOG_DEBUG << "start while, *it:" << *it << "eof";
                    it++;
                }
                LOG_DEBUG << "After while";
                string::iterator doc_id_end = it;
                string doc_id(doc_id_begin, doc_id_end);
                LOG_DEBUG << "doc_id:" << doc_id;
                InvertedMap::GetInstance()->Insert(key_word, Convert<unsigned int, string>(doc_id));
            }

    }while(this_line.length() > 0);
}

void InvertedIndex::OpenInvertedIndexFile(const std::string &file_name)
{
    fp_inverted_index = fopen(INVERTED_INDEX_FILE_NAME.c_str(), "r");
    assert(fp_inverted_index != NULL);
}

string InvertedIndex::GetLine(FILE *fp_inverted_index)
{
    assert(fp_inverted_index != NULL);

    string this_line;

    int read_buf_len = 512;

    do
    {
        char *read_buf = new char[read_buf_len];
        memset(read_buf, 0, read_buf_len);
        char* result_buf = fgets(read_buf, read_buf_len, fp_inverted_index);

        //If file read end or reach end of the file
        if (result_buf == NULL)
        {
            delete [] read_buf;
            return this_line;
        }

        this_line += string(read_buf);

        //This fgets not reach the \n and we should retry until reach the \n
        if ('\n' != *(--this_line.end()) )
        {
            delete [] read_buf;
            continue;
        }
        else
        {
            delete [] read_buf;
            break;
        }

    }while(true);
    
    return this_line;
}
