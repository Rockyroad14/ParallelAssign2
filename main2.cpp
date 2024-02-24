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

        // Decides if the Person goes and locks mutex
        void enterShowroom(int id)
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(0, 1);
            bool toGo = dist(gen);

            // Decide if person wants to visit based on randomness.
            if (toGo)
                cout << "Person " << id << " has decided to go\n";
            if (toGo)
            {
                unique_lock <mutex> locker(mtx);

                cout << "Person " << id << " has entered showroom.\n";
                isOccupied = true;
                this_thread::sleep_for(chrono::seconds(2));
                isOccupied = false;


                condition.notify_all();
            }
            else
            {
                return;
            }
            
        }

        // Runs the Showroom class
        void beginShowroom()
        {
            for(int i = 0; i < numPeople; i++)
            {
                persons.emplace_back(thread(&Showroom::enterShowroom, this, i + 1));
            }

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