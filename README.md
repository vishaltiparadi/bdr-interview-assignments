# BDR Team Interview Home Assignments

## Instructions

1. Clone this repository.
2. Create a new branch called "candidate/${your lastname}".
3. Create a folder for one or both options listed below (bonus points for completing both).
4. Complete the assignments under the respective folders.
5. Check code into the branch and push to remote.
6. Create a pull request for review.
   
Note: **Please check in your work regardless whether you've correctly completed the assignment, for you will be expected to walkthrough your thought process with the interviewing team**

#

## Option 1 - Dictionary

A dictionary consists of english words stored in memory.
Maximum number of words in the dictionary is 1M.

Write a command-line program that allows concurrent (by multiple processes):

 * search for existence of a word in the dictionary
 * insert a word in the dictionary, if it does not exist
 * delete a word from the dictionary

The command should be invoked as following:
```
dict {insert|search|delete} <word>
```

Languages to chose from: C or C++ (no 3rd party libraries)


## Option 2 - Distributed Deadlock Detector

Based on lock queue information from individual nodes, detect deadlocks and
chose which query to kill in order to resolve it most effectively.

Sample input (example is in json but you can adjust the format to suite the
language of choice):
```
{
    "node1": { "obj1": [1, 3], "obj2": [4, 10] }
    "node2": { "obj1": [5, 4] }
    "node3": { "obj2": [3, 5] }
}
```
Meaning that on node1 the query 1 is holding lock on obj1 and query 3 is
waiting for it, query 4 is holding lock on obj2 and query 10 is waiting for
it, etc.

The queryIds represent a distrbuted queries so one query will get same
queryId on all nodes. Object names are unique across cluster.

You can assume max 1000 nodes and max 1000 queries on each node.

Languages to chose from: C, C++, Python, Perl, nodejs, SQL
