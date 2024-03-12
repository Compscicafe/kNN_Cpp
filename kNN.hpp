#include "main.hpp"

template<typename T>
class Node
{
public:
    T data;
    Node* next;
    Node* prev;
    Node(T data, Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) {}


    Node(Node* next = nullptr, Node* prev = nullptr) : next(next), prev(prev) {}
};


template<typename T>
class List {
public:

    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index)  const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;


};
template<typename T>
class LinkedList: public List<T> {
private:
    int size;
    Node<T> *head;
    Node<T> *tail;
    int curpos;
    Node<T>* curr;
    //currpos == positions[0]. slow == pos[1], fast = pos[2];
public:
    ~LinkedList() override {
        this->curr = head;
        while (curr) {
            Node<T>*dummy = curr;
            curr = curr->next;
            dummy->next = nullptr;
            delete dummy;
            head = curr;
        }

    };

    LinkedList()
    {
        head = tail = nullptr;
        curr = head;
        size = 0;
        curpos = -1;
    }
    void insert(int index, T value) override;
    void remove(int index) override;
    T& getHead() const;
    T& getTail() const;


    T &get(int index) const override ;
    T& retrieve(int index)
    {
        if (index < 0 || index >= size) {
            throw ;
        }

        Node<T> *dummy = head;
        for (int i = 0; i < index; i++) {
            dummy = dummy->next;
        }
        return dummy->data;

    }
    int length() const override ;

    void push_back(T value) override ;

    void push_front(T value) override ;


    void clear() override;
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
        auto printNode = [&os](Node<T>* node) {
            if (node) {
                os << node->data;
                if (node->next) {
                    os << " ";
                }
            }
        };

        Node<T>* current = list.head;
        while (current) {
            printNode(current);
            current = current->next;
        }
        return os;
    }
    void getNext()
    {
        if (curr->next)
        {
            curr = curr->next;
            curpos++;
        }
    }

    // Member function to print the elements of the linked list
    void print() const;
    void reverse() override;
    inline void setposition(int index) ;
    void setlast()
    {
        curr = tail;
        curpos = size-1;
    }
    void setfirst()
    {
        curr = head;
        curpos = 0;
    }
    LinkedList& operator = (const LinkedList& other)
    {
        if (this == &other)
        {
            return *this;
        }
        this->clear();
        Node<T>* head;
        Node<T>* dummy = other.head;
        while (dummy)
        {
            this->push_back(dummy->data);
            dummy = dummy->next;
        }
        return *this;
    }
    LinkedList(const LinkedList& other)
    {
        this->head = new Node<T>;
        this->tail = head;
        this->curr = head;
        this->size = 1;
        this->curpos = 0;
        Node<T>* dummy = other.head;
        while (dummy)
        {
            this->push_back(dummy->data);
            dummy = dummy->next;
        }
    }



};

class Dataset {
private:
    LinkedList<LinkedList<int>*>* data;
    int n;      //the rows
    int k;      //the cols
    LinkedList<string>* labels;
    //You may need to define more
public:
    Dataset()
    {
        this->data = new LinkedList<LinkedList<int>*>();
       this-> labels = new LinkedList<string>();
    }
    ~Dataset()
    {
        for(int i=0; i < data->length(); i++)
        {
            LinkedList<int>* row = data->get(i);
            row->clear();
            delete row;
        }
        delete data;

        for(int i=0; i < labels->length(); i++)
        {
            labels->remove(i);
        }
        delete labels;
    }
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other)
    {
        if (this == &other)
        {
            return *this;
        }
        this->data = other.data;
        this->n = other.n;
        this->k = other.k;
        return *this;
    }

    int getRow() const
    {
        return n;
    }
    int getCols() const
    {
        return k;
    }

    bool getSize() const;
    bool loadFromCSV(const char* name);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    LinkedList<LinkedList<int> > getData() const;
    void printLabel() const;
};


template<typename T>
class ArrayList : public List<T>
{
public:
    T* data;
    int size;
    int capacity;
    void resize(int newCapacity)
    {
        T* temp = new T[newCapacity];
        for (int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        capacity = newCapacity;
    }
public:
    ArrayList()
    {
        data = new T[10];
        size = 0;
        capacity = 10;
    }
    ~ArrayList()
    {
        delete[] data;
    }
ArrayList(const ArrayList& other)
    {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }
    ArrayList(int size)
    {
        data = new T[size];
        this->size = size;
        capacity = size;

    }
 T& operator [] (int index) const
 {
     if (index < 0 || index >= size)
     {
         throw ;
     }
        return data[index];
 }
    friend ostream& operator<<(ostream& os, const ArrayList<T>& list) {
        for (int i = 0; i < list.size; ++i) {
            os << list.data[i] << ' ';
        }
        return os;
    }

    void push_back(T value) override;
    void push_front(T value) override;
    void insert(int index, T value) override;
    void remove(int index) override;
    T& get(int index) const override;
    void set(int pos, T val);
    int length() const override;
    void clear() override;
    void print() const override;
    void reverse() override;
};

class kNN {
private:
    ArrayList<ArrayList<int>*>*  xTrain;
    ArrayList<int>* yTrain;
    int k;
    //You may need to define more
public:
    ArrayList<ArrayList<int> *> * convert2D(const LinkedList<LinkedList<int>> &list);
    ArrayList<int>* convert1D(const LinkedList<int> &list);
    kNN(int k)
    {
        this->k = k;
    }
    void reset();
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
    void setK(int k);
    void setsize(int xsize,int ysize);
    int getK();
    int getsize();
    void Hoare(int left, int right);
    void Sorting();
    void quickSort(int left, int right);
    //You may need to define more

    ~kNN()
    {
        if(xTrain != nullptr)
        {
            xTrain->clear();
            delete xTrain;
        }
        else
        {

        }
        if(yTrain != nullptr)
        {
            yTrain->clear();
            delete yTrain;
        }
        else
        {

        }


    }

};
int pivot(int left, int right);


//utilities

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed


