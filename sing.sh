g++ $1.cpp -o $1 -O1 -L. -I. -lbass -lbassenc
LD_LIBRARY_PATH=. ./$1
