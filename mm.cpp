#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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
  int num_blocks;
  vector<int> blocks;
};

void readFile(string, vector<process> &);
void printProcess(process &);

int main()
{
  int memory_size, page_size;
  int starting_time = 0;
  //string filename;
  vector<process> plist;
  queue<process> pq;

  cout << "MEMORY SIZE: ";
  cin >> memory_size;

  cout << "\nPAGE SIZE(1: 100, 2: 200, 4: 400): ";
  cin >> page_size;
  page_size *= 100;

  // read in file
  readFile("in1.txt", plist);
  cout << "file read\n";

  // verify the proccess list
  for(int i = 0; i < plist.size(); i++)
  {
    printProcess(plist[i]);
  }

  // fill up the process queue by order of the input file arriva;
  for(int i = 0; i < plist.size(); i++)
  {
    pq.push(plist[i]);
  }

  // start the clock
  while(starting_time != 100000)
  {

    starting_time++;
  }


  return 0;
}

// helper function to read the workload into a vector
void readFile(string input_file, vector<process> &process_list)
{
	ifstream infile;
	infile.open("in1.txt");
	int num_processes;
	process current_proc;
  vector<int> block_sizes;
  int block;

	infile >> num_processes;

	for (int i = 0; i < num_processes; i++)
	{
		infile >> current_proc.pid;
		infile >> current_proc.start_time;
		infile >> current_proc.end_time;
		infile >> current_proc.num_blocks;

		for (int j = 0; j < current_proc.num_blocks; j++)
		{
			infile >> block;
			block_sizes.push_back(block);
		}
		current_proc.blocks = block_sizes;

		process_list.push_back(current_proc);
	}
	infile.close();
}

// helper function to print a process structure
void printProcess(process &p)
{
  cout << "Pid: " << p.pid << endl;
  cout << "Arrival time: " << p.start_time << " End Time: " << p.end_time << endl;
  cout << "# Blocks: " << p.num_blocks << " ";
  for(int i = 0; i < p.num_blocks; i++)
  {
    cout << "Block size " << i << ": " << p.blocks[i] << " ";
  }
  cout << endl;
}
