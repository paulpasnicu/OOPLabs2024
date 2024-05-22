#include <iostream>
#include <exception>
using namespace std;

// Custom exceptions
class OutOfBoundsException : public exception
{
    virtual const char* what() const throw()
    {
        return "Index is out of bounds!";
    }
};

class AllocationException : public exception
{
    virtual const char* what() const throw()
    {
        return "Memory allocation failed!";
    }
};

class Compare
{
public:
    virtual int CompareElements(void* e1, void* e2) = 0;
};

template<class T>
class ArrayIterator
{
private:
    int Current; // current index in the array
    T** List; // pointer to the array
    int Size; // size of the array

public:
    ArrayIterator(T** list, int size, int current = 0) : List(list), Size(size), Current(current) {}

    ArrayIterator& operator++() {
        if (Current < Size) ++Current;
        return *this;
    }

    ArrayIterator& operator--() {
        if (Current > 0) --Current;
        return *this;
    }

    bool operator==(const ArrayIterator<T>& other) {
        return Current == other.Current;
    }

    bool operator!=(const ArrayIterator<T>& other) {
        return Current != other.Current;
    }

    T* GetElement() {
        if (Current < Size)
            return List[Current];
        return nullptr;
    }
};

template<class T>
class Array
{
private:
    T** List; // list of pointers to objects of type T*
    int Capacity; // capacity of the list
    int Size; // number of elements in the list

    void reallocate(int newCapacity) {
        T** newList = new T*[newCapacity];
        if (!newList) throw AllocationException();

        for (int i = 0; i < Size; ++i)
            newList[i] = List[i];

        delete[] List;
        List = newList;
        Capacity = newCapacity;
    }

public:
    Array() : List(nullptr), Capacity(0), Size(0) {}

    ~Array() {
        delete[] List;
    }

    Array(int capacity) : Capacity(capacity), Size(0) {
        List = new T*[capacity];
        if (!List) throw AllocationException();
    }

    Array(const Array<T>& otherArray) : Capacity(otherArray.Capacity), Size(otherArray.Size) {
        List = new T*[Capacity];
        if (!List) throw AllocationException();

        for (int i = 0; i < Size; ++i)
            List[i] = otherArray.List[i];
    }

    T& operator[] (int index) {
        if (index < 0 || index >= Size)
            throw OutOfBoundsException();
        return *List[index];
    }

    const Array<T>& operator+=(const T& newElem) {
        if (Size >= Capacity)
            reallocate(Capacity == 0 ? 1 : Capacity * 2);

        List[Size++] = new T(newElem);
        return *this;
    }

    const Array<T>& Insert(int index, const T& newElem) {
        if (index < 0 || index > Size)
            throw OutOfBoundsException();

        if (Size >= Capacity)
            reallocate(Capacity == 0 ? 1 : Capacity * 2);

        for (int i = Size; i > index; --i)
            List[i] = List[i - 1];

        List[index] = new T(newElem);
        ++Size;

        return *this;
    }

    const Array<T>& Insert(int index, const Array<T> otherArray) {
        if (index < 0 || index > Size)
            throw OutOfBoundsException();

        while (Size + otherArray.Size > Capacity)
            reallocate(Capacity == 0 ? 1 : Capacity * 2);

        for (int i = Size - 1; i >= index; --i)
            List[i + otherArray.Size] = List[i];

        for (int i = 0; i < otherArray.Size; ++i)
            List[index + i] = otherArray.List[i];

        Size += otherArray.Size;

        return *this;
    }

    const Array<T>& Delete(int index) {
        if (index < 0 || index >= Size)
            throw OutOfBoundsException();

        delete List[index];

        for (int i = index; i < Size - 1; ++i)
            List[i] = List[i + 1];

        --Size;

        return *this;
    }

    bool operator=(const Array<T>& otherArray) {
        if (this != &otherArray) {
            delete[] List;

            Capacity = otherArray.Capacity;
            Size = otherArray.Size;
            List = new T*[Capacity];
            if (!List) throw AllocationException();

            for (int i = 0; i < Size; ++i)
                List[i] = otherArray.List[i];
        }
        return true;
    }

    void Sort() {
        Sort([](const T& a, const T& b) { return a < b; });
    }

    void Sort(int(*compare)(const T&, const T&)) {
        for (int i = 0; i < Size - 1; ++i) {
            for (int j = i + 1; j < Size; ++j) {
                if (compare(*List[i], *List[j]) > 0)
                    std::swap(List[i], List[j]);
            }
        }
    }

    void Sort(Compare* comparator) {
        for (int i = 0; i < Size - 1; ++i) {
            for (int j = i + 1; j < Size; ++j) {
                if (comparator->CompareElements(List[i], List[j]) > 0)
                    std::swap(List[i], List[j]);
            }
        }
    }

    int BinarySearch(const T& elem) {
        return BinarySearch(elem, [](const T& a, const T& b) { return a < b; });
    }

    int BinarySearch(const T& elem, int(*compare)(const T&, const T&)) {
        int left = 0;
        int right = Size - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (compare(*List[mid], elem) == 0)
                return mid;
            if (compare(*List[mid], elem) < 0)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

    int BinarySearch(const T& elem, Compare* comparator) {
        int left = 0;
        int right = Size - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (comparator->CompareElements(List[mid], &elem) == 0)
                return mid;
            if (comparator->CompareElements(List[mid], &elem) < 0)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

    int Find(const T& elem) {
        for (int i = 0; i < Size; ++i)
            if (*List[i] == elem)
                return i;
        return -1;
    }

    int Find(const T& elem, int(*compare)(const T&, const T&)) {
        for (int i = 0; i < Size; ++i)
            if (compare(*List[i], elem) == 0)
                return i;
        return -1;
    }

    int Find(const T& elem, Compare* comparator) {
        for (int i = 0; i < Size; ++i)
            if (comparator->CompareElements(List[i], &elem) == 0)
                return i;
        return -1;
    }

    int GetSize() const {
        return Size;
    }

    int GetCapacity() const {
        return Capacity;
    }

    ArrayIterator<T> GetBeginIterator() {
        return ArrayIterator<T>(List, Size, 0);
    }

    ArrayIterator<T> GetEndIterator() {
        return ArrayIterator<T>(List, Size, Size);
    }
};
