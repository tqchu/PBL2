#ifndef LIST_H
#define LIST_H
#include "CustomException.h"
#include "utils.h"

    template <typename T>
    class ArrayList
{
private:
    T *array;
    int capacity;

    template <typename U>
    T *mergeSort(T *array, int theCapacity, int arraySize, bool (*sorter)(const T& t1,const T& t2, bool (*order)(const U& u,const U& v)), bool (*order)(const U& u,const U& v));

public:
    int size;
    ArrayList();
    ~ArrayList();
    void add(const T &element);
    bool isEmpty();
    void remove(int id);
    void reset();
    void reallocate();
    int getMaxId();
    bool every(bool (*condition)(const T& t));
    template <typename U>
    bool every(bool (*condition)(const T& t,const U& u),const U& u);
    bool some(bool (*condition)(const T& t));
    template <typename U>
    bool some(bool (*condition)(const T& t,const U& u),const U& u);
    void forEach(void (*callback)(const T&t));
    template <typename U>
    void forEach(void (*callback)(const T &t,const U& u),const U& u);
    const T &operator[](int index);
    template <typename U>  
    void sort(bool (*sorter)(const T& t1,const T& t2, bool (*order)(const U& u,const U& v)), bool (*order)(const U& u,const U& v));

    template <typename U>
    bool contains(bool (*func)(const T& t,const U& u),const U& u) const;
    bool contains(const T&) const;
    template <typename U>
    T& get(bool (*func)(const T& t,const U& u),const U& u) const;
    template <typename U>

    ArrayList<T> getGroup(bool (*func)(const T &t, const U &u), const U &u) const;
    const ArrayList<T> &operator=(const ArrayList<T> &);
    template <typename U>
    friend ostream &operator<<(ostream &out, const ArrayList<U> &list);
    //* ... cập nhật thông tin element  
    void update();
};
template <typename T>
ArrayList<T>::ArrayList()
{
   
    array = new T[20];
    capacity = 20;
    size = 0;
};
template <typename T>
ArrayList<T>::~ArrayList()
{

    delete[] array;
    array = NULL;
}
/**
 * thêm vào cuối ds
 */
template <typename T>
bool ArrayList<T>::isEmpty(){
    return (this->size == 0);
}
template <typename T>
void ArrayList<T>::add(const T &element)
{

    if ((size - 1) == capacity)
    {

        reallocate();
    }
    array[size] = element;
    size++;
    // sorted = false;
}

// xoá một element khỏi ds bằng id

template <typename T>
void ArrayList<T>::remove(int id)
{
    // tìm index của element có id = (param) id
    int i = 0;
    for (; i < size; i++)
    {
        if (array[i].getId() == id)
            break;
    }

    if (i == size)
        throw non_existent_element();
    else
    {
        for (int j = i; i < size; i++)
        {

            array[i] = array[i + 1];
        }
        size--;
    }
}
// kiểm tra ds có tồn tại element có id là i không

// thay đổi kích thước (capacity)
template <typename T>
void ArrayList<T>::reset(){
    delete[] array;
    array = new T[20];
    capacity = 20;
    size = 0;
}
template <typename T>
void ArrayList<T>::reallocate()
{

    capacity += 10;
    T *temp = new T[capacity];

    for (int i = 0; i < size; i++)
    {

        temp[i] = array[i];
    }

    delete[] array;

    array = temp;
}
template <typename T>
int ArrayList<T>::getMaxId()
{
    int maxId = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i].getId() > maxId)
            maxId = array[i].getId();
    }
    return maxId;
}

template <typename T>
template <typename U>
bool ArrayList<T>::contains(bool (*func)(const T& t,const U& u),const U& u) const
{
    for (int i = 0; i < size; i++)
    {
        if ((*func)(array[i], u))
            return true;
    }
    return false;
}
template <typename T>
bool ArrayList<T>::contains(const T & t) const{
    for (int i = 0; i < size;i++){
        if (array[i]==t)
            return true;
    }
    return false;
}

template <typename T>
template <typename U>
T& ArrayList<T>::get(bool (*func)(const T& t,const U& u),const U& u) const
{
    for (int i = 0; i < size; i++)
    {
        if ((*func)(array[i], u))
            return array[i];
    }
    throw non_existent_element();
}
template <typename T>
template <typename U>
ArrayList<T> ArrayList<T>::getGroup(bool (*func)(const T& t,const U& u),const U& u) const
{
    ArrayList<T> group;
    for (int i = 0; i < size; i++)
    {
        if ((*func)(array[i], u))
            group.add(array[i]);
    }
    return group;
}
template <typename T>
const ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &l){
    capacity = l.capacity;
    size = l.size;
    delete[] array;
    array = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        array[i] = l.array[i];
    }
    return (*this);
}
template <typename T>
const T &ArrayList<T>::operator[](int index)
{
    return array[index];
}
template <typename T>
template <typename U>
void ArrayList<T>::sort(bool (*sorter)(const T& t1,const T& t2, bool (*order)(const U& u,const U& v)), bool (*order)(const U& u,const U& v))
{
    T *temp = mergeSort(array, capacity, size, sorter, order);
    delete[] array;
    array = temp;
}

template <typename T>
template <typename U>
T *ArrayList<T>::mergeSort(T *array, int theCapacity, int arraySize, bool (*sorter)(const T& t1,const T& t2, bool (*order)(const U& u,const U& v)), bool (*order)(const U& u,const U& v))
{

    T *returnArray;

    // If the array is more than one element.
    if (arraySize > 1)
    {

        int size1 = arraySize / 2;
        int size2 = arraySize - size1;

        T *array1;
        T *array2;

        // Recurse.
        array1 = mergeSort(array, size1, size1, sorter, order);
        array2 = mergeSort(array + size1, size2, size2, sorter, order);

        // Allocate memory for return array.
        returnArray = new T[theCapacity];

        // Loop through all elements in returnArray.
        int i = 0, j = 0, k = 0;
        while (i < arraySize)
        {

            // Place the lesser of two elements in returnArray.
            if ((j < size1) && (k == size2 || (*sorter)(array1[j], array2[k], order)))
            {

                returnArray[i] = array1[j];
                j++;
            }
            else
            {

                returnArray[i] = array2[k];
                k++;
            }

            i++;
        }

        // Free the memory allocated in the recursive calls.

        delete[] array1;
        delete[] array2;
        array1 = 0;
        array2 = 0;
    }
    // If one element is in the passed array.
    else
    {

        // Allocate memory for new array, and assign passed value to it.
        // This is done so delete can be called in the calling function.
        returnArray = new T[1];
        returnArray[0] = array[0];
    }

    return returnArray;
}
template <typename T>
bool ArrayList<T>::every(bool (*condition)(const T& t)){
    for(int i=0;i<size;i++){
        if (!(*condition)(array[i])) return false;
    }
    return true;

}
template <typename T>
template <typename U>
bool ArrayList<T>::every(bool (*condition)(const T& t,const U& u),const U& u){
    for(int i=0;i<size;i++){
        if (!(*condition)(array[i],u)) return false;
    }
    return true;

}
template <typename T>
bool ArrayList<T>::some(bool (*condition)(const T& t)){
    for(int i=0;i<size;i++){
        if ((*condition)(array[i])) return true;
    }
    return false;
}
template <typename T>
template <typename U>
bool ArrayList<T>::some(bool (*condition)(const T& t,const U& u),const U& u){
    for(int i=0;i<size;i++){
        if ((*condition)(array[i],u)) return true;
    }
    return false;
}
template <typename T>
void ArrayList<T>::forEach(void (*callback)(const T& t)){
    for (int i = 0; i < size;i++){
        (*callback)(array[i]);
    }
}
template <typename T>
template <typename U>
void ArrayList<T>::forEach(void (*callback)(const T& t,const U& u),const U& u){
    for (int i = 0; i < size;i++){
        (*callback)(array[i],u);
    }
}
template <typename T>
ostream &operator<<(ostream &out, const ArrayList<T> &list){
    for(int i=0;i<list.size;i++) out<<list.array[i];
    return out;
}
#endif