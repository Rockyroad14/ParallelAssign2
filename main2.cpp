#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <chrono>
#include <condition_variable>
#include <random>


using namespace std;

class Showroom
{
    private:
        
        bool isOccupied;
        int numPeople;
        vector <thread> persons;
        mutex mtx;
        condition_variable condition;
        
    public:
        Showroom(int people)
        {
            isOccupied = false;
            this->numPeople = people;
        }

        void enterShowroom()
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(0, 1);
            bool toGo = dist(gen);

            // Decide if person wants to visit based on randomness.
            if (toGo)
            {
                unique_lock <mutex> locker(mtx);
            
                isOccupied = true;
                this_thread::sleep_for(chrono::seconds(2));
                isOccupied = false;


                condition.notify_one();
            }
            else
            {
                return;
            }
            
        }

        
        void beginShowroom()
        {
            for(int i = 0; i < numPeople; i++)
            {
                persons.emplace_back(thread(&Showroom::enterShowroom, this));
            }

            //Randomly decide to que a thread
            //Somehow make it so that each thread checks if it is the thread being queued 
            //runs its shit if so

            for(auto& thread : persons)
            {
                thread.join();
            }
        }        
};





int main()
{
    int people = 0;
    cout << "Enter number of People: ";
    cin >> people;

    Showroom showroom(people);
    showroom.beginShowroom();

    return 0;
}