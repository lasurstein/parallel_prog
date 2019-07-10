#include <stdio.h>	/* printf() */
#include <stdlib.h>	/* malloc(), exit() */
#include <pthread.h>

#define	BUFFER_SIZE	4
struct circular_buffer
{
	int rp ;
	int wp ;
	int used ;
	int data[BUFFER_SIZE];
	int buffer_state;
	pthread_mutex_t	mutex ;
	pthread_cond_t	not_full ;
	pthread_cond_t	not_empty ;
};

void thread_A(struct circular_buffer **b);
void thread_B(struct circular_buffer **b);

void swapping_buffer( struct circular_buffer **b) {
	struct circular_buffer *tmp;
	tmp = (struct circular_buffer *)malloc(sizeof(struct circular_buffer));
	pthread_mutex_lock( &b[0]->mutex );
	pthread_mutex_lock( &b[1]->mutex );
	// printf( "%p, %p\n", b[0], b[1]);
	tmp = b[0];
	b[0] = b[1];
	b[1] = tmp;
	// printf( "%p, %p\n", b[0], b[1]);
	pthread_mutex_unlock( &b[0]->mutex );
	pthread_mutex_unlock( &b[1]->mutex );
	free(tmp);
}


void put( struct circular_buffer **buffer, int x )
{
	struct circular_buffer *b = buffer[0];
	struct circular_buffer *c = buffer[1];
	
loop:	if( b->used == BUFFER_SIZE )
	{
		pthread_cond_wait( &b->not_full, &b->mutex );
		goto loop;
	}
	b->data[ b->wp++ ] = x ;
	b->used++ ;

	if( b->wp >= BUFFER_SIZE ){
		b->wp = 0 ;
	}

	if( b->used != 0 && c->used == 0){
		// printf( "%p, %p, buffer: %p, %p\n", b, c, buffer[0], buffer[1] );
		swapping_buffer(buffer);
		pthread_cond_broadcast( &c->not_empty );
		// printf( "%p, %p, buffer: %p, %p\n", b, c, buffer[0], buffer[1] );
	}else{
		pthread_cond_broadcast( &b->not_empty );
	}
}



int get( struct circular_buffer **buffer )
{
    int x ;
	struct circular_buffer *b = buffer[1];
	struct circular_buffer *c = buffer[0];


loop:	if( b->used == 0 )
	{
		pthread_cond_wait( &b->not_empty,&b->mutex );
		goto loop;
	}
	x = b->data[ b->rp++ ] ;
	b->used-- ;

	if( b->rp == BUFFER_SIZE ){
		swapping_buffer(buffer);
	}

	if( b->used == 0 && c->used != 0){
		// printf( "%p, %p, buffer: %p, %p\n", b, c, buffer[0], buffer[1] );
		swapping_buffer(buffer);
		// printf( "%p, %p, buffer: %p, %p\n", b, c, buffer[0], buffer[1] );
		pthread_cond_broadcast( &c->not_full );
	}else{
		pthread_cond_broadcast( &b->not_full );
	}

	return( x );
}



int main()
{
	pthread_t t1 ;
	pthread_t t2 ;
	struct circular_buffer *b[2]  ;
	
	// それぞれのバッファの初期化を行う．
	int i;
	for(i=0; i<2; i++){
		b[i] = (struct circular_buffer *)malloc(sizeof(struct circular_buffer));
			if( b[i] == NULL )
		{
			perror("no memory for struct buffer\n");
			exit( -1 );
		}
		b[i]->rp = 0 ;
		b[i]->wp = 0 ;
		b[i]->used = 0;
		b[i]->buffer_state = i;
		pthread_mutex_init( &b[i]->mutex, NULL );
		pthread_cond_init( &b[i]->not_full,NULL );
		pthread_cond_init( &b[i]->not_empty,NULL );
	}
	
	// それぞれのスレッドをforkする．
	pthread_setconcurrency( 2 );
	pthread_create( &t1, NULL, (void *)thread_A, (void *)b );
	pthread_create( &t2, NULL, (void *)thread_B, (void *)b );
	pthread_join( t1, NULL );
	pthread_join( t2, NULL );
	return( 0 );
}

void thread_A( struct circular_buffer **b )	/* producer */
{
	int i, x ;
	for( i = 0 ; i<10 ; i++ )
	{
		x = i ;
		printf("thread_A(): put( %d )\n",x );
		put( b, x );
	}
}

void thread_B( struct circular_buffer **b )	/* consumer */
{
	int i, x ;
	for( i = 0 ; i<10 ; i++ )
	{
		x = get( b );
		printf("thread_B(): get() %d.\n", x );
	}
}