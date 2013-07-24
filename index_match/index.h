/*
 * ============================================================================
 *
 *       Filename:  index.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/13 16:51:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     INDEX_HEADER
#define     INDEX_HEADER
#include    <string>
#include    <sys/types.h>
class Index
{
    private:
        Index& operator = (const Index&);
        Index(const Index&);

    public:
        //If doc_md5 is null, we can guess that this is the end of doc.indx
        static void WriteToDocIndex(const unsigned int doc_id, const off_t doc_offset, const std::string &doc_md5 = std::string(""));
        static void WriteToUrlIndex(const unsigned int doc_id, const std::string &url_md5);
        static void WriteToForwardIndex(const unsigned int doc_id, const std::string &html_data);
        static void WriteToInvertedIndex(const std::string &data);

    private:
        static int doc_index_file_fd_;
        static int url_index_file_fd_;
        static int forward_index_file_fd_;
        static int inverted_index_file_fd_;
        static int OpenFile(const std::string &filename);
        static int WriteDocIndex(const void *write_buf, size_t count);
        static int WriteUrlIndex(const void *write_buf, size_t count);
        static int Write(int file_fd, const void *write_buf, size_t count);
};
#endif
