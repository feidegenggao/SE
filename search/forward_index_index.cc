/*
 * ============================================================================
 *
 *       Filename:  forward_index_index.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/31/13 11:06:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/log.h"
#include    "base/tools.h"
#include    "base/regex.h"
using namespace base;

#include    "forward_index_index.h"
#include    "index_match/participle.h"

#include    <assert.h>
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <fcntl.h>

#include    <string.h>

using namespace std;

ForwardIndexIndex::ForwardIndexIndex():forward_file("../index_match/forward_index.index")
{
    Init();
}

void ForwardIndexIndex::Init()
{
    string this_line;
    do
    {
        this_line = forward_file.GetLine();
        if (this_line.length() == 0) break;

        RegexSearchResultType result;
        string regex_find_offset("^([\\d]+) ([\\d]+).*$");
        RegexSearch(this_line, regex_find_offset, result);

        assert(2 == result.size());
        RegexSearchElementType doc_id = *result.begin();
        RegexSearchElementType off_set = *(++result.begin());
        forward_index_index_map_.insert(std::pair<unsigned int, off_t>
                (Convert<unsigned int, RegexSearchElementType>(doc_id),
                 Convert<off_t, RegexSearchElementType>(off_set)));
    }while(true);

    const string forwar_index_file_name("../index_match/forward.index");
    forward_index_fd_ = open(forwar_index_file_name.c_str(), O_RDONLY);
    assert(forward_index_fd_ != -1);
}

string ForwardIndexIndex::GetForwardIndexString(unsigned int doc_id) const
{
    string pariticlied_words;
    map<unsigned int, off_t>::const_iterator current_off_set  = forward_index_index_map_.find(doc_id);
    map<unsigned int, off_t>::const_iterator next_off_set = forward_index_index_map_.find(1 + doc_id);
    assert(current_off_set != forward_index_index_map_.end() and
           next_off_set != forward_index_index_map_.end());

    off_t off_set = current_off_set->second;
    size_t count = next_off_set->second - off_set;
    lseek(forward_index_fd_, off_set, SEEK_SET);
    char *buf = new char[count + 1];
    memset(buf, 0, count + 1);
    read(forward_index_fd_, buf, count);
    pariticlied_words = string(buf);

    delete [] buf;
    return pariticlied_words;
}

vector<string>::iterator FindStringInVectorString(const string &key_words,
        vector<string> &dst_vector_string)
{
    for (vector<string>::iterator it = dst_vector_string.begin();
           it != dst_vector_string.end(); it++)
    {
        if (*it == key_words)
            return it;
    } 

    return dst_vector_string.end();
}

string ForwardIndexIndex::GetSummary(const string &key_words, unsigned int doc_id) const
{
    string forward_words = GetForwardIndexString(doc_id);
    stringstream temp_stream;
    temp_stream << forward_words;

    string remove_can_not_distinguish_word = RemoveNOChinese(key_words);
    vector<string> participled_str_vector = Participle(remove_can_not_distinguish_word);

    const size_t SummaryMaxLenK = 60 * 3;
    const size_t MaxSentenceLenK = 30 * 3;
    string summary;
    string temp_line;
    vector<string>::iterator find_result_itor;
    while (temp_stream >> temp_line )
    {
        find_result_itor = FindStringInVectorString(temp_line, participled_str_vector);

        if (find_result_itor != participled_str_vector.end())
        {
            LOG_DEBUG << "find_result not end()";
            int rest_len_of_this_sentence = MaxSentenceLenK;
            rest_len_of_this_sentence -= temp_line.length();
            summary += string("<em>") + temp_line + string("</em>");
            while (rest_len_of_this_sentence > 0)
            {
                //if temp_stream reach the end
                if (! (temp_stream >> temp_line)) break;

                 find_result_itor = FindStringInVectorString(temp_line, participled_str_vector);
                 if (find_result_itor != participled_str_vector.end())
                     temp_line = string("<em>") + temp_line + string("</em>");

                summary += temp_line;
                rest_len_of_this_sentence -= temp_line.length();
            }
            participled_str_vector.erase(find_result_itor);
        }
        if (summary.length() > SummaryMaxLenK) break;
    }

    LOG_DEBUG << "SUMMAY:" << summary;

    return summary;
}
