#ifndef CONTAINER_H
#define CONTAINER_H
#define capMax 10

template<class T>
class Container {
private:
  int size;
  int capacity;
  T* array;
  //Utility
  void deepCopy(T*, int, int);
  void deepCopy(T*, T*, int, int);
  void resize();
  void deleteAnElement(int);
  int getCapacity() const;
public:
  Container();
  Container(const Container&);
  ~Container();
  //Getters
  bool isFull() const;
  bool isEmpty() const;
  int getSize() const;
  Container operator+(const Container&) const;
  Container& operator=(const Container&);
  bool operator==(const Container&) const;
  bool operator!=(const Container&) const;
  T& operator[](int i) const;
  void clear();
  void merge(const Container<T>&);
  T search(int) const;
  int search(const T&) const;
  void insert(const T&);
  void remove(const T&);
  void remove(int);

  class const_iterator {
      friend class Container<T>;
    private:
      const T* t;
      bool pastTheEnd;
      // convertitore "privato" T* => const_iterator
      const_iterator(T*, bool pte = false);
    public:
      const_iterator();
      const_iterator& operator++();
      const_iterator operator++(int);
      const_iterator& operator--();
      const_iterator operator--(int);
      bool operator==(const const_iterator&) const;
      bool operator!=(const const_iterator&) const;
      const T& operator*() const;
      const T* operator->() const;
    };
};

template<class T>
void Container<T>::deepCopy(T *t, int start, int size) { for (int i = start; i < size; i++) array[i] = t[i];}

template<class T>
void Container<T>::deepCopy(T *st , T *t, int start, int size) { for (int i = start; i < size; i++) st[i] = t[i - start]; }

template<class T>
void Container<T>::resize() {
    capacity *= 2;
    T* temp = new T[capacity];
    for (int i = 0; i < size; ++i) temp[i] = array[i];
    delete[] array;
    array = temp;
}

template<class T>
void Container<T>::deleteAnElement(int index) {
  T* temp = new T[capacity];
  int j = 0;
  for (int i = 0; i < size; i++) if (i != index) { temp[j] = array[i]; j++; }
  size--;
  delete[] array;
  array = temp;
}

template<class T>
Container<T>::Container() : size(0), capacity(capMax), array(new T[capacity]) {}

template<class T>
Container<T>::Container(const Container& cnt) : size(cnt.size), capacity(cnt.capacity), array(new T[capacity]) {
  deepCopy(cnt.array, 0, cnt.size);
}

template<class T>
Container<T>::~Container<T>() { if (array) delete[] array; }

template<class T>
int Container<T>::getSize() const { return size; }

template<class T>
int Container<T>::getCapacity() const { return capacity; }

template<class T>
bool Container<T>::isEmpty() const { return size == 0; }

template<class T>
bool Container<T>::isFull() const { return size == capacity; }

template<class T>
Container<T> Container<T>::operator+(const Container& obj) const { return merge(obj); }

template<class T>
Container<T>& Container<T>::operator=(const Container& cnt) {
    if (this != &cnt) {
      delete[] array;
      size = cnt.size;
      capacity = cnt.capacity;
      array = size == 0 ? nullptr : new T[capacity];
      deepCopy(cnt.array, 0,  cnt.size);
    }
    return *this;
}

template<class T>
bool Container<T>::operator==(const Container& cnt) const {
    if (this == &cnt) return true;
    if (size != cnt.size) return false;
    bool continua = true;
    for (int i=0; i < size && continua; i++) if (array[i] != cnt.array[i]) continua = !continua;
    return continua;
}

template<class T>
bool Container<T>::operator!=(const Container& cnt) const { return !(*this == cnt); }

template<class T>
T& Container<T>::operator[](int i) const { return array[i]; }

template<class T>
void Container<T>::clear() {
  size = 0;
  capacity = capMax;
  delete[] array;
  array = new T[capacity];
}

template<class T>
void Container<T>::merge(const Container<T> &arr) {
  capacity += arr.capacity;
  T* temp = new T[capacity];
  deepCopy(temp, array, 0, size);
  deepCopy(temp, arr.array, size, size + arr.size);
  size += arr.size;
  delete[] array;
  array = temp;
}

template<class T>
int Container<T>::search(const T& obj) const {
  bool continua = true;
  int i = 0;
  for (i = 0; i < size && continua; i++) { if (array[i] == obj) continua = !continua; }
  return (continua == false) ? i-1 : -1;
}

template<class T>
T Container<T>::search(int index) const {
  bool continua = true;
  int i = 0;
  for (i = 0; i < index && continua; i++) { continua = !continua; }
  return array[i-1];
}

template<class T>
void Container<T>::insert(const T& obj) {
    if (search(obj) == -1) {
      if (size + 1 > capacity) resize();
      size++;
      array[size-1] = obj;
    }
}

template<class T>
void Container<T>::remove(const T& obj) { if (size > 0) { int index = search(obj); if (index != -1) { deleteAnElement(index); } } }

template<class T>
void Container<T>::remove(int index) { if (index < size) { deleteAnElement(index); } }

//  CONST ITERATOR
template<class T>
Container<T>::const_iterator::const_iterator(T *p, bool pte): t(p), pastTheEnd(pte) {}

template<class T>
Container<T>::const_iterator::const_iterator(): t(nullptr), pastTheEnd(false) {}

template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator++() {
  if (t != nullptr) {
    if (!pastTheEnd) {
      if (t + 1 != nullptr) {t = t + sizeof (T);}
      else { t += sizeof(T); pastTheEnd = true; }
     }
  }
  return *this;
}

template<class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int) {
  const_iterator aux(*this);
  ++t;
  return aux;
}

template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator--() {
  if (t != nullptr) {
    if (!pastTheEnd) t = t - sizeof(T);
    else {t = t - sizeof(T); pastTheEnd = false;}
   }
   return *this;
}

template<class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator--(int) {
  const_iterator aux(*this);
  --t;
  return aux;
}

template<class T>
bool Container<T>::const_iterator::operator==(const const_iterator &iter) const{
  return t == iter.t;
}

template<class T>
bool Container<T>::const_iterator::operator!=(const const_iterator &iter) const {
  return !(t == iter.t);
}

template<class T>
const T& Container<T>::const_iterator::operator*() const {
  return *t;
}

template<class T>
const T* Container<T>::const_iterator::operator->() const{
  return &t;
}

#endif // CONTAINER_H
