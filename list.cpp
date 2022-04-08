#include <stdexcept>
namespace lasd {

/* ************************************************************************** */

// STRUCT NODE
  // Specific constructors
    template <typename Data>
    List<Data>::Node::Node(Data newValue){
      value = newValue;
    }

  // Copy constructor
    template <typename Data>
    List<Data>::Node::Node(const Node& copyFrom){
      value = copyFrom.value;
    }

  // Move constructor
    template <typename Data>
    List<Data>::Node::Node(Node&& moveFrom) noexcept{
      std::swap(value, moveFrom.value);
      std::swap(next, moveFrom.next);
    }
     // Comparison operators
    template <typename Data>
    bool List<Data>::Node::operator==(const Node& comp) const noexcept{
      if(value == comp.value && next == comp.next)
        return true;

      return false;
    }

    template <typename Data>
    bool List<Data>::Node::operator!=(const Node& comp) const noexcept{
      return !(*this == comp);
    }
/* ************************************************************************** */
//LIST CONSTRUCTOR
List<Data>::List()
 {
	head = nullptr;
	tail = nullptr;
	size = 0;
 }
 //Constructor (with Linear Container)
	template <typename Data>
	List<Data>::List(const LinearContainer<Data> &container)
	{
		size = 0;

		for (ulong index = 0; index < container.Size(); ++index)
		{
			InsertAtBack(container[index]);
		}
	}
     // Copy constructor
    template <typename Data>
    List<Data>::List(const List& copyFrom){ //DEEP COPY
      if(copyFrom.head != nullptr){
        struct Node* tmp = copyFrom.head;
        while(tmp != nullptr){
          List<Data>::InsertAtBack(tmp->value);
          tmp = tmp->next;
        }
      }
    }
    // Move constructor
    template <typename Data>
    List<Data>::List(List&& moveFrom){
      std::swap(size, moveFrom.size);
      std::swap(head, moveFrom.head);
      std::swap(tail, moveFrom.tail);
    }
    // Destructor
    template <typename Data>
    List<Data>::~List(){
      Clear();
    }
    /* ************************************************************************** */
    List<Data> &List<Data>::operator=(const List<Data> &assList)
	{
		List<Data> *tmplist = new List<Data>(assList);
		std::swap(*tmplist, *this);
		delete (tmplist);
		return *this;
	}
    //Move assignment
	template <typename Data>
	List<Data> &List<Data>::operator=(List<Data> &&assList) noexcept
	{
		std::swap(head, assList.head);
		std::swap(tail, assList.tail);
		std::swap(size, assList.size);
		return *this;
	}
    /* ************************************************************************** */
    template <typename Data>
    bool List<Data>::operator==(const List& comp) const noexcept{
      if(this->size != comp.size)
        return false;

      struct Node* ptrL1 = this->head;
      struct Node* ptrL2 = comp.head;

      while(ptrL1 != nullptr && ptrL2 != nullptr){
        if(ptrL1->value != ptrL2->value)
          return false;

        ptrL1 = ptrL1->next;
        ptrL2 = ptrL2->next;
      }

      return true;
    }

    template <typename Data>
    bool List<Data>::operator!=(const List& comp) const noexcept{
      return !(*this == comp);
    }
    /* ************************************************************************** */
    //Insert At Front (Copy)
	template <typename Data>
	void List<Data>::InsertAtFront(const Data &dato) noexcept
	{
		Node *newNodo = new Node(dato);
		if (head == nullptr)
		{
			head = newNodo;
			tail = newNodo;
		}
		else
		{
			newNodo->next = head;
			head = newNodo;
		}
		size = size + 1;
	}
    //Insert At Front (Move)
	template <typename Data>
	void List<Data>::InsertAtFront(Data &&dato) noexcept
	{
		Data mvDato = std::move(dato);
		Node *newNodo = new Node(mvDato);
		if (head == nullptr)
		{
			head = newNodo;
			tail = newNodo;
		}
		else
		{
			newNodo->next = head;
			head = newNodo;
		}
		size = size + 1;
	}
    //FrontNRemove
    template <typename Data>
    Data List<Data>::FrontNRemove(){
      if(head == nullptr)
        throw std::length_error("Lista vuota!");

      Data returnValue = head->value;

      List<Data>::RemoveFromFront();

      return returnValue;
    }
    //Remove From Front
	template <typename Data>
	void List<Data>::RemoveFromFront()
	{
		if (size != 0)
		{
			Node *ptr = head;
			head = head->next;
			size = size - 1;
			delete ptr;
		}
		else
		{
			throw std::length_error("Access ad una lista vuota");
		}
	}
    //Remove From Front (with return value)
	template <typename Data>
	Data List<Data>::FrontNRemove()
	{
		if (size != 0)
		{
			Node *ptr = head;
			Data returner = head->info;
			head = head->next;
			size = size - 1;
			delete ptr;
			return returner;
		}
		else
		{
			throw std::length_error("Accesso ad una lista vuota");
		}
	}
    //InsertAtBack (Copy)
    template <typename Data>
    void List<Data>::InsertAtBack(const Data& elem){
      if(head==nullptr){
        head = new Node(elem);
        tail = head;
      }else{
        tail->next = new Node(elem);
        tail = tail->next;
      }
      size++;
    }
    //InsertAtBack (Move)
     template <typename Data>
    void List<Data>::InsertAtBack(Data&& elem){
      if(head==nullptr){
        head = new Node(elem);
        tail = head;
      }else{
        tail->next = new Node(elem);
        tail = tail->next;
      }
      size++;
    }
    /* ************************************************************************** */
    //Clear
    template <typename Data>
    void List<Data>::Clear(){
      while(head != nullptr)
        RemoveFromFront();
    }
    /* ************************************************************************** */
    //Front Access
    template <typename Data>
    Data& List<Data>::Front() const{
      if(head == nullptr)
        throw std::length_error("Empty list!");

      return head->value;
    }
    //Back Access
    template <typename Data>
    Data& List<Data>::Back() const{
      if(tail == nullptr)
        throw std::length_error("Empty list!");

      return tail->value;
    }
    //Access for []
    template <typename Data>
	Data &List<Data>::operator[](const ulong index) const
	{
		if (index < size)
		{
			Node *tmp = head;
			for (int i = 0; i < index; ++i)
			{
				tmp = tmp->next;
			}
			return tmp->info;
		}
		else
		{
			throw std::out_of_range("Access at index " + std::to_string(index) + "; list size:" + std::to_string(size));
		}
	}
    /* ************************************************************************** */
    //List MapPostOrder
	template <typename Data>
	void List<Data>::MapPostOrder(MapFunctor function, void *parametro)
	{
		MapPostOrder(function, parametro, head);
	}
      //List MapInOrder
	template <typename Data>
	void List<Data>::MapInOrder(MapFunctor function, void *parametro)
	{
		MapInOrder(function, parametro, head);
	}

	//List FoldPreOrder
	template <typename Data>
	void List<Data>::FoldPreOrder(FoldFunctor function, const void *parametro, void *accumulatore) const
	{
		FoldPreOrder(function, parametro, accumulatore, head);
	}

	//List FoldPostOrder
	template <typename Data>
	void List<Data>::FoldPostOrder(FoldFunctor function, const void *parametro, void *accumulatore) const
	{
		FoldPostOrder(function, parametro, accumulatore, head);
	}

    //List FoldInOrder
	template <typename Data>
	void List<Data>::FoldInOrder(FoldFunctor function, const void *parametro, void *accumulatore) const
	{
		FoldInOrder(function, parametro, accumulatore, head);
	}
     //Breadht
	template <typename Data>
	void List<Data>::MapBreadht(MapFunctor function, void *parametro)
	{
		MapBreadht(function, parametro, head);
	}
    template <typename Data>
	void List<Data>::FoldBreadht(FoldFunctor function, const void *parametro, void *accumulatore) const
	{
		FoldBreadht(function, parametro, accumulatore, head);
	}
    //Specific List MapPostOrder
	template <typename Data>
	void List<Data>::MapPostOrder(MapFunctor fun, void *par, Node *curr)
	{
		if (curr != nullptr)
		{
			MapPostOrder(fun, par, curr->next);
			fun(curr->info, par);
		}
	}
    //Specific List MapInOrder
	template <typename Data>
	void List<Data>::MapInOrder(MapFunctor fun, void *par, Node *curr)
	{
		if (curr != nullptr)
		{
			MapInOrder(fun, par, curr->next);
			fun(curr->info, par);
		}
	}

	//Specific List FoldPreOrder
	template <typename Data>
	void List<Data>::FoldPreOrder(FoldFunctor fun, const void *par, void *acc, Node *curr) const
	{
		for (; curr != nullptr; curr = curr->next)
		{
			fun(curr->info, par, acc);
		}
	}
    //Specific List FoldInOrder
	template <typename Data>
	void List<Data>::FoldInOrder(FoldFunctor fun, const void *par, void *acc, Node *curr) const
	{
		if (curr != nullptr)
		{
			FoldInOrder(fun, par, acc, curr->next);
			fun(curr->info, par, acc);
		}
	}
    //Breadht
    template <typename Data>
	void List<Data>::FoldBreadht(FoldFunctor fun, const void *par, void *acc, Node *curr) const
	{
		if (curr != nullptr)
		{
			FoldBreadht(fun, par, acc, curr->next);
			fun(curr->info, par, acc);
		}
	}
    template <typename Data>
	void List<Data>::MapBreadht(MapFunctor fun, void *par, Node *curr)
	{
		if (curr != nullptr)
		{
			MapBreadht(fun, par, curr->next);
			fun(curr->info, par);
		}
	}


	/* ************************************************************************** */




}
