#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include "mm.h"

using namespace std;

void readFile(string, vector<process> &);
//void allocatePages(vector<block> &, int &, int &);
void printInputQ(queue<process> &);
void memory_manager(vector<block> &, queue<process> &, int &, int &, int &);
//void sumBlocks(process &, int &);
//void adjust_memory(vector<block> &, int &);

int main()
{
  int memory_size, page_size;
  int virtual_clock = 0;
  vector<process> plist;
  queue<process> input_q;
  vector<block> memory_map;

  cout << "MEMORY SIZE: ";
  cin >> memory_size;

  cout << "\nPAGE SIZE(1: 100, 2: 200, 4: 400): ";
  cin >> page_size;
  page_size *= 100;

  // allocate memory
  allocatePages(memory_map, memory_size, page_size);

  // read in file
  readFile("in1.txt", plist);
  cout << "file read\n";

  // verify the proccess list
  for(int i = 0; i < plist.size(); i++)
  {
    printProcess(plist[i]);
  }
  cout << endl;


  // start the clock
  while(virtual_clock != 100000)
  {
    // check for old processes to remove from memory
    for(int i = 0; i < plist.size(); i++)
    {
      if(plist[i].term_time == virtual_clock)
      {
        cout << "t = " << virtual_clock << " Process " << i+1 << " completes" << endl;
        adjust_memory(memory_map, i);
        printMemoryMap(memory_map);
      }
    }


    // check for new processes to add to the input queue
    for(int i = 0; i < plist.size(); i++)
    {
      // add the arriving process to the input queue
      if(plist[i].start_time == virtual_clock)
      {
        input_q.push(plist[i]);
        cout << "t = " << virtual_clock << " Process " << (i+1) << " arrives" << endl;
        //printProcess(plist[i]);
        int sum = 0;
        sumBlocks(plist[i], sum);
        cout << "space req's: " << sum << endl;
        printInputQ(input_q);
        //printMemoryMap(memory_map);
      }
    }

    // check for free memory to add a process to
    for(int i = 0; i < input_q.size(); i++)
    {
      memory_manager(memory_map, input_q, memory_size, page_size, virtual_clock);
    }



    // increment the virtual clock
    virtual_clock++;
  }

  //system("PAUSE");
  return 0;
}

void memory_manager(vector<block> &mmap, queue<process> &pq, int &m_size, int &p_size, int& current_time)
{
  // get the process at the head of the Queue
  process current_proc = pq.front();
  int space_req = 0;
  //int space_req = sumBlocks(current_proc);
  sumBlocks(current_proc, space_req);
  bool space_found = false;
  int contiguous_space = 0;

  // search for free space in memory
  for(int i = 0; i < mmap.size(); i++)
  {
    // if the current block is free, add it to the contiguous_space
    if(!mmap[i].in_use)
    {
      contiguous_space+=p_size;
    }
    else
    {
      // if this current block is in use, end the contiguous block
      contiguous_space = 0;
    }

    // if our block is big enough, add the head of the input queue to it
    if(contiguous_space >= space_req)
    {
      space_found = true;
      break;
    }
  }

  // if we found space, add the head of the queue to the memory block;
  if(space_found)
  {
    cout << "\tMM moves process " << current_proc.pid << " to memory" << endl;
    // calculate end time
    current_proc.term_time = current_time + current_proc.end_time;
    cout << "Term time: " << current_proc.term_time << endl;

    int page_count = 1;
    for(int i = 0; i < mmap.size(); i++)
    {

      if(!mmap[i].in_use)
      {
        mmap[i].current_process = current_proc.pid;
        mmap[i].in_use = true;
        mmap[i].number = page_count;
        page_count++;

        space_req -= p_size;
        if(space_req <= 0)
        {
          break;
        }
      }

    }
    // update the input Queue if we added a process to memory
    pq.pop();

    // print the memory Map and updated queue
    printInputQ(pq);
    printMemoryMap(mmap);
  }
}

// helper function to read the workload into a vector
void readFile(string input_file, vector<process> &process_list)
{
	ifstream infile;
	infile.open("in1.txt");
	int num_processes;
	process current_proc;
  int block;

	infile >> num_processes;

	for (int i = 0; i < num_processes; ++i)
	{
		infile >> current_proc.pid;
		infile >> current_proc.start_time;
		infile >> current_proc.end_time;
		infile >> current_proc.num_blocks;

    vector<int> temp_blocks;
		for (int j = 0; j < current_proc.num_blocks; ++j)
		{
			infile >> block;
      cout << "block: " << block << endl;
      temp_blocks.push_back(block);
		}
    current_proc.term_time = -1;
    current_proc.block_sizes = temp_blocks;
		process_list.push_back(current_proc);
	}
	infile.close();
}

// helper function to print the input queue
void printInputQ(queue<process> &pq)
{
  // copy the input queue to print it correcty
  queue<process> temp = pq;
  cout << "\tInput Queue: [";
  while(!temp.empty())
  {
    process ptemp = temp.front();
    cout << ptemp.pid << " ";
    temp.pop();
  }
  cout << "]" << endl;
}
