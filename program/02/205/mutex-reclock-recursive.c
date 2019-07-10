/*
 * mutex-reclock-recursive.c -- �Ƶ�Ū mutex ��Ȥ���
 */

#include <stdio.h>	/* printf() */
#include <pthread.h>

void thread_A(), thread_B();
int	shared_resource ;
pthread_mutex_t mutex1 ;

void deposit( int n )
{
	pthread_mutex_lock( &mutex1 );
	shared_resource += n ;
	pthread_mutex_unlock( &mutex1 );
}

void add_interest()
{
    int i ;
	pthread_mutex_lock( &mutex1 );
	i = shared_resource * 0.05 ;
	deposit( i );
	pthread_mutex_unlock( &mutex1 );
}

static int my_pthread_mutex_init_recursive( pthread_mutex_t *mutex )
{
    pthread_mutexattr_t attr ;
    int err ;
	if( (err=pthread_mutexattr_init( &attr )) < 0 )
	    return( 0 );
    	if( (err=pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE)) <0 )
	    return( 0 );
    	err = pthread_mutex_init( mutex,&attr );
    	return( err );
}

int main()
{
    pthread_t t1 ;
    pthread_t t2 ;
	shared_resource = 1000000 ;
	my_pthread_mutex_init_recursive( &mutex1 );

	pthread_create( &t1, NULL, (void *)thread_A, 0 );
	pthread_create( &t2, NULL, (void *)thread_B, 0 );
	pthread_join( t1, NULL );
	pthread_join( t2, NULL );
	printf("main(): shared_resource == %d\n", shared_resource );
	return( 0 );
}

void thread_A()
{
	printf("thread_A(): deposit( 10000 ) ... \n");
	deposit( 10000 );	
	printf("thread_A(): deposit( 10000 ) done. \n");
}

void thread_B()
{
	printf("thread_B(): add_interest() ... \n");
	add_interest();
	printf("thread_B(): add_interest() done. \n");
}
