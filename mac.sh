g++ faq.cpp -o problem_3 -mcmodel=medium -I /usr/local/opt/libomp/include/ -L /usr/local/opt/libomp/lib -lomp -O2 -std=c++11
./problem_3 1138_bus.mtx l1.txt u1.txt 
./check 1138_bus.mtx l1.txt u1.txt
./problem_3 bcsstk18.mtx l1.txt u1.txt
./check bcsstk18.mtx l1.txt u1.txt