//
//  main.cpp
//  QueueLinkList
//
//  Created by Kevin Liu on 2024-02-02.
//
#include <iostream>
#include <vector>
#include <iterator>

template <class T>
class Queue
{
private:
    
    // state
    struct Node
    {
        T data;
        Node *next;
        Node *previous;
        
        // parameterized constructor
        Node(const T &data = T{}, Node *next = nullptr, Node *previous = nullptr):
        data(data), next(next), previous(previous)
        {}
    };
    
    // initial and final state pointers
    Node *ptr_front;
    Node *ptr_back;;
    
    // determines the max size for the container
    int counter = 0;
    
    
public:
    
    // default constructor for the frontier
    Queue()
    {
        ptr_front = nullptr;
        ptr_back = nullptr;
    }
    
    // checks the container
    bool is_empty()
    {
        return !ptr_front && !ptr_back;;
    }
    
    // max size is set to 5
    bool is_full()
    {
        return counter == 5;
    }
    
    // returns the front data, error checking
    T front()
    {
        if(is_empty())
        {
            throw std::underflow_error("Queue is empty!\n\n");
        }
        
        return ptr_front->data;
    }
    
    // FIFO insertion
    bool enqueue(const T &data)
    {
        bool flag = false;
        
        // checks against the max list size, error checking
        if(is_full())
        {
            throw std::overflow_error("Queue is full!\n\n");
        }
                                //data, next,    previous
        Node *node_new = new Node(data, nullptr, ptr_back);
        
        if(is_empty())
        {
            ptr_front = node_new;
        }
        else
        {
            ptr_back->next = node_new;
        }

        ptr_back = node_new;
        flag = true;
        counter++;
        
        return flag;
    }
    
    // FIFO deletion
    T dequeue()
    {
        Node *ptr_temp;
        T data_temp;
        
        if(is_empty())
        {
            return static_cast<T>(0);
        }
        else if (ptr_front ==  ptr_back)
        {
            data_temp = ptr_front->data;
            ptr_back = nullptr;
            delete ptr_front;
            ptr_front = nullptr;
        }
        else
        {
            ptr_temp = ptr_front;
            data_temp = ptr_temp->data;
            
            ptr_front = ptr_front->next;
            ptr_front->previous = nullptr;
            
            delete ptr_temp;
            ptr_temp = nullptr;
        }
        
        counter--;
        return data_temp;
    }
    
    ~Queue()
    {
        while(!is_empty())
            dequeue();
    }
};


template <typename T>
void Print(Queue<T> &temp_queue, std::vector<T> &temp_vector)
{
    typename std::vector<T>::iterator itr;
    
    while(!temp_queue.is_empty())
    {
        temp_vector.push_back(temp_queue.dequeue());
    }
    
    for(itr = temp_vector.begin(); itr != temp_vector.end(); itr++)
    {
        std::cout << *itr << "\t";
    }
}


template <typename T>
void fill_up_the_queue(Queue<T> &temp_queue)
{
    std::string A = "Apples";
    std::string B = "Bananas";
    std::string C = "Grapes";
    std::string D = "Berries";
    std::string E = "Oranges";
    
    std::cout << "Order going in -> " << A << "\t" << B << "\t" << C << "\t" << D << "\t" << E << "\t" ;

    temp_queue.enqueue(A);
    temp_queue.enqueue(B);
    temp_queue.enqueue(C);
    temp_queue.enqueue(D);
    temp_queue.enqueue(E);
}


int main(int argc, const char * argv[]) 
{
    std::cout << "Hello, World, this is a Queue!\n\n";
    
    Queue<std::string> my_queue;
    std::vector<std::string> my_vector;
    
    
    // testing enqueue() and dequeue()
    std::cout << "Testing push() and pop()...\n";
    fill_up_the_queue(my_queue);
    std::cout << "\nOrder goin out -> "; Print(my_queue, my_vector);
    
    // testing is_empty()
    std::cout << "\n\nTesting is_empty()...\n";
    if(my_queue.is_empty())
        std::cout << "The queue is now empty!\n\n";
    else
        std::cout << "The queue is not empty!\n\n";
    
    // testing is_full()
    std::cout << "Testing is_full()...\n";
    fill_up_the_queue(my_queue);
    if(my_queue.is_full())
        std::cout << "\nThe queue is now full!\n\n";
    else
        std::cout << "\nThe queue is not full!\n\n";
    
    // testing front()
    std::cout << "Testing front()...\n";
    std::cout << "The top is " << my_queue.front();
    
    puts("");
    puts("");
    return 0;
    return 0;
}
