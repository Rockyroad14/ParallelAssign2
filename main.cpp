#include<iostream>
#include<thread>
#include<cstdlib>
#include<mutex>
#include<vector>
#include<condition_variable>

using namespace std;
int currentIndex = 0;
bool cup_cake = true;
int count = 0;

struct guest
{
    // 0 is if counter, 1 is if hasPlace
    bool array[2] = {false, false};
};

vector<thread> People;
mutex mtx;
condition_variable condition;

int count2 = 0;
void guestAction(int id, guest* guests, int N)
{
    while(count != N)
    {    
        mtx.lock();
        if((cup_cake == false) && (id == currentIndex) && (guests[id].array[1] == false) && (currentIndex != 0))
        {
            cout << "NONCOUNTER GUEST " << id << endl;
            guests[id].array[1] = true;
            cup_cake = true;
            count2 += 1;
        }
        else if(cup_cake == true && id == 0 && currentIndex == 0)
        {
            cout << "COUNTER GUEST " << id << endl;
            count += 1;
            cup_cake = false;
            
        }
        mtx.unlock();
    }
   
}
int main()
{
    int N;
    cout << "Starting sim" << endl;

    cout << "Enter number of Guests: ";
    cin >> N;
    guest guests[N];

    srand((unsigned) time(NULL));

    //Designating counter guest
    guests[0].array[0] = true;
    guests[0].array[1] = true; //doesn't matter for the counter
    People.push_back(thread(guestAction,0, guests, N));

    //Initialize guests
    for(int i = 1; i < N; i++)
    {
            guests[i].array[0] = false;
            guests[i].array[1] = false;
            People.push_back(thread(guestAction,i, guests, N));
    }

    while(count != N)
    {
        // Minotaur picks the next person at random
        currentIndex = rand() % N;
    }

   


    for(auto& Person : People)
        {
            if(Person.joinable())
            {
                Person.join();
            }
        }

    for(int i = 0; i  < N;i++)
    {
        cout <<"GUEST" << i + 1 << ": hasPlaced " << guests[i].array[1] << endl;
    }
    
    cout << "Simulation finished in " << duration.count() << " milliseconds." << endl;
    cout << "All " << count << " guests have been in the labryinth" << endl;
    return 0;
}