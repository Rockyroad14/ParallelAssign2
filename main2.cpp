#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <queue>
#include <chrono>

using namespace std;

class Showroom
{
    public:
        Showroom(int people)
        {
            isOccupied = false;
            for(int i = 0; i < people; i++)
            {
                persons.push_back(thread(enterShowroom));
            }

            
        }

        void enterShowroom()
        {
            unique_lock lk(mtx);

            conditional.wait(lk, []{ return ready; });


            isOccupied = true;
            this_thread::sleep_for(chrono::seconds(2));
            isOccupied = false;

            lk.unlock();

            conditonal.notify_one();
        }
    
    private:
        bool isOccupied;
        vector<thread> persons;
        mutex mtx;
        condition_variable conditonal;
        
};





int main(void)
{

}