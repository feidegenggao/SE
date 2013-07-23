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
#include    "participle.h"
#include    "base/log.h"
#include    "base/tools.h"
using namespace base;
#include    <assert.h>
#include    <sys/stat.h>
#include    <fcntl.h>

#include    <sstream>
using namespace std;

int Index::doc_index_file_fd_ = OpenFile("doc.index");
int Index::url_index_file_fd_ = OpenFile("url.index");
int Index::forward_index_file_fd_ = OpenFile("foward.index");
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
            LOG_DEBUG << "dst_str:" << dst_str;
            LOG_DEBUG  << "length:" << dst_str.length();
            string only_chinese_str = RemoveNOChinese(dst_str);
            //participled_str instead of HanZi that have been participled
            string participled_str = Participle(only_chinese_str);
            forward_index_str += participled_str;
            LOG_DEBUG << "only_chinese_str:" << only_chinese_str;
        }
    }
    LOG_DEBUG << "forward_index_str:" << forward_index_str << "EOF";
}

int Index::Write(int file_fd, const void *write_buf, size_t count)
{
    return write(file_fd, (const void *)write_buf, count);
}
