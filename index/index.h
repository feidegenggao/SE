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
class Index
{
    private:
        Index& operator = (const Index&);
        Index(const Index&);

    public:
        //If doc_md5 is null, we can guess that this is the end of doc.indx
        static void WriteToDocIndex(unsigned int doc_id, off_t doc_offset, const string &doc_md5 = string(""));
        static void WriteToUrlIndex(const string &url_md5, unsigned int doc_id);

    private:
        static int doc_index_file_fd_;
        static int url_index_file_fd_;
        static int OpenFile(const string &filename);
        static int WriteDocIndex(const void *write_buf, size_t count);
        static int WriteUrlIndex(const void *write_buf, size_t count);
};
#endif