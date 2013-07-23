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
#include    "base/tools.h"
using namespace std;
using namespace base;
#include    <assert.h>
#include    <sys/stat.h>
#include    <fcntl.h>

int Index::doc_index_file_fd_ = OpenFile("doc.index");
int Index::url_index_file_fd_ = OpenFile("url.index");
int Index::OpenFile(const string &filename)
{
    int fd = open(filename.c_str(), O_CREAT | O_RDWR | O_TRUNC, S_IRUSR);
    assert(fd != -1);
    return fd;
}

void Index::WriteToDocIndex(unsigned int doc_id, off_t doc_offset, const string &doc_md5)
{
    string write_str = Convert<string, unsigned int>(doc_id) + ' ' +
        Convert<string, off_t>(doc_offset) + ' ' + doc_md5 + '\n';

    Write(doc_index_file_fd_, write_str.c_str(), write_str.length());
}

void Index::WriteToUrlIndex(const string &url_md5, unsigned int doc_id)
{
    string write_str = url_md5 + ' ' + Convert<string, unsigned int>(doc_id) + '\n';

    Write(url_index_file_fd_, write_str.c_str(), write_str.length());

}

int Index::Write(int file_fd, const void *write_buf, size_t count)
{
    return write(file_fd, (const void *)write_buf, count);
}
