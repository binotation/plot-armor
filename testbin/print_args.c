/*
    print arg1 to stdout
    print arg2 to stderr
    wait 5s
*/

#include <stdio.h>
#include <unistd.h>

int main( int argc, char **argv )
{
    if( argc < 3 )
    {
        fputs( "Usage: print_args arg1 arg2\n", stderr );
        fflush( stderr );
        return 1;
    }

    printf( "%s\n", argv[1] );
    fflush( stdout );

    fprintf( stderr, "%s\n", argv[2] );
    fflush( stderr );

    sleep(5);
    return 0;
}
