#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct process
{
  int pid;
  int start_time;
  int end_time;
  int term_time;
  int turnaround_time;
  int num_blocks;
  vector<int> block_sizes;
};

struct block
{
  int number;
  int base;
  int limit;
  int current_process;
  bool in_use;
};

// helper function to print a process structure
void printProcess(process &p)
{
  cout << "Pid: " << p.pid << endl;
  cout << "Arrival time: " << p.start_time << " End Time: " << p.end_time << endl;
  cout << "# Blocks: " << p.num_blocks << " ";
  for(int i = 0; i < p.num_blocks; i++)
  {
    cout << "Block size " << i << ": " << p.block_sizes[i] << " ";
  }
  cout << endl;

  cout << "Term time: " << p.term_time << endl;
}

void sumBlocks(process &p, int &sum)
{
  sum = 0;
  for(int i = 0; i < p.num_blocks; i++)
  {
    sum += p.block_sizes[i];
  }
}

// helper function to print the memory map
void printMemoryMap(vector<block> &mmap)
{
  cout << "\tMemory Map: ";
  for(int i = 0; i < mmap.size(); i++)
  {
    if(i != 0)
    {
      cout << "\t\t";
    }
    cout << mmap[i].base << "-" << mmap[i].limit;
    if(mmap[i].current_process == 0)
    {
      cout << " Free";
    }
    else
    {
      cout << " Process " << mmap[i].current_process;
    }
    cout << ", Page " << mmap[i].number << endl;
  }
}

// helper function to divide the memory chunk into pages
void allocatePages(vector<block> &mmap, int &m_size, int &p_size)
{
  int n = m_size/p_size;

  for(int i = 0; i < n; i++)
  {
    block current_block;
    current_block.number = i+ 1;
    current_block.base = i * p_size;
    current_block.limit = (i+1) * p_size - 1;
    current_block.current_process = 0;
    current_block.in_use = false;
    mmap.push_back(current_block);
  }
}

// helper function to remove a process from memory
void adjust_memory(vector<block> &mmap, int &pnum)
{
  for(int i = 0; i < mmap.size(); ++i)
  {
    if(mmap[i].current_process == pnum)
    {
      mmap[i].current_process = 0;
      mmap[i].in_use = false;
      mmap[i].number = i+1;
    }
  }
}
