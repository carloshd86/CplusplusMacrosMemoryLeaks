#ifndef _MEMORY_LEAKS_MONITOR_H_
#define _MEMORY_LEAKS_MONITOR_H_

#include <Windows.h>

struct MemoryRequestLog {
	unsigned int memory_address;
	unsigned int size;
	char file[_MAX_PATH];
	int line;
	MemoryRequestLog * next;
};

void AddMemoryRequest(unsigned int memory_address, unsigned int size, const char * file, int line);
void RemoveMemoryRequest(unsigned int address);
void PrintMemoryLeaks();

#ifdef MEMORY_LEAKS_MONITOR

inline void * operator new(unsigned int size, const char * file, int line)
{
	void * memory_address = malloc(size);
	AddMemoryRequest(reinterpret_cast<unsigned int>(memory_address), size, file, line);
	return(memory_address);
}

inline void operator delete(void * memory_address)
{
	RemoveMemoryRequest(reinterpret_cast<unsigned int>(memory_address));
	free(memory_address);
}

inline void * operator new[](unsigned int size, const char * file, int line)
{
	void * memory_address = malloc(size);
	AddMemoryRequest(reinterpret_cast<unsigned int>(memory_address), size, file, line);
	return(memory_address);
}

inline void operator delete[](void * memory_address)
{
	RemoveMemoryRequest(reinterpret_cast<unsigned int>(memory_address));
	free(memory_address);
}

#define NEW(type) new(__FILE__, __LINE__) type()
#define NEW_ARRAY(type, number) new(__FILE__, __LINE__) type[number]
#define DELETE(obj) delete obj
#define DELETE_ARRAY(arr) delete[]arr

#else
	#define NEW(type) new type()
	#define NEW_ARRAY(type, number) new type[number]
	#define DELETE(obj) delete obj
	#define DELETE_ARRAY(arr) delete[]arr
#endif 

#endif