#include <stdio.h>
#include <pthread.h>

void thread_A(), thread_B(), thread_C();
int     shared_resource ;
pthread_mutex_t mutex1 ;

int main() {
    pthread_t t1 ;
    pthread_t t2 ;
    pthread_t t3 ;
        shared_resource = 0 ;
        pthread_mutex_init( &mutex1, NULL );
        pthread_setconcurrency( 3 );
        pthread_create( &t1, NULL, (void *)thread_A, 0 );
        pthread_create( &t2, NULL, (void *)thread_B, 0 );
        pthread_create( &t3, NULL, (void *)thread_C, 0 );
        pthread_join( t1, NULL );
        pthread_join( t2, NULL );
        pthread_join( t3, NULL );
        printf("main(): shared_resource == %d\n", shared_resource );
        return( 0 );
}

void thread_A()
{
    int i, x ;
        for( i = 0 ; i<1000000 ; i++ )
        {
            pthread_mutex_lock( &mutex1 );
            x = shared_resource ;
            x = x + 1 ;
            shared_resource = x ;
            pthread_mutex_unlock( &mutex1 );
        }
}

void thread_B() {
    int i, x ;
        for( i = 0 ; i<1000000 ; i++ ) {
            pthread_mutex_lock( &mutex1 );
            x = shared_resource ;
            x = x + 1 ;
            shared_resource = x ;
            pthread_mutex_unlock( &mutex1 );
        }
}

void thread_C() {
    int i, x ;
        for( i = 0 ; i<1000000 ; i++ ) {
            pthread_mutex_lock( &mutex1 );
            x = shared_resource ;
            x = x + 1 ;
            shared_resource = x ;
            pthread_mutex_unlock( &mutex1 );
        }
}