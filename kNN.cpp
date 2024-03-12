#include "kNN.hpp"



//LinkedList
template<typename T>
void LinkedList<T>::insert(int index, T value)
{
    if (index == size) {
        push_back(value);
    } else if (index == 0) {
        push_front(value);
    } else {
        setposition(index);
        Node<T> *tmp = new Node<T>(value);
        tmp->next = curr;
        curr->prev = tmp;
        tmp->prev = curr->prev;
        curr->prev->next = tmp;
        curr = tmp;
        size++;
    }

}

template<typename T> void LinkedList<T>::remove(int index)
{
    if (index < 0 || index >= size)
    {
        return;
    }
    if (index == 0)
    {
        Node<T> *tmp = head;
        head = head->next;
        head->prev = nullptr;
        delete tmp;
    }
    else if (index == size - 1) {
        Node<T> *tmp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete tmp;
    }
    else
    {
        setposition(index);
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        size--;
    }
}

template<typename T> T& LinkedList<T>::getHead() const
{
    return this->head->data;
}
template<typename T> T& LinkedList<T>::getTail() const
{
    return this->tail->data;
}

template<typename T> T& LinkedList<T>::get(int index) const
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

template<typename T> int LinkedList<T>::length() const
{
    return this->size;
}

template<typename T> void LinkedList<T>::push_back(T value)
{
    Node<T> *tmp = new Node<T>(value);
    if (this->head == nullptr)
    {
        this->head = tmp;
        this->tail = tmp;
    }
    else
    {
        this->tail->next = tmp;
        tmp->prev = this->tail;
        this->tail = tmp;
    }
    this->size++;
}

template<typename T> void LinkedList<T>::push_front(T value)
{
    Node<T> *tmp = new Node<T>(value);
    if (this->head == nullptr)
    {
        this->head = tmp;
        this->tail = tmp;
    }
    else
    {
        this->head->prev = tmp;
        tmp->next = this->head;
        this->head = tmp;
    }
    this->size++;
}

template<typename T> inline void LinkedList<T>::setposition(int index)
{
    if (index < 0 || index >= size)
    {
        throw;

    }
    if (index < size / 2)
    {
        curr = head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
    }
    else
    {
        curr = tail;
        for (int i = size - 1; i > index; i--)
        {
            curr = curr->prev;
        }
    }
}
template<typename T>
void LinkedList<T>::print() const
{
    auto printNode = [](Node<T>* node)
    {
        if (node) {
            std::cout << node->data;
            if (node->next) {
                std::cout << " ";
            }
        }
    };

    Node<T>* dummy = head;
    while (dummy) {
        printNode(dummy);
        dummy = dummy->next;
    }
    std::cout << std::endl;
}

template<typename T>
void LinkedList<T>::clear()
{
    Node<T> *dummy = head;
    while (dummy)
    {
        Node<T> *tmp = dummy;
        dummy = dummy->next;
        delete tmp;
    }
    head = nullptr;
    tail = nullptr;
    curr = nullptr;
    size = 0;
    curpos = 0;

}

template<typename T>
void LinkedList<T>::reverse()
{
    Node<T> *dummy = head;
    head = tail;
    tail = dummy;
    this->curr = head;
    for (int i = 0; i < size; i++) {
        Node<T> *tmp = curr->next;
        curr->next = curr->prev;
        curr->prev = tmp;
        curr = curr->next;
    }
}



//VectorList
template <typename T>
void ArrayList<T>::push_back(T value)
{
    if (size == capacity)
    {
        resize(capacity * 1.5);
    }
    data[size++] = value;
}
template<typename T>
void ArrayList<T>::push_front(T value)
{
    if (size == capacity)
    {
        resize(capacity * 1.5);
    }
    for (int i = size; i > 0; i--)
    {
        data[i] = data[i - 1];
    }
    data[0] = value;
    size++;
}

template<typename T>
void ArrayList<T>::insert(int index, T value)
{
    if (index < 0 || index > size)
    {
        return;
    }
    if (size == capacity)
    {
        resize(capacity * 1.5);
    }
    for (int i = size; i > index; i--)
    {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}

template<typename T>
void ArrayList<T>::remove(int index)
{
    if (index < 0 || index >= size)
    {
        return;
    }
    for (int i = index; i < size - 1; i++)
    {
        data[i] = data[i + 1];
    }
    size--;
}

template<typename T>
T& ArrayList<T>::get(int index) const
{
    if (index < 0 || index >= size)
    {
        throw;
    }
    return data[index];
}

template<typename T>
void ArrayList<T>::set(int pos, T val)
{
    if (pos < 0 || pos >= size)
    {
        return ;
    }
    data[pos] = val;
}

template<typename T>
int ArrayList<T>::length() const
{
    return size;
}

template<typename T>
void ArrayList<T>::clear()
{
    delete[] data;
    data = new T[capacity];
    size = 0;
}
template<typename T>
void ArrayList<T>::print() const
{
    for (int i = 0; i < size; i++)
    {
        cout << data[i] << " ";
    }
    cout << std::endl;
}

template<typename T>
void ArrayList<T>::reverse()
{

    for (int i = 0; i < size / 2; i++)
    {
        T temp = data[i];
        data[i] = data[size - i - 1];
        data[size - i - 1] = temp;

    }
}



//Dataset

bool Dataset::loadFromCSV(const char *fileName)
{
    ifstream file(fileName);
    if(!file.is_open())
    {
        throw;
    }
    if (data->length() > 0)
    {
        data->clear();
    }
    string line;
    bool label = true;
    while(getline(file,line))
    {
        istringstream iss(line);
        string token;
        if(label)
        {
            while(getline(iss,token,','))
            {
                labels->push_back(token);
            }
            label = false;
            continue;
        }
        else
        {
            LinkedList<int> *row = new LinkedList<int>();
            while(getline(iss,token,','))
            {
                row->push_back(stoi(token));
            }
            data->push_back(row);
        }
    }
    file.close();
    return true;

}
void Dataset::printLabel() const
{
    for(int i=0; i<labels->length(); i++)
    {
        cout << labels->get(i) << " ";
    }
}

void Dataset::printHead(int nRows, int nCols) const
{
    if (nRows < 0 || nCols < 0)
    {
        return;
    }
    for(int i=0; i<nCols-1; i++)
    {
        cout << labels->get(i) << " ";
    }
    cout << labels->get(nCols-1) << endl;

    for (int i=0 ; i < nRows; i++)
    {
        LinkedList<int> *row = data->get(i);
        cout << row->get(0);
        for (int j = 1; j < nCols; j++)
        {
            cout << " " << row->get(j);
        }
        cout << endl;
    }


}

void Dataset::printTail(int nRows, int nCols) const
{
    if (nRows <0 || nCols <0)
    {
        return ;
    }
    for(int i=labels->length()-nCols; i<labels->length()-1; i++)
    {
        cout << labels->get(i) << " ";
    }
    cout << labels->get(labels->length()-1) << endl;
    for (int i = data->length() - nRows; i < data->length(); i++)
    {
        LinkedList<int> *row = data->get(i);
        for (int j = row->length() - nCols; j < row->length(); j++)
        {
            cout << " " << row->get(j);
        }
        cout << endl;
    }

}

void Dataset::getShape(int &nRows, int &nCols) const
{
    nRows = data->length();
    nCols = data->get(0)->length();
}

void Dataset::columns() const
{
    cout << "label";
    for(int i=0; i<data->get(0)->length(); i++)
    {
        for(int j=0; j < data->length(); j++)
        {
            cout << " " << data->get(j)->get(i);
        }
        cout << " " << i;
    }
}

bool Dataset::drop(int axis, int index, std::string columns)
{
    if (axis == 0)
    {
        if (index < 0 || index >= data->length())
        {
            return false;
        }
        data->remove(index);
    }
    else if (axis == 1)
    {
        LinkedList<int> *row = data->get(0);
        int colIndex = -1;
        for (int i = 0; i < row->length(); i++)
        {
            if (columns == to_string(i))
            {
                colIndex = i;
                break;
            }
        }
        if (colIndex == -1)
        {
            return false;
        }
        for (int i = 0; i < data->length(); i++)
        {
            LinkedList<int> *row = data->get(i);
            row->remove(colIndex);
        }
    }
    return true;
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const
{
    Dataset result;
    if (startRow < 0)
    {
        startRow = 0;
    }
    if (endRow < 0 || endRow >= data->length())
    {
        endRow = data->length() - 1;
    }
    if (startCol < 0)
    {
        startCol = 0;
    }
    if (endCol < 0 || endCol >= data->get(0)->length())
    {
        endCol = data->get(0)->length() - 1;
    }
    for (int i = startRow; i <= endRow; i++)
    {
        LinkedList<int> *row = new LinkedList<int>;
        for (int j = startCol; j <= endCol; j++)
        {
            row->push_back(data->get(i)->get(j));
        }
        result.data->push_back(row);
    }
    return result;
}

LinkedList<LinkedList<int> > Dataset::getData() const
{

    LinkedList<LinkedList<int>> res;
    for (int i = 0; i < data->length(); i++) {
        res.push_back(*data->get(i));
    }
    return res;
}


bool Dataset::getSize() const
{
    return this->n;

}

//kNN
ArrayList<ArrayList<int> *> * kNN::convert2D(const LinkedList<LinkedList<int>> &list) {
    ArrayList<ArrayList<int> *> *result = new ArrayList<ArrayList<int> *>;
    for (int i = 0; i < list.length(); ++i)
    {
        ArrayList<int> *subList = new ArrayList<int>;
        LinkedList<int>&llSubList = list.get(i);
        for (int j = 0; j < llSubList.length(); ++j)
        {
            subList->push_back(llSubList.get(j));
        }
        result->push_back(subList);
    }
    return result;
}

ArrayList<int>* kNN::convert1D( const LinkedList<int> &list)
{
    ArrayList<int>* res = new ArrayList<int>;

    for (int i = 0; i < list.length(); ++i)
    {
        res->push_back(list.get(i));
    }
    return res;
}


// Then in your fit function

void kNN::fit(const Dataset &X_train, const Dataset &y_train)
{
    if (this->xTrain != nullptr)
    {
        for(int i=0; i < this->xTrain->length();i++)
        {
            delete xTrain->get(i)->data;
        }

    }
    this->xTrain = this->convert2D(X_train.getData());

    if (this->yTrain != nullptr)
    {
        delete yTrain;
    }
    this->yTrain = this->convert1D(y_train.getData().get(0));
}

inline int majority(ArrayList<int> &arr)
{
    int n = arr.length();
    int maxCount = 0, index = -1;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr.get(i) == arr.get(j))
                count++;
        }

        if (count > maxCount) {
            maxCount = count;
            index = i;
        }
    }

    return arr.get(index);
}


void train_test_split(Dataset& X, Dataset& y, double test_size,
                      Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test)
                      {

    int n = X.getRow();
    int m = X.getCols();
    int nTrain = n * (1 - test_size);
    int nTest = n - nTrain;
    for (int i = 0; i < nTrain; i++)
    {
        LinkedList<int> *row = new LinkedList<int>();
        for (int j = 0; j < m; j++)
        {
            row->push_back(X.getData().get(i).get(j));
        }
       // X_train.getData().push_back(row);
        y_train.getData().get(0).push_back(y.getData().get(0).get(i));
    }

    return;
}

 int Hoare(int left, int right)
{
    return (left + right) / 2;
}

void qSort(ArrayList<int> &arr, int left, int right)
{
    int i = left, j = right;
    int pivot = arr.get(Hoare(left, right));
    while (i <= j)
    {
        while (arr.get(i) < pivot)
        {
            i++;
        }
        while (arr.get(j) > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            int tmp = arr.get(i);
            arr.set(i, arr.get(j));
            arr.set(j, tmp);
            i++;
            j--;
        }
    }
    if (left < j)
    {
        qSort(arr, left, j);
    }
    if (i < right)
    {
        qSort(arr, i, right);
    }
}



Dataset kNN::predict(const Dataset &X_test)
{
    Dataset res;
    ArrayList<int>* distances = new ArrayList<int>();
    int cnt=0;

    ArrayList<ArrayList<int>*>* sub_Test = convert2D(X_test.getData());
    //LinkedList<int> row = X_test.getData().get(0);

    for(int i=0; i < sub_Test->length();i++)
    {

        int val =0;
        for(int j=0; j < xTrain->length();j++)
        {
            ArrayList<int>* rowTrain = xTrain->get(j);
            for(int l=0; l < rowTrain->length();l++)
            {
                val += sqrt(pow(sub_Test->get(i)->get(l) - rowTrain->get(l),2));
            }
            distances->push_back(sqrt(val));

        }

        qSort(*distances, 0, distances->length() - 1);
        ArrayList<int> tmp(k);
        for(int i=0; i < k; i++)
        {
            tmp.push_back(distances->get(i));
        }
        distances->clear();
        res.getData().get(0).push_back(majority(tmp));

    }
    delete distances;
    sub_Test->clear();
    delete sub_Test;
return res;

}
