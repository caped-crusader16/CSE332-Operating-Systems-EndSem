#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <condition_variable>


using namespace std;

std::mutex mu;
std::condition_variable cond;
int cnt = 1;
int char_value = 0;

int print_char(int offset, int action){

    for(int i = 0; i < 26; i++){
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [&]{return (cnt == action);});

        
        if(action == 2)
            std::cout << char_value+1 << " ";
        else{
            char c = (char) char_value+offset;
            std::cout << c << " ";
        }
        cnt++;

        if(action == 3){
            char_value++;
            cnt = 1;
        }

        locker.unlock();
        cond.notify_all();
    
    }

    return 0;
}


int main(){
    
    std::thread t1(print_char, 65, 1);
    std::thread t2(print_char, 49, 2);
    std::thread t3(print_char, 97, 3);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}