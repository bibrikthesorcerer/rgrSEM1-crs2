#pragma once
#include <iostream>


struct pair
{
  int key;
  int data;
};

class iterator;

/*класс вектор с пол€ми
  int vec_dimension - размерность вектора
  int m_size - количество пар в массиве, т.е. количество ненулевых координат вектора
  pair* m_array - вектор в виде неупор€доченного массива пар (номер, значение)
*/
class vector
{
   private:
      int vec_dimension;
      int m_size;
      pair* m_array;

      /*
      * @brief метод копировани€ - копирует пол€ объекта obj в вызвавший объект
      * @param const vector& obj
      */
      void copy(const vector& obj)
      {
         vec_dimension = obj.vec_dimension;
         m_size = obj.m_size;
         if (obj.vec_dimension == 0)
            m_array = nullptr;
         else
         {
            m_array = new pair[m_size];
            for (int i = 0; i < m_size; i++)
            {
               m_array[i].data = obj.m_array[i].data;
               m_array[i].key = obj.m_array[i].key;
            }
         }
      }
   public:
      friend iterator;
      /*
      * @brief конструктор по умолчанию создает объект с m_size = 0, m_array = nullptr
      */
      vector()
      {
         vec_dimension = 0;
         m_size = 0;
         m_array = nullptr;
      }

      /*
      * @brief конструктор копировани€ - создает новый объект и инициализирет его пол€ми объекта obj
      * @param const vector& obj
      */
      vector(const vector& obj)
      {
         copy(obj);
      }

      ~vector()
      {
         clear();
      }

      //@brief очищение контейнера
      void clear();

      /*
      * @brief оператор поиска - ищет индекс нужного элемента по ключу
      * @param int key_
      * @return индекс искомого элемента.
      * если он нулевой, то возвращаемое значение равно -1
      */
      int find(int key_) const;

      void pushback(int key_, int data_);
      void delZero(int index_);

      vector& operator=(const vector& obj);
      int operator[](int key_);
      bool operator==(const vector& obj) const;
      bool operator>(const vector& obj) const;
      bool operator<(const vector& obj) const;
      bool operator!=(const vector& obj) const;
      vector& operator+=(const vector& obj);
      vector& operator>>(int shift);
      vector& operator<<(int shift);

      /*
      * @brief оператор вывода - печатает вектор в консоль. пример вывода: //1/3/5//
      * @param std::ostream& os_, const vector& obj
      * @return std::ostream& os_
      */
      friend std::ostream& operator<< (std::ostream& os_, const vector& obj);

      /*
      * @brief оператор ввода - считывает вектор в объект. пример ввода: //1/3/5//
      * @param std::istream is_, vector& obj
      * @return std::istream& is_
      */
      friend std::istream& operator>> (std::istream& is_, vector& obj);

      vector operator+(const vector& obj) const;
      vector operator-(const vector& obj) const;
      vector operator*(const vector& obj) const;
      vector operator/(const vector& obj) const;
      
      /*
      * @brief скал€рное произведение векторов
      * @param const vector& obj
      * @return произведение - значение типа int
      */
      int scalarProduct(const vector& obj) const;
      vector subVec(int startInd, int finInd) const;

      iterator begin();
      iterator end();



};

/*итератор класса вектор с пол€ми
  pair* m_array - указатель на начальный элемент массива
  int index - индекс текущего элемента
*/
class iterator
{
private:
   pair* pointer;
public:
   friend vector;
   iterator()
   {
      pointer = nullptr;
   }

   iterator(pair& pair_)
   {
      pointer = &pair_;
   }

   iterator(const iterator& iter)
   {
      pointer = iter.pointer;
   }

   int& operator *()
   {
      return pointer->data;
   }

   int* operator->()
   {
      return &pointer->data;
   }

   iterator& operator++ ()
   {
      ++pointer;
      return *this;
   }
   iterator& operator++(int)
   {
      iterator old = *this;
      ++pointer;
      return old;
   }

   bool operator==(const iterator& iter)
   {
      return (pointer == iter.pointer);
   }

   bool operator!=(const iterator& iter)
   {
      return (pointer != iter.pointer);
   }

};