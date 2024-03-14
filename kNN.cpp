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
        throw("File not found");
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
    //for(int i=0; i<nCols-1; i++)
   // {
     //   cout << labels->get(i) << " ";
   // }
    //cout << labels->get(nCols-1) << endl;

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
    cout << nRows << "x" << nCols << endl;
}

void Dataset::columns() const
{
    for(int i=0; i<labels->length()-1; i++)
    {
        cout << labels->get(i) << " ";
    }
    cout << labels->get(labels->length()-1) << endl;

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
    Dataset result = Dataset();
    if (endRow ==-1)
    {
        endRow = data->length()-1;
    }
    if (endCol == -1)
    {
        endCol = data->get(0)->length()-1;
    }

    for (int i = startRow; i < endRow; i++)
    {
        LinkedList<int>* row = new LinkedList<int>();
        for (int j = startCol; j < endCol; j++)
        {
            row->push_back(this->data->get(i)->get(j));
        }
        result.data->push_back(row);
    }
    return result;
}

LinkedList<LinkedList<int>*>* Dataset::getData() const
{

    return this->data;
}

//kNN
ArrayList<int>* kNN::convert1D( LinkedList<int>* list)
{
    ArrayList<int>* res = new ArrayList<int>;

    for (int i = 0; i < list->length(); ++i)
    {
        res->push_back(list->get(i));
    }
    return res;
}


void train_test_split(Dataset &X, Dataset &y, double test_size, Dataset &X_train,
                      Dataset &X_test, Dataset &y_train, Dataset &y_test)
{
    int nRows = X.getData()->length();
    int nTrain = (int)ceil(nRows* (1 - test_size));
    for(int i=0; i < nTrain;i++)
    {
        LinkedList<int>* Xrow = new LinkedList<int>();
        LinkedList<int>* Yrow = new LinkedList<int>();
        X_train.getData()->push_back(Xrow);
        y_train.getData()->push_back(Yrow);
        for(int j=0; j < X.getData()->get(0)->length();j++)
        {
            X_train.getData()->get(i)->push_back(X.getData()->get(i)->get(j));
        }
        y_train.getData()->get(0)->push_back(y.getData()->get(i)->get(0));

    }

    for(int i=nTrain; i < nRows;i++)
    {
        LinkedList<int>* Xrow = new LinkedList<int>();
        LinkedList<int>* Yrow = new LinkedList<int>();
        X_test.getData()->push_back(Xrow);
        y_test.getData()->push_back(Yrow);
        for(int j=0; j < X.getData()->get(0)->length();j++)
        {
            X_test.getData()->get(i-nTrain)->push_back(X.getData()->get(i)->get(j));
        }
        y_test.getData()->get(0)->push_back(y.getData()->get(i)->get(0));

    }


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
    else
    {xTrain = new ArrayList<ArrayList<int>*>(X_train.getData()->length());
    for (int i = 0; i < X_train.getData()->length(); ++i) {
        xTrain->push_back(convert1D(X_train.getData()->get(i)));
    }
        }
    if (this->yTrain != nullptr)
    {
        delete yTrain;
    }
    else {
        yTrain = new ArrayList<int>(y_train.getData()->length());
        for (int i = 0; i < y_train.getData()->length(); ++i) {
            yTrain->push_back(y_train.getData()->get(i)->get(0));
        }

    }

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



//Dataset kNN::predict(const Dataset &X_test)
//{
 //   Dataset res;
   // ArrayList<int>* distances = new ArrayList<int>();
    //int cnt=0;
    /*
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
        res.getData()->get(0)->push_back(majority(tmp));

    }
    delete distances;
    sub_Test->clear();
    delete sub_Test;
return res;
*/

