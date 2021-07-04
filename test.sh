g++ normal.cpp -o normal -O2 -mcmodel=medium -std=c++11
./normal 1138_bus.mtx l.txt u.txt 
./check 1138_bus.mtx l.txt u.txt
./normal bcsstk18.mtx l.txt u.txt
./check bcsstk18.mtx l.txt u.txt