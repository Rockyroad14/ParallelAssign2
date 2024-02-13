#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <thread>
#include <vector>
#include <future>
#include <mutex>

using namespace std;

struct guests
{
    bool counterPerson;
    int counter;
};

class Guest {
    Guest(int total_guests, bool isCounter) : total_guests(total_guests), cupcake_available(true), counter(isCounter) {}
    public:
        void enterLabyrinth() {
            std::lock_guard<std::mutex> lock(mutex);

        }


    
    
    
    private: 
        int total_guests;
        bool cupcake_available;
        bool counter;
        std::mutex mutex;

        
};

void guestThread(Guest& guest, bool counter)
{

}


int main(void)
{
    bool counter = false;
    int N;
    std::cout << "Enter the number of guests: ";
    std::cin >> N;

    Guest guest(N)

    std::vector<std::thread> threads;

    for(int i = 0; i < N; i++)
    {
        if(i == N-1)
        {
            counter = true;
        }
        threads.emplace_back(guestThread, std::ref(guest), )
    }

    

}