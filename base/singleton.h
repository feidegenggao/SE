/*
 * ============================================================================
 *
 *       Filename:  singleton.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/14/13 19:36:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     BASE_SINGLETON_HEADER
#define     BASE_SINGLETON_HEADER
#include    <pthread.h>
namespace base
{
    template  <typename T>
        class Singleton
        {
            public:
                virtual ~Singleton(){}
                static T*  GetInstance()
                { 
                    pthread_once(&only_once_, &Singleton::init_routine);
                    return self_;
                }

            protected:
                Singleton(){}

            private:
                Singleton(const Singleton &);
                Singleton& operator = (const Singleton &);

            private:
                static pthread_once_t only_once_;
                static T *self_;
                static void init_routine()
                {
                    self_ = new T();
                }
        };
    template <typename T>
        T * Singleton<T>::self_ = NULL;
    template <typename T>
        pthread_once_t Singleton<T>::only_once_ = PTHREAD_ONCE_INIT;
}
#endif
