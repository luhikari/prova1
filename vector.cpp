#include <stdexcept>


/* Costructos - Destructors */

//Constructor
template<typename Data>
Vector<Data>::Vector(const ulong newsize){
    Elements = new Data[newsize] {};
    size = newsize;
}
//Destructor
template<typename Data>
Vector<Data>::~Vector() {
	delete[] Elements;
}
/* ************************************************************************** */
// Copy constructor
  template <typename Data>
  Vector<Data>::Vector(const Vector<Data>& vec){
    size = vec.size;
    Elements = new Data[vec.size];
     std::copy(vec.Elements, vec.Elements + vec.size, Elements);

    for(ulong i=0; i<size; i++)
      Elements[i] = vec[i];
  }

// Move constructor
  template <typename Data>
  Vector<Data>::Vector(Vector<Data>&& vec) noexcept{
    std::swap(Eelements, vec.Elements);
    std::swap(size, vec.size);
  }
/* ************************************************************************** */
/* Assignment - Operators */

// Copy assignment
  template <typename Data>
  Vector<Data>& Vector<Data>::operator=(const Vector<Data>& copyFrom){
    if(&copyFrom != this){ //self assignment is invalid
      size = copyFrom.size;

      if(size != 0){
        Data* newData = new Data[size];

        for(ulong i=0; i<size; i++)
          newData[i] = copyFrom.Elements[i];

        delete[] Elements;

        Elements = newData;
      }else{
        Elements = nullptr;
      }

    }

    return *this;
  }

// Move assignment
  template <typename Data>
  Vector<Data>& Vector<Data>::operator=(Vector<Data>&& moveFrom) noexcept{
    std::swap(size, moveFrom.size);
    std::swap(Elements, moveFrom.Elements);

    return *this;
  }
/* ************************************************************************** */ 

// Equal operator
 template<typename Data>
bool Vector<Data>::operator==(const Vector& vec) const noexcept {
	if (size == vec.size) {
		for (ulong i = 0; i < size; ++i) {
			if (Elements[i] != vec.Elements[i]) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

    return flag;
  }

// Not equal operator
template<typename Data>
bool Vector<Data>::operator!=(const Vector& vec) const noexcept {
	return !(*this == vec);
}
/* ************************************************************************** */
/* Member functions */

//Resize
  template <typename Data>
  void Vector<Data>::Resize(const ulong newSize){
    if(newSize == 0)
      Clear();
      } else if(size != newsize) {
        ulong limit = (size < newsize) ? size : newsize;
        Data* TmpElements = new Data[newsize] {};
        for (ulong index = 0; index < limit; ++index) {
            std::swap(Elements[index], TmpElements[index]);
        }
        std::swap(Elements, TmpElements);
        size = newsize;
        delete[] TmpElements;
    }
}

  //Clear
  template <typename Data>
  void Vector<Data>::Clear(){
    size = 0;
    delete[] Elements;
    Elements = nullptr;
  }

  //Front
  template <typename Data>
  Data& Vector<Data>::Front() const{
    if(Elements == nullptr)
      throw std::length_error("L'Array è pieno");

    return Elements[0];
  }

  //Back
  template <typename Data>
  Data& Vector<Data>::Back() const{
    if(Elements == nullptr)
      throw std::length_error("Array is empty!");

    return Elements[size-1];
  }

  template <typename Data>
  Data& Vector<Data>::operator[](const ulong index) const{
    if(size == 0)
      throw std::length_error("Array is empty!");
      
    if(index >= size)
      throw std::length_error("Out of Range!");

    return Elements[index];
  }


/* Map and Fold */

  //Map
  template <typename Data>
  void Vector<Data>::MapPreOrder(MapFunctor function, void* par){
    for(ulong i = 0; i<size; i++)
      function(Elements[i], par);
  }

  template <typename Data>
  void Vector<Data>::MapPostOrder(MapFunctor function, void* par){
    for(ulong i=size-1; i>=0 && i < size; i--)
      function(Elements[i], par);
  }

  //Fold
  template <typename Data>
  void Vector<Data>::FoldPreOrder(FoldFunctor function, const void* cPar, void* par) const{
    for(ulong i = 0; i<size; i++)
      function(Elements[i], cPar, par);
  }

  template <typename Data>
  void Vector<Data>::FoldPostOrder(FoldFunctor function, const void* cPar, void* par) const{
    for(ulong i=size-1; i>=0 && i < size; i--)
      function(Elements[i], cPar, par);
    
    template <typename Data>
    void Vector<Data>::MapInOrder(MapFunctor function, void* par){
     for(ulong i=1; i>=0 && i < size; i++)
      function(Elements[i], par);
    
    template <typename Data>
    void Vector<Data>::FoldInOrder(MapFunctor function, void* par){
    for(ulong i=1; i>=0 && i < size; i++)
      function(Elements[i], par);
  }
    }
    //non so se devo mettere anche le breadht