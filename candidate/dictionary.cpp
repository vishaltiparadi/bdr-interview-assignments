#include <iostream>
#include <set>
#include <cstring>
using namespace std;
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define BUF_SIZE (1000000 * 255)
#define MAX_WORDS 1000000

struct shmseg {
   int cnt;
   int complete;
   char buf[BUF_SIZE];
};

static uint_least32_t wordCount;
set<string>* dictPtr;
int shmid;

/*
 * Boost IPC calls can very well be used to
 * implement shared memory logic.
 */
set<string>* sharedMemory()
{
   set<string>* setshmPtr;
   struct shmseg *shmp;

   key_t key = ftok("shmfile",65);

   shmid = shmget(key, BUF_SIZE, 0666|IPC_CREAT);
   if (shmid == -1) {
      perror("Shared memory shmget error");
      return NULL;
   }

   // Attach to the segment to get a pointer to it.
   shmp = (struct shmseg *) shmat(shmid, NULL, 0);
   if (shmp == (void *) -1) {
      perror("Shared memory attach");
      return NULL;
   }
   setshmPtr = new(shmp) set<string>;
   return setshmPtr;
}

void usage()
{
    cout << "dict {insert|search|delete} word" << endl;
}

bool searchWord(string word)
{
    bool found = false;
    auto itr = (*dictPtr).find(word);
    if(itr != (*dictPtr).end())
    {
        cout << "Input word: " << word << " found in dictionary." << endl;
        found = true;
    }
    else
    {
        cout << "Input word: " << word << " not found in dictionary." << endl;
    }

    return found;
}

bool insertWord(string word)
{
    bool found = searchWord(word);
    pair<set<string>::iterator, bool> iw;
    bool retVal = false;

    if(found)
    {
        cout << "Input word: " << word << " already present in dictionary." << endl;
    }
    else
    {
        if (wordCount >= MAX_WORDS)
        {
            cout << "Dictionary is full. Cannot insert any more words!" << endl;
        }
        else
        {
            iw = (*dictPtr).insert(word);
            if(iw.second)
            {
                cout << "Input word: " << word << " inserted in dictionary." << endl;
                wordCount ++;
                retVal = true;
            }
        }
    }
    return retVal;
}

bool deleteWord(string word)
{
    size_t count;
    bool retVal = false;
    if (searchWord(word))
    {
        count = (*dictPtr).erase(word);
    }

    if(count)
    {
        cout << "Input word: " << word << " deleted from dictionary." << endl;
        wordCount --;
        retVal = true;
    }
    return retVal;
}

int main(int argc, char** argv)
{
    bool retVal = false;
    if ( (argc > 3) || (argc == 0) )
    {
        cout << "Too many or too few arguments" << endl;
        usage();
    }
    else
    {
        dictPtr = sharedMemory();

        if ( memcmp(argv[1], "insert", 6) == 0 )
        {
            retVal = insertWord(argv[2]);
        }
        else if ( memcmp(argv[1], "search", 6) == 0 )
        {
            retVal = searchWord(argv[2]);
        }
        else if ( memcmp(argv[1], "delete", 6) == 0 )
        {
            retVal = deleteWord(argv[2]);
        }
        else
        {
            cout << "Invalid input. Exiting..." << endl;
        }
    }
    cout << endl;
    return 0;
}
