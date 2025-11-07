#include <iostream>
#include <ctime>
#include <random>
#include <pthread.h>

class P {
public:
    pthread_t tid;
    int* arr_;
    int start_;
    int end_;
    int res_;
};

void* t_sum(void* arg){
    P* td = (P*) arg;

    td->res_ = 0;
    for(int i = td->start_; i < td->end_; ++i) {
        td->res_ += td->arr_[i];
    }

    return NULL;
}

void sum(int n, int th_count) {
    int arr_[n];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 10);
    
    for (int i = 0; i < n; ++i) {
		 arr_[i] = dis(gen); 
	}


    P th_datas[th_count];
    int chunk = n / th_count;

    std::clock_t clock_start = std::clock();


    for (int i = 0; i < th_count; ++i) {
        th_datas[i].arr_ = arr_;
        th_datas[i].start_ = i*chunk;
        th_datas[i].end_ = (i == th_count-1) ? n : (i+1)*chunk;

        int threadCreated = pthread_create(&th_datas[i].tid, NULL, t_sum, (void*) &th_datas[i]); 

        if(threadCreated != 0){
            std::cerr << "Can`t create new thread" << std::endl;
        }

    }
	

    long int th_sum = 0;
    for (int i = 0; i < th_count; ++i) {
        pthread_join(th_datas[i].tid, NULL);
        th_sum += th_datas[i].res_;
    }
    std::clock_t clock_end = std::clock();
    double duration = 1000.0 * (clock_end - clock_start) / CLOCKS_PER_SEC;

    std::cout << "sum with threads took " << duration << " ms" << std::endl;
    std::cout << th_sum <<  "\n";
    

    
	//without
    clock_start = std::clock();
    long int sum_ = 0; 
    for (int i = 0; i < n; i++) { 
        sum_ += arr_[i];
    }
    clock_end = std::clock();
    duration = 1000.0 * (clock_end - clock_start) / CLOCKS_PER_SEC;

    std::cout << "sum without threads took " << duration << " ms" << std::endl;
    std::cout << sum_ << "\n";
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "wrong args\n";
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);  // arr size
    int m = atoi(argv[2]);  // cout of threads


    sum(n, m);
    return 0;
}
