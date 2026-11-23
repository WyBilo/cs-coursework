class Queue
{
private:
    Node* front;
    Node* rear;

public:
    Queue()
    {
        front = rear = nullptr;
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    void enqueue(int x)
    {
        Node* newNode = new Node;
        newNode->data = x;
        newNode->next = nullptr;

        if(isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue()
    {
        if(isEmpty())
            return;

        Node* temp = front;
        front = front->next;

        if(front == nullptr)
            rear = nullptr;

        delete temp;
    }

    int getFront()
    {
        return front->data;
    }
};