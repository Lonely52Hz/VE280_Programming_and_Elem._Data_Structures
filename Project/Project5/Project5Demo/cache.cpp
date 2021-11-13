#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include "dlist.h"

using namespace std;

class LRUCache {
private:
    int mem_size; // size of memory
    int* memory;
    struct block {
        int address; // its address in memory
        int data;
    };
    Dlist<block> cache;
    int cur_cache_size; // current length of `cache`
    int max_cache_size; // maximum length of `cache`

    static bool compare(const block* a, const block* b);
    // EFFECTS: returns true if two blocks have the same address

public:
    LRUCache(int cache_size, int memory_size);
    // EFFECTS: constructor

    ~LRUCache();
    // EFFECTS: destructor
    
    int read(int address);
    // EFFECTS: returns data corresponding to address,

    void write(int address, int data);
    // EFFECTS: writes data to address
    
    void printCache();
    // EFFECTS: prints the cache in given format

    void printMem();
    // EFFECTS: prints the memory in given format
};

bool LRUCache::compare(const block* a, const block* b) {
    // EFFECTS: returns true if two blocks have the same address
    if (a->address == b->address) {
        return true;
    }
    else {
        return false;
    }
}

LRUCache::LRUCache(int cache_size, int memory_size) {
    // constructor
    mem_size = memory_size;
    memory = new int[memory_size];
    for (int i = 0; i < memory_size; ++i) {
        memory[i] = 0;
    }
    cur_cache_size = 0;
    max_cache_size = cache_size;
}

LRUCache::~LRUCache() {
    // destructor
    delete[] memory;
}

int LRUCache::read(int address) {
    // EFFECTS: returns data corresponding to address,
    block* ref = new block;
    ref->address = address;
    ref->data = 0;
    block* np = cache.remove(compare, ref);
    if (np != nullptr) { // if it is nullptr
        block* nnp = new block;
        nnp->address = address;
        nnp->data = np->data;
        cache.insertFront(nnp);
        delete ref;
        delete np;
        return nnp->data;
    }
    else { // if it is not nullptr
        if (cur_cache_size < max_cache_size) {
            block* nnp = new block;
            nnp->address = address;
            nnp->data = memory[address];
            cache.insertFront(nnp);
            cur_cache_size++;
            delete ref;
            delete np;
            return nnp->data;
        }
        else {
            block* nnp = new block;
            nnp->address = address;
            nnp->data = memory[address];
            block* victim = cache.removeBack(); // the last one
            memory[victim->address] = victim->data;
            cache.insertFront(nnp);
            delete ref;
            delete np;
            delete victim;
            return nnp->data;
        }
    }
}

void LRUCache::write(int address, int data) {
    // EFFECTS: writes data to address
    block* ref = new block;
    ref->address = address;
    ref->data = data;
    block* np = cache.remove(compare, ref);
    if (np != nullptr) { // if it is nullptr
        cache.insertFront(ref);
        delete np;
    }
    else { // if not nullptr
        if (cur_cache_size < max_cache_size) {
            cache.insertFront(ref);
            cur_cache_size++;
            delete np;
        }
        else {
            block* victim = cache.removeBack();
            memory[victim->address] = victim->data;
            cache.insertFront(ref);
            delete np;
            delete victim;
        }
    }
}

void LRUCache::printCache() {
    // EFFECTS: prints the cache in given format
    Dlist<block> temp(cache);
    while (!temp.isEmpty()) {
        block* np = temp.removeFront();
        cout << np->address << " " << np->data << endl;
        delete np;
    }
}

void LRUCache::printMem() {
    // EFFECTS: prints the memory in given format
    for (int i = 0; i < mem_size; ++i) {
        cout << memory[i] << " ";
    }
    cout << endl;
}

void read_op(istringstream& nline, int& memorysize, LRUCache* cache);
// EFFECTS: the read operation

void write_op(istringstream& nline, int& memorysize, LRUCache* cache);
// EFFECTS: the write operation

int main() {
    string line;
    int memorysize, cachesize;
    string ins;
    cin >> cachesize >> memorysize;
    getline(cin, line); //get"\n"
    LRUCache cache(cachesize, memorysize);
    while (getline(cin, line)) {
        istringstream nline;
        nline.str(line);
        nline >> ins;
        if (ins == "READ") { //read
            read_op(nline, memorysize, &cache);
        }
        else if (ins == "WRITE") { //write
            write_op(nline, memorysize, &cache);
        }
        else if (ins == "PRINTCACHE") { // printcache
            if (nline >> ins) {
                cout << "ERROR: Too many operands" << endl;
            }
            else {
                cache.printCache();
            }
        }
        else if (ins == "PRINTMEM") { // printmem
            if (nline >> ins) {
                cout << "ERROR: Too many operands" << endl;
            }
            else {
                cache.printMem();
            }
        }
        else if (ins == "EXIT") {  // exit
            return 0;
        }
        else { // unknown
            cout << "ERROR: Unknown instruction" << endl;
        }
    }
    return 0;
}

void read_op(istringstream& nline,int& memorysize, LRUCache* cache) {
    int address;
    string ins;
    if (nline >> address) {
        if (nline >> ins) { // Too many operands
            cout << "ERROR: Too many operands" << endl;
        }
        else {
            if (address >= memorysize || address < 0) {
                cout << "ERROR: Address out of bound" << endl;
            }
            else {
                cout << cache->read(address) << endl;
            }
        }
    }
    else { // not enough 
        cout << "ERROR: Not enough operands" << endl;
    }
}

void write_op(istringstream& nline, int& memorysize, LRUCache* cache) {
    int address, data;
    string ins;
    if (nline >> address) {
        if (nline >> data) {
            if (nline >> ins) { // Too many operands
                cout << "ERROR: Too many operands" << endl;
            }
            else {
                if (address >= memorysize || address < 0) {
                    cout << "ERROR: Address out of bound" << endl;
                }
                else {
                    cache->write(address, data);
                }
            }
        }
        else { // not enough 
            cout << "ERROR: Not enough operands" << endl;
        }
    }
    else { // not enough 
        cout << "ERROR: Not enough operands" << endl;
    }
}
