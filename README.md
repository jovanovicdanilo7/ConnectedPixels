# ConnectedPixels
Program gets matrix of zeros and ones. User gives coordinates of pixel for which he wants to find his neighbor pixels with same value, as well as all neighboring pixels of the same value to its equivalent neighbors, etc. The module is implemented as a dynamic library.

HOW TO RUN:

Position yourself at the location of "matrix" directory and execute following commands:

    gcc -c -fpic matrix.c
  
    gcc -shared -o libmatrix.so matrix.o
  
    cd ..
  
Now you will need your current workspaces, which you can get with this command:

    pwd
  
Then you copy your current workspace instead of mine in following command and execute it:

    export LD_LIBRARY_PATH=/workspaces/137607718/NapredniCe/projekat/matrix:$LD_LIBRARY_PATH
  
    gcc -Imatrix/ -Lmatrix/ -o app main.c
  
    ./app
