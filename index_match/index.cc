/*
 * ============================================================================
 *
 *       Filename:  index.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/13 16:55:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "index.h"
#include    "inverted_map.h"
#include    "participle.h"
#include    "base/log.h"
#include    "base/tools.h"
using namespace base;
#include    <assert.h>
#include    <sys/stat.h>
#include    <fcntl.h>

#include    <sstream>
using namespace std;

void Index::OpenAllIndexFiles()
{
    doc_index_file_fd_ = OpenFile("doc.index");
    url_index_file_fd_ = OpenFile("url.index");
    forward_index_file_fd_ = OpenFile("forward.index");
    forward_index_index_file_fd_ = OpenFile("forward_index.index");
    inverted_index_file_fd_ = OpenFile("inverted.index");
}

int Index::OpenFile(const string &filename)
{
    int fd = open(filename.c_str(), O_CREAT | O_RDWR | O_TRUNC, S_IRUSR);
    assert(fd != -1);
    return fd;
}

void Index::WriteToDocIndex(const unsigned int doc_id, const off_t doc_offset, const string &doc_md5)
{
    string write_str = Convert<string, unsigned int>(doc_id) + ' ' +
        Convert<string, off_t>(doc_offset) + ' ' + doc_md5 + '\n';

    Write(doc_index_file_fd_, write_str.c_str(), write_str.length());
}

void Index::WriteToUrlIndex(const unsigned int doc_id, const string &url_md5)
{
    string write_str = url_md5 + ' ' + Convert<string, unsigned int>(doc_id) + '\n';

    Write(url_index_file_fd_, write_str.c_str(), write_str.length());
}

string RemoveHTMLLLabel(const string &html_line)
{
    //extract valid data from html
    //remove html-lable and js and other invlid data for browser user
    string dst_str;
    for (string::const_iterator it = html_line.begin(); it != html_line.end(); it++)
    {
        if (*it == '<')
        {
            while(it != html_line.end() and *it != '>')
            {
                it++;
            }
            if (it == html_line.end()) break;
        }
        else
        {
            if (
                    *it == ' ' or //!= space
                    *it == '\t' or 
                    *it == '\n' or 
                    *it == '\r'
               )
            {

            }
            else
            {
                dst_str += *it;
            }
        }
    }
    return dst_str;
}

void Index::WriteToForwardIndex(const unsigned int doc_id, const string &html_data)
{
    stringstream temp_stream;
    temp_stream << html_data;
    string html_line;
    string forward_index_str = Convert<string, const unsigned int>(doc_id);
    while (getline(temp_stream, html_line))
    {
        if (html_line.length() == 0) continue;

        string dst_str = RemoveHTMLLLabel(html_line);

        if (dst_str.length() != 0)
        {
            string only_chinese_str = RemoveNOChinese(dst_str);
            //participled_str instead of HanZi that have been participled
            vector<string> participled_str_vector = Participle(only_chinese_str);
            for (vector<string>::iterator it = participled_str_vector.begin();
                    it != participled_str_vector.end(); ++it)
            {
                forward_index_str = forward_index_str + SEPARATOR + *it;
                InvertedMap::GetInstance()->Insert(*it, doc_id);
            }
        }
    }
    forward_index_str += '\n';
    off_t forward_index_file_cur_off_set = lseek(forward_index_file_fd_, 0, SEEK_CUR);
    string forward_index_index_str = Convert<string, unsigned int>(doc_id) + SEPARATOR +
        Convert<string, off_t>(forward_index_file_cur_off_set) + "\n";
    Write(forward_index_index_file_fd_, forward_index_index_str.data(), forward_index_index_str.length());
    Write(forward_index_file_fd_, forward_index_str.c_str(), forward_index_str.length());
}

void Index::WriteTheLastIndeToForwardIndexIndex(unsigned int doc_id)
{
    off_t forward_index_file_cur_off_set = lseek(forward_index_file_fd_, 0, SEEK_CUR);
    string forward_index_index_str = Convert<string, unsigned int>(doc_id) + SEPARATOR +
        Convert<string, off_t>(forward_index_file_cur_off_set) + "\n";
    Write(forward_index_index_file_fd_, forward_index_index_str.data(), forward_index_index_str.length());
}

void Index::WriteToInvertedIndex()
{
    LOG_DEBUG << "WriteToFile";
    InvertedMapT inverted_map = InvertedMap::GetInstance()->GetInvertedMap();
    for (InvertedMapTItor start = inverted_map.begin(); start != inverted_map.end(); ++start)
    {
        std::string dst_str = start->first;
        std::string doc_id_str;
        for (DocSetTItor doc_set_it = start->second.begin(); doc_set_it != start->second.end(); ++doc_set_it)
        {
            doc_id_str = doc_id_str + ' ' + Convert<string, unsigned int>(*doc_set_it);
        }
        doc_id_str += '\n';

        dst_str += doc_id_str;
        Write(inverted_index_file_fd_, dst_str.c_str(), dst_str.length());
    }
}

int Index::Write(int file_fd, const void *write_buf, size_t count)
{
    return write(file_fd, (const void *)write_buf, count);
}


