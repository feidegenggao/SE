/*
 * ============================================================================
 *
 *       Filename:  search.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/29/13 10:39:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "search/search.h"
#include    "base/log.h"
using namespace base;
#include    "net/socket.h"
#include    "net/sock_addr.h"
using namespace net;

#include    <assert.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include    <pthread.h>

static void *HandleQuery(void *p_accept_fd)
{
    int accept_fd = *((int*)p_accept_fd);
    LOG_DEBUG << "accept_fd:" << accept_fd;
    Socket accept_socket(accept_fd);
    char read_buf[1024] = {0};
    accept_socket.Read(read_buf, sizeof(read_buf) - 1);

    //If you  send data to php-cgi, we MUST add \n at the end of the string,
    //When php-cgi read data as PHP_NORMAL_READ type.
    string write_buf("Hello everyone, I am pighead\n");
    ssize_t write_n = accept_socket.Write(write_buf.c_str(), write_buf.length());
    LOG_DEBUG << "writed num:" << write_n;
    LOG_DEBUG << "read:" << read_buf;

    return NULL;
}

void StartSearch()
{
    SockAddr listen_addr(SEARCH_LISTEN_PORT);
    Socket listen_socket(listen_addr);
    listen_socket.Listen();

    while(true)
    {
        const int accept_fd = listen_socket.Accept();
        pthread_t thread_id;
        int create_thread_rt = pthread_create(&thread_id, NULL, &HandleQuery,(void*) &accept_fd);
        assert(create_thread_rt == 0);
    }
}

void Query(const std::string &key_word)
{

}
