#include <iostream>
#include <vector>
#include <cmath>

// using sieve to check for prime
bool prime(int n) 
{
    if (n <= 1) 
    return false;
    if (n == 2 || n == 3) 
    return true;
    if (n % 2 == 0 || n % 3 == 0) 
    return false;
    for (int i = 5; i * i <= n; i += 6) 
    {
        if (n % i == 0 || n % (i + 2) == 0) 
        return false;
    }
    return true;
}

// function to get prime to resize the table
int nextSize(int n) 
{
    while (!prime(n)) 
    {
        n++;
    }
    return n;
}

class HashTable 
{
private:
    std::vector<int> table; // Initial Hash table
    int size; // To store current number of ele
    int cap; // Initial capacity of the table
    double loadfactor = 0.8; 

    // Hash Function Given
    int hash(int key) const 
    {
        return key % cap;
    }

    // Quadratic Probing Function
    int probe(int key, int i) const 
    {
        return (hash(key) + i * i) % cap;
    }

    // To resize the hash table when load factor exceeds 0.8
    void resize() 
    {
        int newCap = nextSize(cap * 2); //New size of the table
        std::vector<int> newTable(newCap, -1); 

        // Putting the keys in the new table
        for (int i = 0; i < cap; i++) 
        {
            if (table[i] != -1) 
            { // To check that it is not empty
                int key = table[i];
                int newHash = key % newCap;
                int j = 0;
                while (newTable[(newHash + j * j) % newCap] != -1) 
                {
                    j++;
                }
                newTable[(newHash + j * j) % newCap] = key; 
            }
        }

        table = std::move(newTable); // Replace old table with the new one
        cap = newCap; // Update capacity
    }

public:
    HashTable(int initialSize) 
    {
        cap = nextSize(initialSize); // Ensure that the size is a prime number
        table = std::vector<int>(cap, -1); // -1 represents an empty slot
        size = 0;
    }

    void insert(int key) 
    {
        // This is checking to see if this key exists
        if (search(key) != -1) 
        {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }
        // resizing if it load factor increases 0.8
        if ((double) size / cap > loadfactor) 
        {
            resize();
        }

        int i = 0;
        while (i < cap) 
        {
            int index = probe(key, i);
            if (table[index] == -1) //checking for an empty slot
            { 
                table[index] = key;
                size++;
                return;
            }
            i++;
        }

        // printing if it could not insert because probing limit has been reached
        std::cout << "Max probing limit reached!" << std::endl;
    }

    void remove(int key) 
    {
        int i = 0;
        while (i < cap) 
        {
            int index = probe(key, i);
            if (table[index] == key) 
            {
                table[index] = -1; // Marking that key as empty
                size--;
                return;
            } 
            else if (table[index] == -1) 
            { // Stopping the search if we hit an empty slot while doing quadratic probing
                std::cout << "Element not found" << std::endl;
                return;
            }
            i++;
        }
        std::cout << "Element not found" << std::endl;
    }

    int search(int key) const 
    {
        int i = 0;
        while (i < cap) 
        {
            int index = probe(key, i);
            if (table[index] == key) 
            {
                return index; // found key so returns index
            } 
            else if (table[index] == -1) 
            { // Stopping search if we hit empty slot while quadratic probing
                return -1;
            }
            i++;
        }
        return -1; // Returns -1 when key is not there
    }

    void printTable() const 
    {
        for (int i = 0; i < cap; i++) 
        {
            if (table[i] == -1) 
            {
                std::cout << "- ";
            } else 
            {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};