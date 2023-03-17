
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
using namespace std;

void Setcolor(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

class Node { // For Queue
private:
	int Process_No;
	int Execution_Time;
	Node* next;
public:

	// Contructors
	Node()
	{
		Process_No = -1;
		Execution_Time = -1;
		next = nullptr;
	}
	Node(int Process_No, int Execution_Time)
	{
		this->Process_No = Process_No;
		this->Execution_Time = Execution_Time;
		next = nullptr;
	}

	//Setters
	void Set_Process(int Process_No)
	{
		this->Process_No = Process_No;
	}
	void Set_Execution_Time(int Execution_Time)
	{
		this->Execution_Time = Execution_Time;
	}
	void Set_Next(Node* node)
	{
		this->next = node;
	}

	//Getters
	int Get_Process()
	{
		return Process_No;
	}
	int Get_Execution_Time()
	{
		return Execution_Time;
	}
	Node* Get_Next()
	{
		return next;
	}
};

class P_Node { // For Priority Queue
private:
	int Process_No;
	int Execution_Time;
	int Priority;
	P_Node* next;
public:

	// Contructors
	P_Node()
	{
		Process_No = -1;
		Execution_Time = -1;
		next = nullptr;
		Priority = false;
	}
	P_Node(int Process_No, int Execution_Time, int Priority)
	{
		this->Process_No = Process_No;
		this->Execution_Time = Execution_Time;
		next = nullptr;
		this->Priority=Priority;
	}

	//Setters
	void Set_Process(int Process_No)
	{
		this->Process_No = Process_No;
	}
	void Set_Execution_Time(int Execution_Time)
	{
		this->Execution_Time = Execution_Time;
	}
	void Set_Next(P_Node* node)
	{
		this->next = node;
	}
	void Set_Priority(int Priority)
	{
		this->Priority = Priority;
	}

	//Getters
	int Get_Process()
	{
		return Process_No;
	}
	int Get_Execution_Time()
	{
		return Execution_Time;
	}
	P_Node* Get_Next()
	{
		return next;
	}
	int Get_Priority()
	{
		return Priority;
	}
};


class HeapItem { // For Heap
private:
	int Process_No;
	int Execution_Time;
public:

	// Contructors
	HeapItem()
	{
		Process_No = -1;
		Execution_Time = -1;
	}
	HeapItem(int Process_No, int Execution_Time)
	{
		this->Process_No = Process_No;
		this->Execution_Time = Execution_Time;
	}

	//Setters
	void Set_Process(int Process_No)
	{
		this->Process_No = Process_No;
	}
	void Set_Execution_Time(int Execution_Time)
	{
		this->Execution_Time = Execution_Time;
	}

	//Getters
	int Get_Process()
	{
		return Process_No;
	}
	int Get_Execution_Time()
	{
		return Execution_Time;
	}
};

class MinHeap { // Min Heap (For Shortest Job First Scheduling)
private:
	HeapItem* arr;
	int capacity;
	int total_items;

	void Shift_Up(int index)// for shifting up
	{
		if (index < 1)
			return;

		int parent = (index - 1) / 2;

		if (this->arr[index].Get_Execution_Time() < this->arr[parent].Get_Execution_Time())
			swap(this->arr[index], this->arr[parent]);

		Shift_Up(parent);

	}
	void Shift_Down(int index)// for shifting down
	{
		int min_Index = -1;
		int lChild_Index = index * 2 + 1;
		int rChild_Index = (index * 2) + 2;

		if (lChild_Index < total_items)
		{
			if (arr[index].Get_Execution_Time() > arr[lChild_Index].Get_Execution_Time())
			{
				min_Index = lChild_Index;
			}
		}
		
		if (rChild_Index < total_items)
		{
			if (arr[(min_Index == -1 ? index : min_Index)].Get_Execution_Time() > arr[rChild_Index].Get_Execution_Time())
			{
				min_Index = rChild_Index;
			}
		}

		if (min_Index == -1)
			return;

		swap(arr[index], arr[min_Index]);
		Shift_Down(min_Index);
	}

public:

	//constructors
	MinHeap()
	{
		this->arr = nullptr;
		this->capacity = 0;
		this->total_items = 0;
	}
	MinHeap(int capacity)
	{
		this->arr = new HeapItem[capacity];
		this->capacity = capacity;
		this->total_items = 0;
	}

	void Insert(int Process_No, int Execution_Time)// to insert a node in min Heap
	{

		this->arr[total_items].Set_Process(Process_No);
		this->arr[total_items].Set_Execution_Time(Execution_Time);

		Shift_Up(total_items);
		total_items++;
	}
	void Delete_Min()// to delect the minimum node in min heap
	{
		swap(arr[0], arr[this->total_items - 1]);

		total_items--;
		Shift_Down(0);
	}
	bool is_Empty() // to check weather heap is empty or not
	{
		if (total_items == 0)
			return true;
		else
			return false;
	}
	HeapItem Get_Min()// to get thr minimum item from the min heap
	{
		return this->arr[0];
	}
	void Shortest_Job_First();
};

class Queue { // Queue (For First Come First Serve and Round Robin Scheduling)
private:
	Node* front;
	Node* rear;
public:

	//Constructor
	Queue()
	{
		front = nullptr;
		rear = nullptr;
	}

	void EnQueue(int Process_No, int Execution_Time)// to add an item in a queue
	{
		Node* tem = new Node(Process_No, Execution_Time);

		if (front == nullptr)
		{
			front = tem;
			rear = tem;
		}
		rear->Set_Next(tem);
		rear = tem;
	}
	void DeQueue()// to delete an item from queue
	{

		if (front == rear)
		{
			front = nullptr;
			rear = nullptr;
		}
		else
		{
			Node* tem = front;
			front = front->Get_Next();
			tem = NULL;
		}
	}
	bool IS_EMPTY()// to check wather queue is empty or not
	{
		if (front == nullptr)
			return true;
		else
			return false;
	}
	void First_Come_First_Serve();
	void Round_Robin(int Time_Quantum, int Total);
};

class P_Queue {// Priority Queue (For Prority Scheduling)
private:
	P_Node* front;
	P_Node* rear;
public:

	////Constructor
	P_Queue()
	{
		front = nullptr;
		rear = nullptr;
	}

	void EnQueue(int Process_No, int Execution_Time, int Priority)// to add an item in prority queue
	{
		P_Node* tem = new P_Node(Process_No, Execution_Time, Priority);

		if (front == nullptr)
		{
			front = tem;
			rear = tem;
		}
		rear->Set_Next(tem);
		rear = tem;
	}
	void DeQueue()// to delete an item from prority queue.
	{
		if (front == rear)
		{
			front = nullptr;
			rear = nullptr;
		}
		else
		{
			P_Node* tem = front;
			front = front->Get_Next();
			tem = NULL;
		}
	}
	bool IS_EMPTY()//to check weather prority queue is empty or not
	{
		if (front == nullptr)
			return true;
		else
			return false;
	}
	void Take_Input(int Total)// this function is a helper function. Use to take input in prority scheduling 
	{
		P_Node** arr = new P_Node*[Total];
		int t = 1;
		for (int i = 0; i < Total; i++)
		{
			int exe, pro;
			Setcolor(9);
			cout << "Enter Execution time of process " << i + 1 << " ";
			Setcolor(7);
			cin >> exe;

			Setcolor(9);
			cout << "Enter Priority(should be between 1 and total no of process) of process " << i + 1 << " ";
			Setcolor(7);
			cin >> pro;

			while (pro<0 && pro>Total)
			{
				Setcolor(9);
				cout << "Enter valid Priority(should be between 1 and total no of process) of process " << i + 1 << " ";
				Setcolor(7);
				cin >> pro;
			}

			for (int j = 0; j < i; j++)
			{
				while (pro == arr[j]->Get_Priority())
				{
					Setcolor(9);
					cout << "Enter unique valid Priority(should be between 1 and total no of process) of process " << i + 1 << " ";
					Setcolor(7);
					cin >> pro;
					j = 0;
				}
			}

			P_Node* tem = new P_Node(i + 1, exe, pro);
			arr[i] = tem;
			system("cls");
		}
		
		while (t <=Total)
		{
			for (int i = 0; i < Total; i++)
			{
				P_Node* tem = arr[i];
				if (tem->Get_Priority() == t)
				{
					this->EnQueue(tem->Get_Process(), tem->Get_Execution_Time(), tem->Get_Priority());
				}
			}
			t++;
		}
	}
	void Priority_Scheduling();

};

void Queue::First_Come_First_Serve()// this scheduling algorithm takes all the processes and execute the on the basis of "First Come".. the process that comes first is exected first..
{
	clock_t t1, t2, t3;
	Setcolor(7);
	cout << "                                              Algorithm: First Come First Serve..! " << endl;
	while (!IS_EMPTY())
	{	
		t1 = clock();

		Setcolor(3);
		cout << "Executing Process No: ";
		Setcolor(7);
		cout<<front->Get_Process() << "..!!" << endl;

		int x = front->Get_Execution_Time();
		Sleep(x * 100);

		Setcolor(11);
		cout << "Process No: ";
		Setcolor(7);
		cout << front->Get_Process();
		Setcolor(11);
		cout<< " has finished execution..!!" << endl;
		t2 = clock();

		Setcolor(6);
		cout << "Arrival Time: ";
		Setcolor(14);
		cout << ((float)t1 / CLOCKS_PER_SEC) * 10 << endl;

		Setcolor(6);
		cout << "Departure Time: ";
		Setcolor(14);
		cout<< ((float)t2 / CLOCKS_PER_SEC) * 10 << endl;

		t3 = t2 - t1;
		Setcolor(6);
		cout << "Total Time Taken for Execution: ";
		Setcolor(14);
		cout<< ((float)t3 / CLOCKS_PER_SEC)*10 << endl;
		this->DeQueue();

		cout << endl;

		if (IS_EMPTY())
		{
			Setcolor(4);
			cout << "All the processes has been Executed..!!" << endl<<endl;
		}
	}
}

void Queue::Round_Robin(int Time_Quantum,int Total) // this scheduling algorithm takes all the processes and time quantum.. and then executes them using "Round Robin" Algorithm.. each task is givene equal execution time which is time quantum until that process is finished..
{
	int x = 0;
	clock_t t1, t2, t3, * tem;
	tem = new clock_t[Total];
	Setcolor(7);
	cout << "                                              Algorithm: Round Robin..! " << endl;
	while (!IS_EMPTY())
	{
		t1 = clock();
		if (x < Total)
		{
			tem[x] = t1;
			x++;
		}

		Setcolor(3);
		cout << "Executing Process No: ";
		Setcolor(7);
		cout << front->Get_Process() << "..!!" << endl;

		Sleep(Time_Quantum * 100);
		int a = front->Get_Execution_Time();
		a = a - Time_Quantum;
		if (a > 0)
		{
			Setcolor(13);
			front->Set_Execution_Time(a);
			cout << "Remaining Process Execution of Process " << front->Get_Process() << " is ";
			Setcolor(7);
			cout << front->Get_Execution_Time() << ".." << endl;
			Setcolor(13);
			cout << "Time Quantum: " ;
			Setcolor(7);
			cout<< Time_Quantum << endl;

			int b = front->Get_Process();
			this->DeQueue();
			this->EnQueue(b,a);
		}
		else
		{
			t2 = clock();
			t3 = t2 - tem[(front->Get_Process()) - 1];

			Setcolor(11);
			cout << "Process No: ";
			Setcolor(7);
			cout << front->Get_Process();
			Setcolor(11);
			cout << " has finished execution..!!" << endl;

			Setcolor(6);
			cout << "Arrival Time: ";
			Setcolor(14);
			cout << ((float)tem[(front->Get_Process()) - 1] / CLOCKS_PER_SEC) * 10 << endl;

			Setcolor(6);
			cout << "Departure Time: ";
			Setcolor(14);
			cout << ((float)t2 / CLOCKS_PER_SEC) * 10 << endl;

			Setcolor(6);
			cout << "Total Time Taken for Execution: ";
			Setcolor(14);
			cout << ((float)t3 / CLOCKS_PER_SEC) * 10 << endl;

			this->DeQueue();
		}
		cout << endl<<endl;
	}
}

void MinHeap::Shortest_Job_First() // this scheduling algorithm takes all the processes and execute the on the basis of "Shortest Process First"..the process that has least execution time is executed first..
{
	clock_t t1, t2, t3;
	Setcolor(7);
	cout << "                                              Algorithm: Shortest Job First..! " << endl;
	while (!is_Empty())
	{
		t1 = clock();

		Setcolor(3);
		cout << "Executing Process No: ";
		Setcolor(7);
		cout << arr[0].Get_Process() << "..!!" << endl;

		int x = arr[0].Get_Execution_Time();
		Sleep(x * 100);

		Setcolor(11);
		cout << "Process No: ";
		Setcolor(7);
		cout << arr[0].Get_Process();
		Setcolor(11);
		cout << " has finished execution..!!" << endl;
		t2 = clock();

		Setcolor(6);
		cout << "Arrival Time: ";
		Setcolor(14);
		cout << ((float)t1 / CLOCKS_PER_SEC) * 10 << endl;

		Setcolor(6);
		cout << "Departure Time: ";
		Setcolor(14);
		cout << ((float)t2 / CLOCKS_PER_SEC) * 10 << endl;

		t3 = t2 - t1;
		Setcolor(6);
		cout << "Total Time Taken for Execution: ";
		Setcolor(14);
		cout << ((float)t3 / CLOCKS_PER_SEC) * 10 << endl;

		this->Delete_Min();
		cout << endl;

		if (is_Empty())
		{
			Setcolor(4);
			cout << "All the processes has been Executed..!!" << endl;
		}
	}
}

void P_Queue::Priority_Scheduling() // this scheduling algorithm takes all the processes and execute the on the basis of "Priority"..the process that has highest priority is exected first..
{

	clock_t t1, t2, t3;
	cout << "                                              Algorithm: Priority Scheduling..! " << endl;
	while (!IS_EMPTY())
	{
		t1 = clock();

		Setcolor(3);
		cout << "Executing Process No: ";
		Setcolor(7);
		cout << front->Get_Process() << "..!!" << endl;

		Setcolor(13);
		cout << "Priority: ";
		Setcolor(7);
		cout<< front->Get_Priority() << "..!" << endl;

		int x = front->Get_Execution_Time();
		Sleep(x * 100);

		Setcolor(11);
		cout << "Process No: ";
		Setcolor(7);
		cout << front->Get_Process();
		Setcolor(11);
		cout << " has finished execution..!!" << endl;
		
		t2 = clock();

		Setcolor(6);
		cout << "Arrival Time: ";
		Setcolor(14);
		cout << ((float)t1 / CLOCKS_PER_SEC) * 10 << endl;

		Setcolor(6);
		cout << "Departure Time: ";
		Setcolor(14);
		cout << ((float)t2 / CLOCKS_PER_SEC) * 10 << endl;

		t3 = t2 - t1;
		Setcolor(6);
		cout << "Total Time Taken for Execution: ";
		Setcolor(14);
		cout << ((float)t3 / CLOCKS_PER_SEC) * 10 << endl;

		this->DeQueue();
		cout << endl;

		if (IS_EMPTY())
		{
			Setcolor(4);
			cout << "All the processes has been Executed..!!" << endl;
		}
	}
}

void M_Menu()// just a helper function
{
	Setcolor(12);
	cout << "Enter 'M'to go to Main Menu. " << endl
		<< "Enter 'Q' to Quit. "<<endl
		<< "Please Enter your choice ";
	Setcolor(7);
}

void M_Choice()// just a helper function for main menu
{
	Setcolor(7);
	cout << "                                                   CPU SCHEDULER..!" << endl;

	Setcolor(12);
	cout << "Please select Scheduling Strategy. " << endl
		<< "Enter 'F' for First Come First Serve. " << endl
		<< "Enter 'S' for Shortest Job First. " << endl
		<< "Enter 'R' for Round Robin. " << endl
		<< "Enter 'P' for Priority Scheduling. " << endl
		<< "Enter 'Q' to Quit. " << endl
		<< "Please Enter your choice ";
	Setcolor(7);
}

int main()
{
	char Main_Choice;
	M_Choice();
	cin >> Main_Choice;

	// the code below is for Main Menu 
	while (Main_Choice != 'Q' && Main_Choice != 'Y')
	{
		if (Main_Choice == 'F')
		{
			Queue FCFS;
			system("cls");
			int total;
			Setcolor(8);
			cout << "Please Enter total number of processes ";
			Setcolor(7);
			cin >> total;
			system("cls");

			for (int i = 0; i < total; i++)
			{
				int tim;
				Setcolor(9);
				cout << "Please Enter Execution time of process " << i + 1<<" ";
				Setcolor(7);
				cin >> tim;
				FCFS.EnQueue(i + 1, tim);
			}

			Setcolor(8);
			cout << endl << "All the processes has been taken..!!" << endl;
			Sleep(1000);

			system("cls");
			FCFS.First_Come_First_Serve();

			M_Menu();
			cin >> Main_Choice;
			if (Main_Choice == 'M')
			{
				system("cls");
				M_Choice();
				cin >> Main_Choice;
			}
		}
		else if (Main_Choice == 'S')
		{
			system("cls");
			int total;
			Setcolor(8);
			cout << "Please Enter total number of processes ";
			Setcolor(7);
			cin >> total;
			MinHeap SJF(total);
			system("cls");

			for (int i = 0; i < total; i++)
			{
				int tim;
				Setcolor(9);
				cout << "Please Enter Execution time of process " << i + 1 << " ";
				Setcolor(7);
				cin >> tim;
				SJF.Insert(i + 1, tim);
			}

			Setcolor(8);
			cout << endl << "All the processes has been taken..!!" << endl;
			Sleep(1000);


			system("cls");
			SJF.Shortest_Job_First();

			M_Menu();
			cin >> Main_Choice;
			if (Main_Choice == 'M')
			{
				system("cls");
				M_Choice();
				cin >> Main_Choice;
			}
		}
		else if (Main_Choice == 'R')
		{
			Queue RR;
			system("cls");
			int total,time;
			Setcolor(8);
			cout << "Please Enter total number of processes ";
			Setcolor(7);
			cin >> total;
			Setcolor(8);
			cout << "Please Enter Time Quantum ";
			Setcolor(7);
			cin >> time;

			system("cls");
			for (int i = 0; i < total; i++)
			{
				int tim;
				Setcolor(9);
				cout << "Please Enter Execution time of process " << i + 1 << " ";
				Setcolor(7);
				cin >> tim;
				RR.EnQueue(i + 1, tim);
			}

			Setcolor(8);
			cout << endl << "All the processes has been taken..!!" << endl;
			Sleep(1000);

			system("cls");
			RR.Round_Robin(time,total);

			M_Menu();
			cin >> Main_Choice;
			if (Main_Choice == 'M')
			{
				system("cls");
				M_Choice();
				cin >> Main_Choice;
			}
		}
		else if (Main_Choice == 'P')
		{
			P_Queue PS;
			system("cls");
			int total;
			Setcolor(8);
			cout << "Please Enter total number of processes ";
			Setcolor(7);
			cin >> total;
			system("cls");
			PS.Take_Input(total);

			Setcolor(8);
			cout << endl << "All the processes has been taken..!!" << endl;
			Sleep(1000);
			
			system("cls");
			PS.Priority_Scheduling();

			M_Menu();
			cin >> Main_Choice;
			if (Main_Choice == 'M')
			{
				system("cls");
				M_Choice();
				cin >> Main_Choice;
			}
		}
		if (Main_Choice == 'Q')
		{
			system("CLS");
			Setcolor(12);

			cout << "Do you really want to Quit.?" << endl
				<< "(Press 'Y' for Yes and 'N' for No)" << endl;

			Setcolor(7);
			cin >> Main_Choice;

			if (Main_Choice == 'N')
			{
				system("CLS");
				M_Choice();
				Setcolor(7);
				cin >> Main_Choice;
			}
		}
	}
	system("pause");
	return 0;
}
