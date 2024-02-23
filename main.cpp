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
const int N = 10;

struct guest
{
    bool counter=false;
    bool has_placed=false; 
};
guest guests[N];
vector<thread> threads;
mutex mtx;
condition_variable cv;

int count2 = 0;
void guestAction(int id)
{
    while(count != N)
    {    
        mtx.lock();
        if((cup_cake == false) && (id == currentIndex) && (guests[id].has_placed == false) && (currentIndex != 0))
        {
            cout << "NONCOUNTER GUEST " << id << endl;
            guests[id].has_placed = true;
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
    cout << "Starting sim...." << endl;

    srand((unsigned) time(NULL));

    //Designating counter guest
    guests[0].counter = true;
    guests[0].has_placed = true; //doesn't matter for the counter
    threads.push_back(thread(guestAction,0));

    //Initialize guests
    for(int i = 1; i < N; i++)
    {
            guests[i].counter = false;
            guests[i].has_placed = false;
            threads.push_back(thread(guestAction,i));
    }

    auto start = chrono::high_resolution_clock::now();

    while(count != N)
    {
        //Generate a random number between 0 and N
        currentIndex = rand() % N;
        cout<<"index:"<< currentIndex <<endl;
        cout <<"Guests Gone:" << count << endl; 
    }

   


    for(auto& t : threads)
        {
            if(t.joinable())
            {
                t.join();
            }
        }

    for(int i = 0; i  < N;i++)
    {
        cout <<"GUEST" << i << ": hasPlaced " << guests[i].has_placed << endl;
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Simulation finished in " << duration.count() << " milliseconds." << endl;
    cout << "All " << count << " guests have been in the labryinth" << endl;
    return 0;
}