#include <sys/statvfs.h>
#include <iostream>
#include <cstring>
using namespace std;

int main( int argc, char *argv[] )
{
    struct statvfs fiData;

    if( argc < 2 ) {
            cout <<"Usage, ./size dir1 dir2 ... dirN\n";
            return(1);
    }

    //Lets loopyloop through the argvs
    for( int  i= 1 ; i<argc; i++ ) {
            if((statvfs(argv[i],&fiData)) < 0 ) {
                    cout << "\nFailed to stat:"  << argv[i];
            } else {
                    cout << "\nDisk: " <<  argv[i];
                    cout << "\nBlock size: "<< fiData.f_bsize;
                    cout << "\nTotal no blocks: "<< fiData.f_blocks;
                    cout << "\nFree blocks: "<< fiData.f_bfree<<endl;
            }
    }
}
