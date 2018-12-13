#include "stdafx.h"

#include "MemoryLeaksMonitor.h"

MemoryRequestLog * g_memory_request_log = nullptr;

void AddMemoryRequest(unsigned int memory_address, unsigned int size, const char * file, int line)
{
	MemoryRequestLog * memory_log = reinterpret_cast<MemoryRequestLog *>(malloc(sizeof(MemoryRequestLog)));
	
	memory_log->memory_address = memory_address;
	memory_log->size = size;
	strncpy(memory_log->file, file, _MAX_PATH-1);
	memory_log->line = line;
	memory_log->next = g_memory_request_log;
	g_memory_request_log = memory_log;
}

void RemoveMemoryRequest(unsigned int address)
{
	MemoryRequestLog * memory_log_to_free = g_memory_request_log;
	MemoryRequestLog * memory_log_prev = nullptr;
	while(memory_log_to_free && (address != memory_log_to_free->memory_address))
	{
		memory_log_prev = memory_log_to_free;
		memory_log_to_free = memory_log_to_free->next;
	}
	
	if (memory_log_to_free)
	{
		if (memory_log_prev)
			memory_log_prev->next = memory_log_to_free->next;

		if (memory_log_to_free == g_memory_request_log)
			g_memory_request_log = g_memory_request_log->next;

		free(memory_log_to_free);
		memory_log_to_free = nullptr;
	}
}

void PrintMemoryLeaks()
{
	unsigned long total_size = 0;
	char buf[1024];

	if(!g_memory_request_log)
		return;

	MemoryRequestLog * memory_leaked = g_memory_request_log;
	while (memory_leaked)
	{
		sprintf(buf, "%s(%d): ADDRESS %d\t%d unfreed\n", memory_leaked->file, memory_leaked->line, memory_leaked->memory_address, memory_leaked->size);
		OutputDebugStringA(buf);
		total_size += memory_leaked->size;
		memory_leaked = memory_leaked->next;
	}
	sprintf(buf, "-----------------------------------------------------------\n");
	OutputDebugStringA(buf);
	sprintf(buf, "Total Unfreed: %lu bytes\n", total_size);
	OutputDebugStringA(buf);
}