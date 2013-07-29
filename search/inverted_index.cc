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
#include    "index_match/participle.h"
#include    "inverted_index.h"
#include    "base/log.h"
#include    "base/tools.h"

using namespace base;

#include    <assert.h>
#include    <string.h>
using namespace std;

const string INVERTED_INDEX_FILE_NAME("../index_match/inverted.index");

InvertedIndex::InvertedIndex()
{
    Init();
}

DocSetT InvertedIndex::Query(const std::string &query_str) const
{
    DocSetT result_doc_set;
    vector<DocSetT> doc_set_vector;
    LOG_DEBUG << "You want to query:" << query_str;
    string remove_can_not_distinguish_word = RemoveNOChinese(query_str);
    LOG_DEBUG << "After we handled, it become:" << remove_can_not_distinguish_word;

    if (remove_can_not_distinguish_word.size() == 0)
    {
        LOG_INFO << "We could not distingguish the words you input \
            We could not service you... I am sorry";
        return result_doc_set;
    }

    vector<string> participled_str_vector = Participle(remove_can_not_distinguish_word);
    for (vector<string>::iterator it = participled_str_vector.begin();
            it != participled_str_vector.end(); ++it)
    {
        DocSetT this_key_word_doc_set = QueryKeyWord(*it);
        if (this_key_word_doc_set.size() > 0)
        {
            doc_set_vector.push_back(this_key_word_doc_set);
        }
        else
        {
            //If we could not find the doc_set through this key_word
            //We will ignore this key_word
        }
    }

    result_doc_set = FindInterSection(doc_set_vector);
    return result_doc_set;
}

DocSetT InvertedIndex::QueryKeyWord(const std::string &key_word) const
{
    DocSetT result_set = InvertedMap::GetInstance()->Search(key_word);
    return result_set;
}

DocSetT InvertedIndex::FindInterSection(const std::vector<DocSetT> &doc_set_vector) const
{
    //find the intersection of multi doc_set
    DocSetT result_doc_set;
    if (doc_set_vector.size() == 0) return result_doc_set;

    vector<DocSetT>::const_iterator it = doc_set_vector.begin();
    result_doc_set = *it++;

    while(it != doc_set_vector.end())
    {
        result_doc_set = FindeInterSectionOfTwoSets(result_doc_set, *it);
        it++;
    }

    return result_doc_set;
}

DocSetT InvertedIndex::FindeInterSectionOfTwoSets(const DocSetT &left, const DocSetT &right) const
{
    DocSetT result_doc_set;
    if (left.size() == 0 or right.size() == 0) return result_doc_set;

    for (DocSetTItor it = left.begin(); it != left.end(); ++it)
    {
        if (right.end() != right.find(*it))
        {
            result_doc_set.insert(*it);
        }
    }
    return result_doc_set;
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

            while (*it != '\n')
            {
                it++;
                string::iterator doc_id_begin = it;
                while (*it != ' ' and *it != '\n')
                {
                    it++;
                }
                string::iterator doc_id_end = it;
                string doc_id(doc_id_begin, doc_id_end);
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
