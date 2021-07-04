g++ normal.cpp -o normal -O2 -mcmodel=medium -std=c++11 -fopenmp
./normal 1138_bus.mtx l3.txt u3.txt 
# ./check 1138_bus.mtx l3.txt u3.txt
./normal bcsstk18.mtx l3.txt u3.txt
# ./check bcsstk18.mtx l3.txt u3.txt