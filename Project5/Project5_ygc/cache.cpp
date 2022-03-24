#include "dlist.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>

using namespace std;

struct block {
	int address; // its address in memory
	int data;
};

class Address_out_bound {};
class Unkown_instruction{};
class Not_enough_operands{};
class Too_many_operands{};

class LRUCache {
private:
	int mem_size; // size of memory
	int* memory;
	Dlist<block> cache;
	int cur_cache_size; // current length of `cache`
	int max_cache_size; // maximum length of `cache`
	static bool compare(const block* a, const block* b);
	// EFFECTS: returns true if two blocks have the same address
public:
	LRUCache(int cache_size, int memory_size); // constructor
	// Initialize `cur_cache_size`, `max_cache_size`, `memory`
	// Initialize all elements in `memory` to 0
	~LRUCache(); // destructor
	int read(int address);
	// EFFECTS: returns data corresponding to address,
	// 0 <= address < mem_size;
	// if address is out of bound, throws an exception
	//
	// if hit,
	// removes this block and insert it to the front;
	// returns `data`;
	// if miss,
	// if `cur_cache_size` equals to `max_cache_size`,
	// removes the last (least recently used) block
	// in the `cache`;
	// writes data in the last block
	// to the corresponding address in `memory`;
	// if `cur_cache_size` < `max_cache_size`,
	// increment `cur_cache_size` by 1;
	// reads `data` of `address` from `memory`,
	// inserts the block with `address` and `data`
	// to the front of `cache`;
	// returns `data`
	void write(int address, int data);
	// EFFECTS: writes data to address, 0 <= address < mem_size
	// if address is out of bound, throws an exception
	//
	// if hit,
	// removes this block from list,
	// writes `data` to this block,
	// and inserts this block to the front;
	// if miss,
	// if `cur_cache_size` equals to `max_cache_size`,
	// removes the last (least recently used) block
	// in the `cache`;
	// writes data in the last block
	// to the corresponding address in `memory`;
	// if `cur_cache_size` < `max_cache_size`,
	// increment `cur_cache_size` by 1;
	// inserts the block with `address` and `data`
	// to the front of `cache`
	void printCache();
	// EFFECTS: prints the cache in given format
	void printMem();
	// EFFECTS: prints the memory in given format
	block* hit_remove(int address);
	// EFFECTS: return the block if there exists a block with address equal to address, otherwise return nullptr
};

LRUCache::LRUCache(int cache_size, int memory_size): mem_size(memory_size), cur_cache_size(0), max_cache_size(cache_size)  {
	memory = new int[mem_size];
	for (int i = 0; i < mem_size; i++) {
		memory[i] = 0;
	}
}

LRUCache::~LRUCache() {
	delete[] memory;
}

bool LRUCache::compare(const block* a, const block* b) {
	return a->address == b->address;
}

block* LRUCache::hit_remove(int address) {
	block *temp_address = new block;
	temp_address->address = address;
	temp_address->data = 0;
	block* mem_data = cache.remove(compare, temp_address);
	delete temp_address;
	return mem_data;
}

int LRUCache::read(int address) {
	if (address >= mem_size) {
		Address_out_bound err;
		throw err;
	}
	block* mem_data = hit_remove(address);
	if (mem_data == nullptr) {
		if (cur_cache_size == max_cache_size) {
			mem_data = cache.removeBack();
			memory[mem_data->address] = mem_data->data;
			delete mem_data;
		}
		else {
			cur_cache_size++;
		}
		block* read_memory = new block;
		read_memory->address = address;
		read_memory->data = memory[address];
		cache.insertFront(read_memory);
		return read_memory->data;
	}
	else {
		cache.insertFront(mem_data);
		return mem_data->data;
	}
}

void LRUCache::write(int address, int data) {
	if (address >= mem_size) {
		Address_out_bound err;
		throw err;
	}
	block* mem_data = hit_remove(address);
	if (mem_data == nullptr) {
		if (cur_cache_size == max_cache_size) {
			mem_data = cache.removeBack();
			memory[mem_data->address] = mem_data->data;
			delete mem_data;
		}
		else {
			cur_cache_size++;
		}
		block* write_memory = new block;
		write_memory->address = address;
		write_memory->data = data;
		cache.insertFront(write_memory);
	}
	else {
		mem_data->data = data;
		cache.insertFront(mem_data);
	}
}


void LRUCache::printCache() {
	for (int i = 0; i < cur_cache_size; i++) {
		block* temp = cache.removeFront();
		cout << temp->address << " " << temp->data << endl;
		cache.insertBack(temp);
	}
}

void LRUCache::printMem() {
	for (int i = 0; i < mem_size - 1; i++) {
		cout << memory[i] << " ";
	}
	cout << memory[mem_size - 1] << endl;

}

void Read_command(istringstream &cin_Stream, LRUCache &Cache) {
	// MODIFIES: this
	// EFFECTS: implement read command
	int address;
	cin_Stream.get();
	if (!cin_Stream) {
		Not_enough_operands err;
		throw err;
	}
	cin_Stream >> address;
	cin_Stream.get();
	if (cin_Stream) {
		Too_many_operands err;
		throw err;
	}
	int data = Cache.read(address);
	cout << data << endl;
}

void Write_command(istringstream& cin_Stream, LRUCache& Cache) {
	// MODIFIES: this
	// EFFECTS: implement write command
	int address;
	int data;
	cin_Stream.get();
	if (!cin_Stream) {
		Not_enough_operands err;
		throw err;
	}
	cin_Stream >> address;
	cin_Stream.get();
	if (!cin_Stream) {
		Not_enough_operands err;
		throw err;
	}
	cin_Stream >> data;
	cin_Stream.get();
	if (cin_Stream) {
		Too_many_operands err;
		throw err;
	}
	Cache.write(address, data);
}


int main(int argc, char* argv[]) {
	int cache_size;
	int memory_size;
	cin >> cache_size >> memory_size;
	LRUCache Cache(cache_size, memory_size);
	string line;
	string command;
	cin >> command;
	while (command != "EXIT") {
		try {
			getline(cin, line);
			istringstream cin_Stream(line);
			if (command == "READ") {
				Read_command(cin_Stream, Cache);
			}
			else if (command == "WRITE") {
				Write_command(cin_Stream, Cache);
			}
			else if (command == "PRINTCACHE") {
				Cache.printCache();
			}
			else if (command == "PRINTMEM") {
				Cache.printMem();
			}
			else {
				Unkown_instruction err;
				throw err;
			}
		}
		catch (Unkown_instruction err) {
			cout << "ERROR: Unknown instruction" << endl;
		}
		catch (Address_out_bound err) {
			cout << "ERROR: Address out of bound" << endl;
		}
		catch (Too_many_operands err) {
			cout << "ERROR: Too many operands" << endl;
		}
		catch (Not_enough_operands err) {
			cout << "ERROR: Not enough operands" << endl;
		}
		cin >> command;
	}
}