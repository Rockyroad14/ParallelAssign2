#include <iostream>
#include <thread>
#include <cstdlib>
#include <mutex>
#include <vector>
#include <condition_variable>

using namespace std;

int currentIndex = 0;
bool cupCake = true;
int count = 0;

struct guest
{
    // 0 is if counter, 1 is if hasPlace
    bool array[2] = {false, false};
};

vector<thread> People;
mutex m;
condition_variable condition;

void countGuestAction(int id, guest guests[], int N);

int count2 = 0;

// Mutex locking occurs here to make sure no thread can access the same variable at the same time
void guestAction(int id, guest guests[], int N)
{

    while(count != N)
    {    
        m.lock();
        countGuestAction(id, guests, N);
        m.unlock();
    }
   
}

void countGuestAction(int id, guest guests[], int N)
{
    if((cupCake == false) && (id == currentIndex) && (guests[id].array[1] == false) && (currentIndex != 0))
    {
        cout << "NONCOUNTER GUEST " << id << endl;
        guests[id].array[1] = true;
        cupCake = true;
        count2 += 1;
    }
    else if(cupCake == true && id == 0 && currentIndex == 0)
    {
        cout << "COUNTER GUEST " << id << endl;
        count += 1;
        cupCake = false;
    }

}

void initializeGuests(guest *guests, int N)
{
    for(int i = 1; i < N; i++)
    {
        guests[i].array[0] = false;
        guests[i].array[1] = false;
        People.push_back(thread(guestAction, i, guests, N));
    }
}

void randomGuestSelector(int N)
{
    while(count != N)
    {
        // Minotaur picks the next person at random
        currentIndex = rand() % N;
    }
}

void debuggingPrint(guest *guests, int N)
{
    for(int i = 0; i  < N;i++)
    {
        cout <<"GUEST" << i + 1 << ": has placed a cupcake?: " << guests[i].array[1] << endl;
    }
}

void joinThreads()
{
    for(auto& Person : People)
    {
        if(Person.joinable())
        {
            Person.join();
        }
    }
}

int main()
{
    
    int N;
    cout << "Enter Number of Guests: ";
    cin >> N;

    guest* guests = (guest*) malloc(sizeof(guest) * N);
    

    //Designating counter guest
    guests[0].array[0] = true;
    guests[0].array[1] = true; //doesn't matter for the counter
    People.push_back(thread(guestAction, 0, guests, N));

    // Setting the rest of the guests that are not counters.
    initializeGuests(ref(guests), N);

    // Minotaur telling which guests to go in random order.
    randomGuestSelector(N);

    // join all threads back together.
    joinThreads();

    cout << "All " << count << " guests have been in the labryinth" << endl;

    free(guests);
    return 0;
}