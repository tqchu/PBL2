#ifndef LIST_H
#define LIST_H
#include "CustomException.h"
#include "utils.h"

/** 
 * ArrayList sử dụng một mảng cấp phát động, tự động resize
 * Sức chứa ban đầu là 20.
*/
template <typename T>
class ArrayList
{
private:
    T *array;
    int capacity;

    template <typename U>
    T *mergeSort(T *array, int theCapacity, int arraySize, bool (*sorter)(const T &t1, const T &t2, bool (*order)(const U &u, const U &v)), bool (*order)(const U &u, const U &v));

public:
    int size;
    ArrayList();
    ArrayList(const ArrayList<T> &list);

    ~ArrayList();

    void reallocate();
    void reset();
    bool isEmpty();
    void add(const T &element);
    void add(const ArrayList<T> &list);
    void remove(int id);
    void update(const T& t);
    const T &operator[](int index) const;
    int getMaxId();

    bool every(bool (*condition)(const T &t));
    template <typename U>
    bool every(bool (*condition)(const T &t, const U &u), const U &u);

    bool some(bool (*condition)(const T &t));
    template <typename U>
    bool some(bool (*condition)(const T &t, const U &u), const U &u);

    void forEach(void (*callback)(const T &t));
    template <typename U>
    void forEach(void (*callback)(const T &t, const U &u), const U &u);

    template <typename U>
    void sort(bool (*sorter)(const T &t1, const T &t2, bool (*order)(const U &u, const U &v)), bool (*order)(const U &u, const U &v));

    template <typename U>
    bool contains(bool (*func)(const T &t, const U &u), const U &u) const;
    bool contains(const T &) const;

    template <typename U>
    T &get(bool (*func)(const T &t, const U &u), const U &u) const;
    template <typename U>

    ArrayList<T> getGroup(bool (*func)(const T &t, const U &u), const U &u) const;
    const ArrayList<T> &operator=(const ArrayList<T> &);
    template <typename U>

    // FRIEND
    friend ostream &operator<<(ostream &out, const ArrayList<U> &list);
   
};
template <typename T>
ArrayList<T>::ArrayList()
{

    array = new T[20];
    capacity = 20;
    size = 0;
};

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &list)
{
    capacity = list.capacity;
    size = list.size;
    array = new T[capacity];
    for (int i = 0; i < size; i++)
        array[i] = list[i];
}

template <typename T>
ArrayList<T>::~ArrayList()
{

    delete[] array;
    array = NULL;
}

template <typename T>
bool ArrayList<T>::isEmpty()
{
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

/** 
 * Thêm vào 1 list khác
 * @param list ds thêm vào
*/
template <typename T>
void ArrayList<T>::add(const ArrayList<T> &list){
    for (int i = 0; i < list.size;i++)
    {
        add(list[i]);
    }
}

/**
 * Xoá một phần tử bất kỳ
 * @param id mã của phần tử cần xoá
 * @throws non_existent_element()
 */
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

/** 
 * Update element trong ds
 * Tìm element cần update bằng id, sau đó gán element trong ds bằng @param t
 * (element này chắc chắn có trong ds)
 * @param t element ta đưa vào để thay thế element trong mảng
*/
template <typename T>
void ArrayList<T>::update(const T &t){
    // Tìm element trong DS
    for (int i = 0; i < size;i++){
        if (array[i]==t)
            {   // Thay element tìm được
                array[i] = t;
                break;
            }
    }
}

/**
 * Reset, đưa size về 0
 */
template <typename T>
void ArrayList<T>::reset()
{
    delete[] array;
    array = new T[20];
    capacity = 20;
    size = 0;
}

/**
 * Tăng kích thước mảng khi mảng đã đầy
 */
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

/**
 * Lấy maxId từ các element trong mảng
 */
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

/**
 * Kiểm tra xem đã chứa phần tử t chưa
 * @param func hàm chứa tiêu chí tìm kiếm
 * @param U tham số của hàm func
 */
template <typename T>
template <typename U>
bool ArrayList<T>::contains(bool (*func)(const T &t, const U &u), const U &u) const
{
    for (int i = 0; i < size; i++)
    {
        if ((*func)(array[i], u))
            return true;
    }
    return false;
}

/**
 * @param t phần tử cần kiểm tra
 */
template <typename T>
bool ArrayList<T>::contains(const T &t) const
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == t)
            return true;
    }
    return false;
}

/**
 * Lấy một phần tử theo tiêu chí
 * @param func hàm tiêu chí
 * @throws non_existent_element()
 */
template <typename T>
template <typename U>
T &ArrayList<T>::get(bool (*func)(const T &t, const U &u), const U &u) const
{
    for (int i = 0; i < size; i++)
    {
        if ((*func)(array[i], u))
            return array[i];
    }
    throw non_existent_element();
}

/**
 * Lấy ra một nhóm theo tiêu chí
 * @param func
 * @param u
 */
template <typename T>
template <typename U>
ArrayList<T> ArrayList<T>::getGroup(bool (*func)(const T &t, const U &u), const U &u) const
{
    ArrayList<T> group;
    for (int i = 0; i < size; i++)
    {
        if ((*func)(array[i], u))
            group.add(array[i]);
    }
    return group;
}

/**
 * Hàm sao chép
 */
template <typename T>
const ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &l)
{
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

/**
 * chỉ lấy giá trị
 * @param index
 */
template <typename T>
const T &ArrayList<T>::operator[](int index) const
{
    return array[index];
}

/**
 * sắp xếp theo tiêu chí và thứ tự
 * sử dụng merge sort
 * @param sorter
 * @param order
 */
template <typename T>
template <typename U>
void ArrayList<T>::sort(bool (*sorter)(const T &t1, const T &t2, bool (*order)(const U &u, const U &v)), bool (*order)(const U &u, const U &v))
{
    T *temp = mergeSort(array, capacity, size, sorter, order);
    delete[] array;
    array = temp;
}

template <typename T>
template <typename U>
T *ArrayList<T>::mergeSort(T *array, int theCapacity, int arraySize, bool (*sorter)(const T &t1, const T &t2, bool (*order)(const U &u, const U &v)), bool (*order)(const U &u, const U &v))
{

    T *returnArray;

    if (arraySize > 1)
    {

        int size1 = arraySize / 2;
        int size2 = arraySize - size1;

        T *array1;
        T *array2;

        array1 = mergeSort(array, size1, size1, sorter, order);
        array2 = mergeSort(array + size1, size2, size2, sorter, order);

        // cấp phát vùng nhớ cho returnArray
        returnArray = new T[theCapacity];

        // Loop qua arraySize
        int i = 0, j = 0, k = 0;
        while (i < arraySize)
        {

            // Thêm phần tử nhỏ hơn( tăng dần)/ lớn hơn( giảm dần) vào returnArray
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

        // Thu hồi vùng nhớ của 2 mảng đã gọi đệ quy.

        delete[] array1;
        delete[] array2;
        array1 = 0;
        array2 = 0;
    }
    // Nếu mảng chỉ có 1 phần tử
    else
    {
        // Cấp phát vùng nhớ cho mảng mới
        // Để có thể gọi delete khi call function
        returnArray = new T[1];
        returnArray[0] = array[0];
    }

    return returnArray;
}

/**
 * @param condition
 */
template <typename T>
bool ArrayList<T>::every(bool (*condition)(const T &t))
{
    for (int i = 0; i < size; i++)
    {
        if (!(*condition)(array[i]))
            return false;
    }
    return true;
}
template <typename T>
template <typename U>
bool ArrayList<T>::every(bool (*condition)(const T &t, const U &u), const U &u)
{
    for (int i = 0; i < size; i++)
    {
        if (!(*condition)(array[i], u))
            return false;
    }
    return true;
}

/**
 * kiểm tra xem có ít nhất một phần tử trong mảng thoả mãn điều kiện nào đó
 * @param condition
 */
template <typename T>
bool ArrayList<T>::some(bool (*condition)(const T &t))
{
    for (int i = 0; i < size; i++)
    {
        if ((*condition)(array[i]))
            return true;
    }
    return false;
}
template <typename T>
template <typename U>
bool ArrayList<T>::some(bool (*condition)(const T &t, const U &u), const U &u)
{
    for (int i = 0; i < size; i++)
    {
        if ((*condition)(array[i], u))
            return true;
    }
    return false;
}

template <typename T>
void ArrayList<T>::forEach(void (*callback)(const T &t))
{
    for (int i = 0; i < size; i++)
    {
        (*callback)(array[i]);
    }
}
template <typename T>
template <typename U>
void ArrayList<T>::forEach(void (*callback)(const T &t, const U &u), const U &u)
{
    for (int i = 0; i < size; i++)
    {
        (*callback)(array[i], u);
    }
}

template <typename T>
ostream &operator<<(ostream &out, const ArrayList<T> &list)
{
    for (int i = 0; i < list.size; i++)
        out << list.array[i];
    return out;
}
#endif