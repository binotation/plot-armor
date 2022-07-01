/*
    print "Running normally"
    wait 5s
    open and read non-existent file -> segfault
*/

#include <stdio.h>
#include <unistd.h>

int main( void )
{
    fputs( "Running normally\n", stdout );
    fflush( stdout );

    FILE *file = fopen( "non_existent.txt", "r" );
    sleep(5);
    int c = fgetc( file );

    return c;
}
