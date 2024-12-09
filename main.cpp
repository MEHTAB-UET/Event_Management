#include <iostream>
#include <string>
using namespace std;

class Event
{
public:
    string name;
    string date;

    Event() : name(""), date("") {}
    Event(string n, string d) : name(n), date(d) {}
};

class Attendee
{
public:
    string name;

    Attendee() : name("") {}
    Attendee(string n) : name(n) {}
};

class Resource
{
public:
    string name;

    Resource(string n) : name(n) {}
};

class Location
{
public:
    string name;

    Location(string n) : name(n) {}
};

// Custom Stack for undo/redo functionality
class Stack
{
private:
    Event *stack;
    int top;
    int capacity;

public:
    Stack(int size) : capacity(size), top(-1)
    {
        stack = new Event[capacity];
    }

    ~Stack()
    {
        delete[] stack;
    }

    void push(Event event)
    {
        if (top < capacity - 1)
        {
            stack[++top] = event;
        }
        else
        {
            cout << "Stack overflow" << endl;
        }
    }

    Event pop()
    {
        if (top >= 0)
        {
            return stack[top--];
        }
        return Event("", "");
    }

    bool isEmpty()
    {
        return top == -1;
    }
};

// Custom Queue for attendee management
class Queue
{
private:
    Attendee *queue;
    int front;
    int rear;
    int capacity;

public:
    Queue(int size) : capacity(size), front(0), rear(0)
    {
        queue = new Attendee[capacity];
    }

    ~Queue()
    {
        delete[] queue;
    }

    void enqueue(Attendee attendee)
    {
        if (rear < capacity)
        {
            queue[rear++] = attendee;
        }
        else
        {
            cout << "Queue overflow" << endl;
        }
    }

    Attendee dequeue()
    {
        if (!isEmpty())
        {
            return queue[front++];
        }
        return Attendee("");
    }

    bool isEmpty()
    {
        return front == rear;
    }
};

// Binary Search Tree for event management
class TreeNode
{
public:
    Event event;
    TreeNode *left;
    TreeNode *right;

    TreeNode(Event e) : event(e), left(nullptr), right(nullptr) {}
};

class BST
{
private:
    TreeNode *root;

    void insert(TreeNode *&node, Event event)
    {
        if (node == nullptr)
        {
            node = new TreeNode(event);
        }
        else if (event.date < node->event.date)
        {
            insert(node->left, event);
        }
        else
        {
            insert(node->right, event);
        }
    }

    TreeNode *search(TreeNode *node, string date)
    {
        if (node == nullptr || node->event.date == date)
        {
            return node;
        }
        else if (date < node->event.date)
        {
            return search(node->left, date);
        }
        else
        {
            return search(node->right, date);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(Event event)
    {
        insert(root, event);
    }

    Event search(string date)
    {
        TreeNode *node = search(root, date);
        if (node != nullptr)
        {
            return node->event;
        }
        return Event("", "");
    }
};

// Graph for resource management
class Graph
{
private:
    string **adjList;
    int *adjListSize;
    int capacity;

public:
    Graph(int size) : capacity(size)
    {
        adjList = new string *[capacity];
        adjListSize = new int[capacity];
        for (int i = 0; i < capacity; ++i)
        {
            adjList[i] = new string[10]; // Assuming max 10 neighbors for simplicity
            adjListSize[i] = 0;
        }
    }

    ~Graph()
    {
        for (int i = 0; i < capacity; ++i)
        {
            delete[] adjList[i];
        }
        delete[] adjList;
        delete[] adjListSize;
    }

    void addEdge(string u, string v)
    {
        int uIndex = hashFunction(u);
        adjList[uIndex][adjListSize[uIndex]++] = v;
    }

    string *getNeighbors(string u)
    {
        int uIndex = hashFunction(u);
        return adjList[uIndex];
    }

    int getNeighborCount(string u)
    {
        int uIndex = hashFunction(u);
        return adjListSize[uIndex];
    }

    int hashFunction(string key)
    {
        int hash = 0;
        for (char c : key)
        {
            hash = (hash * 31 + c) % capacity;
        }
        return hash;
    }
};

// Sorting algorithms
void quicksort(Event *events, int left, int right)
{
    if (left < right)
    {
        int pivotIndex = left + (right - left) / 2;
        Event pivot = events[pivotIndex];
        int i = left, j = right;
        while (i <= j)
        {
            while (events[i].date < pivot.date)
                i++;
            while (events[j].date > pivot.date)
                j--;
            if (i <= j)
            {
                swap(events[i], events[j]);
                i++;
                j--;
            }
        }
        quicksort(events, left, j);
        quicksort(events, i, right);
    }
}
void merge(Event *events, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Event *L = new Event[n1];
    Event *R = new Event[n2];
    for (int i = 0; i < n1; i++)
        L[i] = events[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = events[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].date <= R[j].date)
        {
            events[k] = L[i];
            i++;
        }
        else
        {
            events[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        events[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        events[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

// Example usage

void mergesort(Event *events, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergesort(events, left, mid);
        mergesort(events, mid + 1, right);
        merge(events, left, mid, right);
    }
}

int main()
{
    // Create events
    Event event1("Conference", "2023-10-01");
    Event event2("Concert", "2023-11-15");
    Event event3("Workshop", "2023-09-20");

    // Insert events into BST
    BST bst;
    bst.insert(event1);
    bst.insert(event2);
    bst.insert(event3);

    // Search for an event
    Event foundEvent = bst.search("2023-11-15");
    if (foundEvent.name != "")
    {
        cout << "Event found: " << foundEvent.name << " on " << foundEvent.date << endl;
    }

    // Sort events by date
    Event events[] = {event1, event2, event3};
    quicksort(events, 0, 2);
    cout << "Sorted events by date:" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << events[i].name << " on " << events[i].date << endl;
    }

    return 0;
}