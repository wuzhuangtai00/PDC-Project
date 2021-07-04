g++ faq.cpp -o problem_3 -O2 -mcmodel=medium -std=c++11 -fopenmp
./normal 1138_bus.mtx l1.txt u1.txt 
./check 1138_bus.mtx l1.txt u1.txt
./normal bcsstk18.mtx l1.txt u1.txt
./check bcsstk18.mtx l1.txt u1.txt