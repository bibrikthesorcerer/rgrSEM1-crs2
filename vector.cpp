#include "vector.h"
#include <iostream>

//USEFUL METHODS

void vector::clear()
{
   vec_dimension = 0;
   m_size = 0;
   delete[] m_array;
   m_array = nullptr;
}

int vector::find(int key_) const
{
   for (int i = 0; i < m_size; i++)
   {
      if(m_array[i].key == key_)// ищем пару с нужным ключом
      {
         return i; // если нашли, то вернем положение этой пары в массиве пар
      }
   }
   return -1;// если не нашли, то вернём несуществующий индекс
}

void vector::pushback(int key_, int data_)
{
   if (key_ <= 0)
      throw "error in 'pushback': index key_ is out of bounds";
   pair* temp_arr = new pair[m_size + (size_t)1]; //создадим массив пар, с размером на один больше. сюда скопируем массив из исходного объекта

   for (int i = 0; i < m_size; i++)
   {
      temp_arr[i].key = m_array[i].key;
      temp_arr[i].data = m_array[i].data;
   }

   temp_arr[m_size].key = key_;//заполняем новую пару соответствующими значениями
   temp_arr[m_size].data = data_;

   m_size++;// увеличиваем количество пар
   if (vec_dimension > key_)// ......если размерность больше ключа
   {
      if (find(key_) != -1)//то если по ключу был не ноль
         vec_dimension++;// увеличиваем размерность
   }
   else
      vec_dimension = key_;
   delete[] m_array;//удаляем предыдущий массив (сейчас все нужные элементы в массиве temp_arr)

   m_array = new pair[m_size];//заново выделяем память уже под новое кол-во пар и копируем их

   for (int i = 0; i < m_size; i++)
   {
      m_array[i].key = temp_arr[i].key;
      m_array[i].data = temp_arr[i].data;
   }
   delete[] temp_arr;// очистка временного массива
}

void vector::delZero(int index_)
{
   if (index_ < 0)
      throw "error in 'delZero': index_ is out of bounds";
   pair* temp_arr = new pair[m_size]; //создадим массив пар. сюда скопируем массив из исходного объекта

   for (int i = 0; i < m_size; i++)
   {
      temp_arr[i].key = m_array[i].key;
      temp_arr[i].data = m_array[i].data;
   }

   delete[] m_array;//удаляем предыдущий массив (сейчас все нужные элементы в массиве temp_arr)

   m_array = new pair[m_size - (size_t)1];//заново выделяем память уже под новое кол-во пар и копируем их

   for (int i = 0, j = 0; i < m_size; ++i)
   {
      if (i != index_)
      {
         m_array[j].key = temp_arr[i].key;
         m_array[j].data = temp_arr[i].data;
         ++j;
      }
      else
         continue;
   }
   --m_size;   // уменьшаем количество пар
   delete[] temp_arr;// очистка временного массива

}

//USEFUL OPERATORS

vector& vector::operator=(const vector& obj) 
{
   if (this == &obj)
      return *this;
   clear();
   copy(obj);
   return *this;
}


int vector::operator[](int key_)
{
   if(key_ <= 0)
      throw "error in 'operator[]': index out of bounds";
   if(key_ >= vec_dimension)
      throw "error in 'operator[]': index out of bounds";

   int search_res = find(key_);
   if (search_res != -1)
      return m_array[search_res].data;
   else
      return 0;
}

bool vector::operator==(const vector& obj) const
{
   if (this == &obj)
      return true;
   if (m_size != obj.m_size)
      return false;
   if (vec_dimension != obj.vec_dimension)
      return false;
   for (int i = 1; i <= vec_dimension; i++)// заходя в цикл, мы считаем что размерности и количества ненулевых пар равны
   {
      int index = find(i);//ищем i-ю координату в this
      int index_obj = obj.find(i);//ищем i-ю координату в obj
      if (index != -1 && index_obj != -1)
      {
         if (m_array[index].data != obj.m_array[index_obj].data)
            return false;
      }
      else // сюда попадаем если одна или обе координаты равны нулю
      {
         if (index == -1 && index_obj == -1)// если обе координаты равны нулю, то просто продолжаем работу
            continue;
         else
            return false;// если же одна из координат равна нулю, а другая нет - векторы не равны
      }

   }
   return true;
}

bool vector::operator<(const vector& obj) const
{
   if (this == &obj)
      return false;
   if (m_size < obj.m_size)
      return true;
   if (m_size > obj.m_size )
      return false;
   if (vec_dimension < obj.vec_dimension)
      return true;
   if (vec_dimension > obj.vec_dimension)
      return false;

   for (int i = 1; i <= vec_dimension; i++)// заходя в цикл, мы считаем что размерности и количества ненулевых пар равны
   {
      int index = find(i);//ищем i-ю координату в this
      int index_obj = obj.find(i);//ищем i-ю координату в obj
      if (index != -1 && index_obj != -1)
      {
         if (m_array[index].data >= obj.m_array[index_obj].data)
            return false;
      }
      else // сюда попадаем если одна или обе координаты равны нулю
         if (index_obj == -1)// если координата во втором векторе равна нулю, то первая либо больше либо равна нулю - а это провал
            return false;//тогда результат проверки - false
      //если координата в this равна нулю, то продолжаем проверку
   }

   return true;
}

bool vector::operator>(const vector& obj) const//
{
   if (*this < obj)
      return false;
   else
      if (*this == obj)
         return false;
      else
         return true;
}

bool vector::operator!=(const vector& obj) const
{
   if (*this == obj)
      return false;
   else
      return true;
     
}

vector& vector::operator+=(const vector& obj) 
{
   if (obj.vec_dimension == 0)
      return *this;
   for (int i = 1; i <= obj.vec_dimension; ++i)
   {
      int index = obj.find(i);
      if (index != -1)
         pushback(vec_dimension+1, obj.m_array[index].data);
      else
         vec_dimension++;
   }
   
   return *this;
}

vector& vector::operator>>(int shift)
{
   if (m_array == nullptr || m_size == 0)
      return *this;
   pair* temp_arr = new pair[m_size]; 
   int thrown = 0;
   for (int i = 0, j = 0; i < m_size; i++)
   {
      if (m_array[i].key + shift <= vec_dimension)
      {
         temp_arr[j].key = m_array[i].key + shift;
         temp_arr[j].data = m_array[i].data;
         ++j;
      }
      else
         thrown++;
   }

   delete[] m_array;//удаляем предыдущий массив (сейчас все нужные элементы в массиве temp_arr)
   m_size -= thrown;// уменьшаем количество пар

   m_array = new pair[m_size];//заново выделяем память уже под новое кол-во пар и копируем их

   for (int i = 0; i < m_size; i++)
   {
      m_array[i].key = temp_arr[i].key;
      m_array[i].data = temp_arr[i].data;
   }
   delete[] temp_arr;// очистка временного массива
   
   return *this;
}

vector& vector::operator<<(int shift)
{
   if (m_array == nullptr || m_size == 0)
      return *this;
   pair* temp_arr = new pair[m_size];
   int thrown = 0;
   for (int i = 0, j = 0; i < m_size; i++)
   {
      if (m_array[i].key - shift > 0)
      {
         temp_arr[j].key = m_array[i].key - shift;
         temp_arr[j].data = m_array[i].data;
         ++j;
      }
      else
         thrown++;
   }

   delete[] m_array;//удаляем предыдущий массив (сейчас все нужные элементы в массиве temp_arr)
   m_size -= thrown;// уменьшаем количество пар

   m_array = new pair[m_size];//заново выделяем память уже под новое кол-во пар и копируем их

   for (int i = 0; i < m_size; i++)
   {
      m_array[i].key = temp_arr[i].key;
      m_array[i].data = temp_arr[i].data;
   }
   delete[] temp_arr;// очистка временного массива
   return *this;

}

//INPUT - OUTPUT

std::ostream& operator<<(std::ostream& os_, const vector& obj)
{
   os_ << "//";
   if (obj.m_array == nullptr)// если вектор пустой, то выведем всего лишь пару слешей
   {
      os_ << "//";
      return os_;
   }
   for (int i = 1; i <= obj.vec_dimension; i++)// выводим элементы кол-во раз, соотв. размерности вектора
   {
      int index = obj.find(i);// смотрим, равняется ли i-я координата вектора нулю (находим нужный индекс)
      if (index != -1)// метод find вернет -1 только если пара i-ой координаты не содержится в массиве (т.е. она нулевая)
         os_ << obj.m_array[index].data;// если мы нашли нужную пару, то выведем
      else
         os_ << '0';// если мы не нашли пары с i-ой координатой, то это значит, что в исходном вектора она нулевая

      os_ << '/';
   }
   os_ << '/';
   return os_;
}

std::istream& operator>>(std::istream& is_, vector& obj)
{
   obj.clear();
   while (is_.peek() == ' ')//пропустим все ненужные пробелы
      is_.ignore();

   if (is_.peek() != '/')//начинается ли форматированный ввод вектора?
      throw"there are no symbol / in the input";
   else
      is_.ignore();

   if (is_.peek() != '/')//продолжается ли он или это лишь одиночный /?
      throw"there are no second symbol / in the input";
   else
      is_.ignore();

   // здесь посмотрим третий символ - если это /, то остается ситуация с вводом нуль-вектора, если нет, то считываем число
  
   int temp_arr[128];
   if (is_.peek() == '/')
   {
      is_.ignore();
      if (is_.peek() == '/')
      {
         is_.ignore();
         return is_;
      }
      else
         throw"incorrect! there are no closing double-slashes for that vector";
   }
   else
      if(is_.peek() != EOF) // для случая с вводом "///"
      {
         is_ >> temp_arr[0];
         if (is_.fail())
            throw"symbol of non-int type was read";
         else
         {
            if(temp_arr[0] != 0)
               obj.m_size++;
            obj.vec_dimension++;
         }
      }
      else
         throw"incorrect! there are no closing double-slashes for that vector";

   bool read_flag = true; //флаг, который ознаменует окончание считывания

   for (int i = 1; read_flag; i++)// начинаем с i=1, т.к. один раз координату мы уже считали
   {
      if (is_.peek() == '/')// если видим /, то это либо разделяющий координаты символ, либо начало закрывающего двойного слеша
      {
         is_.ignore();
         if (is_.peek() == '/')
         {
            read_flag = false;// если это двойной слеш
            is_.ignore();
         }
         else
            if (is_.peek() != EOF) // для случая если введут "//.../"  (А НАДО ЛИ ЭТО ОБРАБАТЫВАТЬ? РАЗВЕ НЕ ОБРАБОТАНО РАНЬШЕ???)
            {
               {
                  is_ >> temp_arr[i];
                  if (is_.fail())
                     throw"symbol of non-int type was read";
                  else
                  {
                     if (temp_arr[i] != 0)
                        obj.m_size++;
                     obj.vec_dimension++;
                  }
               }
            }
            else
               throw"incorrect! there are no closing double-slashes for that vector";
      }
   }

   obj.m_array = new pair[obj.m_size];

   for (int i = 0, j= 0; i < obj.m_size; ++i, ++j)
   {
      while(temp_arr[j] == 0)
         ++j;
      obj.m_array[i].key = j+1;
      obj.m_array[i].data = temp_arr[j];

   }

   return is_;
}

//ARITHMETIC ACTIONS (+ - * /)

vector vector::operator+(const vector& obj) const
{
      vector result = *this;
      for (int i = 0; i < obj.m_size; i++)
      {
         int index = result.find(obj.m_array[i].key);
         if (index != -1)
         {
            result.m_array[index].data += obj.m_array[i].data;
            if (result.m_array[index].data == 0)// если появилась пара с 0 - чистим ее
               result.delZero(index);
         }
         else
         {
            result.pushback(obj.m_array[i].key, obj.m_array[i].data);
         }
      }
      return result;
}

vector vector::operator-(const vector& obj) const
{
   vector result = *this;
   for (int i = 0; i < obj.m_size; i++)
   {
      int index = result.find(obj.m_array[i].key);
      if (index != -1)
      {
         result.m_array[index].data -= obj.m_array[i].data;
         if (result.m_array[index].data == 0)// если появилась пара с 0 - чистим ее
            result.delZero(index);
      }
      else
      {
         result.pushback(obj.m_array[i].key, -obj.m_array[i].data);
      }
   }
   return result;
}

vector vector::operator*(const vector& obj) const
{
   if (vec_dimension != obj.vec_dimension)
      throw "error in 'operator*': different dimensions";
   vector result = *this;
   for (int i = 0; i < result.vec_dimension; i++)
   {
      int index = result.find(i+1);
      int index_obj = obj.find(i+1);
      if (index != -1 && index_obj != -1)
         result.m_array[index].data *= obj.m_array[index_obj].data;
      if (index != -1 && index_obj == -1)
         result.delZero(index); //мы все знаем что происходит при умножении на 0, не так ли?

   }
   return result;
}

vector vector::operator/(const vector& obj) const
{
   if (vec_dimension != obj.vec_dimension)
      throw "error in 'operator/': different dimensions";
   if(m_size == 0 || obj.m_size == 0)
      throw "error in 'operator/': attempt of dividing by zero was caught";

   vector result = *this;
   for (int i = 0; i < result.vec_dimension; i++)
   {
      int index = result.find(i+1);
      int index_obj = obj.find(i+1);
      if (index != -1 && index_obj != -1)
      {
         result.m_array[index].data /= obj.m_array[index_obj].data;
         if (result.m_array[index].data == 0)
            result.delZero(index);
      }
      if (index != -1 && index_obj == -1)
         throw "attempt of dividing by zero was caught";
   }
   return result;
}

//OTHER METHODS

int vector::scalarProduct(const vector& obj) const
{
   if (vec_dimension != obj.vec_dimension)
      throw "error in 'scalarProduct': different dimensions";
   int scProd = 0;

   for (int i = 0; i < std::min(vec_dimension,obj.vec_dimension); i++)
   {
      int index = find(i+1);
      int index_obj = obj.find(i+1);
      if (index != -1 && index_obj != -1)
         scProd += (m_array[index].data*obj.m_array[index_obj].data);//если i-я координата есть в обоих векторах, то кидаем их произв в сумму 
      //иначе ничего не требуется, т.к. одна из координат равна 0, след. их произведение тоже
   }

   return scProd;
}

vector vector::subVec(int startInd, int finInd) const
{
   if (startInd <= 0 || finInd > vec_dimension)
      throw "error in 'subvec': index out of bounds";
   vector subVector;

   for (int i = startInd, j = 1; i <= finInd; ++i, ++j)
   {
      int index = find(i);
      if (index != -1)
         subVector.pushback(j, m_array[index].data);
      else
         ++subVector.vec_dimension;
   }

   subVector.vec_dimension = finInd - startInd + 1;

   return subVector;
}

iterator vector::begin()
{
   if (m_array != nullptr)
   {
      return iterator(m_array[0]);
   }
   else
      throw "error in 'begin': m_array is nullptr";
}

iterator vector::end()
{
   return iterator(m_array[m_size]);
}
