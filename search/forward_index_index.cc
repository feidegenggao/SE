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

string ForwardIndexIndex::GetSummary(unsigned int doc_id) const
{
    string summary;
    LOG_DEBUG << "summary:" << GetForwardIndexString(doc_id);
    return summary;
}
