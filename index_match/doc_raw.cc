/*
 * ============================================================================
 *
 *       Filename:  doc_raw.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/30/13 09:51:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/log.h"
#include    "base/regex.h"
#include    "base/tools.h"
using namespace base;
#include    "doc_raw.h"

#include    <assert.h>
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <fcntl.h>
#include    <string.h>
#include    <stdio.h>
#include    <errno.h>

namespace detail
{
    int raw_file_fd = 0;
}

void OpenDocRaw(std::string raw_file_name)
{
    detail::raw_file_fd = open(raw_file_name.c_str(), O_RDONLY);
    if (detail::raw_file_fd == -1)
    {
        LOG_ERROR << "Open raw_file(" << raw_file_name << ") error: " << strerror(errno);
    }
    assert(detail::raw_file_fd != -1);
}

bool GetRawDataAndUrl(string &raw_data, string &url)
{
    string raw_header_length_str;
    char read_buf = '\0';

    //1.read raw_header_length:1234
    while(read_buf != ' ')
    {
        ssize_t readnum = read(detail::raw_file_fd, &read_buf, 1);
        if (readnum == 0 or readnum == -1) return false;
        raw_header_length_str += read_buf;
    }
    //2.get raw_header_length 
    RegexSearchResultType result;
    string regex_find_length_num("^raw_header_length:(\\d+) $");
    RegexSearch(raw_header_length_str, regex_find_length_num, result);
    assert(result.size() == 1);
    unsigned int raw_header_length_num = Convert<unsigned int, string>(*result.begin());

    //3.read raw_header
    char *raw_header_buf = new char[raw_header_length_num];
    memset(raw_header_buf, 0, sizeof(raw_header_buf));
    read(detail::raw_file_fd, raw_header_buf, raw_header_length_num);
    string raw_header_str(raw_header_buf, raw_header_length_num);
    delete [] raw_header_buf;

    //4.get url adn raw_data_length
    string regex_find_url_and_raw_data_length("^version:0\\.1url:(.+)date:.*raw_data_length:(\\d+).*$");
    RegexSearch(raw_header_str, regex_find_url_and_raw_data_length, result);
    assert(result.size() == 2);
    url = *result.begin();
    unsigned int raw_data_length_num = Convert<unsigned int, string>(*(++result.begin()));

    //5.read raw_data
    char *raw_data_buf = new char[raw_data_length_num];
    memset(raw_data_buf, 0, sizeof(raw_data_buf));
    read(detail::raw_file_fd, raw_data_buf, raw_data_length_num);
    raw_data = string(raw_data_buf, raw_data_length_num);
    delete [] raw_data_buf;

    return true;
}

off_t GetRawFileOffset()
{
    return lseek(detail::raw_file_fd, 0, SEEK_CUR);
}
