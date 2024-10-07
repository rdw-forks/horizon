/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla <sagunxp@gmail.com>
 *
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/


#define BOOST_TEST_MODULE "ReferenceTypeListTest"

#include "Core/Structures/LinkedList/ReferenceList/Reference.hpp"
#include "Core/Structures/LinkedList/ReferenceList/RefManager.hpp"
#include "Core/Structures/TypeList.hpp"

#include <boost/test/unit_test.hpp>
#include <cstring>
#include <iostream>
#include <cassert>

template <class OBJECT>
class TestReference;

template <class OBJECT>
class TestRefManager : public Horizon::Structures::LinkedList::RefManager<TestRefManager<OBJECT>, OBJECT>
{
public:
	typedef Horizon::Structures::LinkedList::Head::Iterator<TestReference<OBJECT>> iterator;

	TestReference<OBJECT> *first()
	{
		return static_cast<TestReference<OBJECT> *> (Horizon::Structures::LinkedList::RefManager<TestRefManager<OBJECT>, OBJECT>::first());
	}
	TestReference<OBJECT> const *first() const
	{
		return static_cast<TestReference<OBJECT> const *> (Horizon::Structures::LinkedList::RefManager<TestRefManager<OBJECT>, OBJECT>::first());
	}

	iterator begin() { return iterator(first()); }
};

template <class OBJECT>
class TestReference : public Horizon::Structures::LinkedList::Reference<TestRefManager<OBJECT>, OBJECT>
{
public:
    TestReference() : Horizon::Structures::LinkedList::Reference<TestRefManager<OBJECT>, OBJECT>()
    {
    	//
    }
    ~TestReference() override { this->remove(); }
    TestReference *next()
    {
    	return (TestReference *) Horizon::Structures::LinkedList::Reference<TestRefManager<OBJECT>, OBJECT>::next();
    }

protected:
    void target_object_build_link() override
    {
        // called from link()
        this->target()->push_front(this);
        this->target()->inc_size();
    }
    void target_object_destroy_link() override
    {
        // called from erase()
        if (this->is_valid())
        	this->target()->dec_size();
    }
    void source_object_destroy_link() override
    {
        // called from invalidate()
        this->target()->dec_size();
    }
};

template<class T>
class ReferenceObject
{
public:
	virtual ~ReferenceObject() { }

    bool is_valid() const { return _ref.is_valid(); }
    void add_reference(TestRefManager<T> &m) { assert(!is_valid()); _ref.link(&m, (T*) this); }
    void remove_reference() { assert(is_valid()); _ref.remove(); }

	TestReference<T> &get_reference() { return _ref; }

private:
	TestReference<T> _ref;
};

class GenericTestObject
{
public:
	GenericTestObject(int id, char type) : _id(id), _type(type) { }

	virtual int get_id() { return _id; }
	virtual void set_id(int id) { _id = id; }

	char get_type() { return _type; }

private:
	int _id;
	char _type;
};

/*============================*
 * Subjects
 *============================*/
class A : public ReferenceObject<A>, public GenericTestObject
{
public:
	A(int id = 0) : GenericTestObject(id, 'A') { }
};

class B : public ReferenceObject<B>, public GenericTestObject
{
public:
	B(int id = 0) : GenericTestObject(id, 'B') { }
};

class C : public ReferenceObject<C>, public GenericTestObject
{
public:
	C(int id = 0) : GenericTestObject(id, 'C') { }
};

/*============================*
 * Container Data Type
 *============================*/
template<class OBJECT>
struct ContainerMapList
{
	TestRefManager<OBJECT> _element;
};

template<>
struct ContainerMapList<TypeNull>
{
};

template<class HEAD, class TAIL>
struct ContainerMapList<TypeList<HEAD, TAIL>>
{
	ContainerMapList<HEAD> _elements;
	ContainerMapList<TAIL> _tail_elements;
};

/*============================*
 * TypeListIterator Insert Functions
 *============================*/
// non-const insert functions
namespace TypeListIterator
{
	// Invoked in the condition that the SPECIFIC_TYPE has been visited.
	template<class SPECIFIC_TYPE>
	SPECIFIC_TYPE *Insert(ContainerMapList<SPECIFIC_TYPE> &elements, SPECIFIC_TYPE *obj)
	{
		obj->add_reference(elements._element);
		return obj;
	}
	// Invoked in the condition that a TypeNull has been visited.
	template<class SPECIFIC_TYPE>
	SPECIFIC_TYPE *Insert(ContainerMapList<TypeNull> &/*elements*/, SPECIFIC_TYPE */*obj*/)
	{
		return nullptr;
	}
	// In a case such as the following, where the ContainerMapList is not one of the specific type
	// that we are in search of, the resulting return of the function is a nullptr. 
	template<class SPECIFIC_TYPE, class T>
	SPECIFIC_TYPE *Insert(ContainerMapList<T> &/*elements*/, SPECIFIC_TYPE */*obj*/)
	{
		return nullptr;
	}
	// In a condition such as the following where a ContainerMapList of a TypeList<HEAD, TAIL> is invoked,
	// and the specific object that is to be inserted is also a valid argument. The function definition matches the 
	// search criteria of the template function that is to be invoked. We try recursing to iterate through the TypeLists
	// contained in the ContainerMapList until a reference has been added or the end of the TypeList (TypeNull) is met and the 
	// appropriate function has been invoked to return a nullptr or a valid pointer to the object.
	template<class SPECIFIC_TYPE, class HEAD, class TAIL>
	SPECIFIC_TYPE* Insert(ContainerMapList<TypeList<HEAD, TAIL>> &elements, SPECIFIC_TYPE* obj)
	{
		SPECIFIC_TYPE *t = Insert(elements._elements, obj);
		return (t != nullptr ? t : Insert(elements._tail_elements, obj));
	}
/*============================*
 * TypeListIterator Count Functions
 *============================*/
	// Function for when the specific type has been invoked and the requirement of meeting the function
	// definition has been successful.
	template <class SPECIFIC_TYPE>
	size_t count(ContainerMapList<SPECIFIC_TYPE> const &elements, SPECIFIC_TYPE */*fake*/)
	{
		return elements._element.get_size();
	}
	// Function for when a TypeNull has been visited.
	template <class SPECIFIC_TYPE>
	size_t count(ContainerMapList<TypeNull> const &/*elements*/, SPECIFIC_TYPE */*fake*/)
	{
		return 0;
	}
	// Function containing any other type than the one we are in search of, will be invoked.
	template <class SPECIFIC_TYPE, class T>
	size_t count(ContainerMapList<T> const &/*elements*/, SPECIFIC_TYPE */*fake*/)
	{
		return 0;
	}
	// Invoked in the condition that the a TypeList of type <SPECIFIC_TYPE, T> has been met. 
	template <class SPECIFIC_TYPE, class T>
	size_t count(ContainerMapList<TypeList<SPECIFIC_TYPE, T>> const &elements, SPECIFIC_TYPE *fake)
	{
		return count(elements._elements, fake);
	}
	// Invoked in the condition that any other TypeList, the ones that are not of the SPECIFIC_TYPE.
	// All of the element types will be visited, invoking the count() function 
	// for the specific type we are in search of.
	template <class SPECIFIC_TYPE, class H, class T>
	size_t count(ContainerMapList<TypeList<H, T>> const &elements, SPECIFIC_TYPE *fake)
	{
		return count(elements._tail_elements, fake);
	}

	template <class TypeNull>
	size_t count_all(ContainerMapList<TypeNull> const &elements)
	{
		return 0;
	}

	// Counts all of the objects in a GridTypeListContainer.
	template <class H, class T>
	size_t count_all(ContainerMapList<TypeList<H, T>> const &elements)
	{
		return count(elements._elements, (H *) nullptr) + count_all(elements._tail_elements);
	}
}
/*============================*
 * TypeRefContainer
 *============================*/
template<class OBJECT_TYPES>
class TypeRefContainer
{
public:

	template <class SPECIFIC_TYPE>
	size_t count() const
	{
		return TypeListIterator::count(_elements, (SPECIFIC_TYPE *) nullptr);
	}

	size_t count_all() const
	{
		return TypeListIterator::count_all(_elements);
	}

	/// inserts a specific object into the container
	template <class SPECIFIC_TYPE>
	bool insert(SPECIFIC_TYPE *obj)
	{
		assert(!obj->is_valid());
		SPECIFIC_TYPE* t = TypeListIterator::Insert(_elements, obj);
		return (t != nullptr);
	}

	ContainerMapList<OBJECT_TYPES> &get_elements(void) { return _elements; }
	const ContainerMapList<OBJECT_TYPES> &get_elements(void) const { return _elements;}

private:
	ContainerMapList<OBJECT_TYPES> _elements;
};

/*============================*
 * Visitor Helper Functions
 *============================*/
template<class VISITOR>
void VisitorHelper(VISITOR &/*v*/, ContainerMapList<TypeNull> &/*c*/)
{
	// terminate condition container map list
}

template<class VISITOR, class T>
void VisitorHelper(VISITOR &v, ContainerMapList<T> &c)
{
	v.Visit(c._element);
}

// recursion container map list
template<class VISITOR, class H, class T>
void VisitorHelper(VISITOR &v, ContainerMapList<TypeList<H, T>> &c)
{
	VisitorHelper(v, c._elements); // template<class OBJECT> struct ContainerMapList
	VisitorHelper(v, c._tail_elements); // template<class HEAD, class TAIL> struct ContainerMapList<TypeList<HEAD, TAIL>>
}

// for TypeRefContainer
template<class VISITOR, class OBJECT_TYPES>
void VisitorHelper(VISITOR &v, TypeRefContainer<OBJECT_TYPES> &c)
{
	VisitorHelper(v, c.get_elements());
}

/*============================*
 * TypeContainerVisitor
 *============================*/
template<class VISITOR, class TYPE_CONTAINER>
class TypeContainerVisitor
{
public:
	TypeContainerVisitor(VISITOR &v) : _visitor(v) { }

	void Visit(TYPE_CONTAINER &c)
	{
		VisitorHelper(_visitor, c);
	}

	void Visit(const TYPE_CONTAINER &c) const
	{
		VisitorHelper(_visitor, c);
	}

private:
	VISITOR &_visitor;
};

/*============================*
 * Defines
 *============================*/
typedef TYPELIST_3(A, B, C) MyTypes;

#define MAX_A_TYPES 3
#define MAX_B_TYPES 6
#define MAX_C_TYPES 9

void print_count(TypeRefContainer<MyTypes> &refContainer)
{
	std::cout << "A: " << refContainer.count<A>()
	<< " | B: " << refContainer.count<B>()
	<< " | C: " << refContainer.count<C>() << std::endl;

	std::cout << "Total of " << refContainer.count_all() << " elements created." << std::endl;
}

/*============================*
 * Checkers
 *============================*/
class CompareGenericTestObjectID
{
public:
	CompareGenericTestObjectID(int id)
	: _id(id) { }

	bool operator()(GenericTestObject *obj)
	{
		if (obj->get_id() == _id) {
			return true;
		}
		return false;
	}

private:
	int _id;
};

/*============================*
 * Searchers
 *============================*/
template<class PREDICATE>
struct GenericTestObjectSearcher
{
	GenericTestObject *&_object;
	PREDICATE &_check;

	GenericTestObjectSearcher(GenericTestObject *&result, PREDICATE &check)
	: _object(result), _check(check) { }

	template <class T>
	inline void perform_on(TestRefManager<T> &m)
	{
		if (_object != nullptr)
			return;

		for (typename TestRefManager<T>::iterator it = m.begin(); it != typename TestRefManager<T>::iterator(nullptr); it++)
			if (_check(it->source())) {
				_object = it->source();
				break;
			}
	}

	void Visit(TestRefManager<A> &m) { perform_on<A>(m); }
	void Visit(TestRefManager<B> &m) { perform_on<B>(m); }
	void Visit(TestRefManager<C> &m) { perform_on<C>(m); }

	template<class NOT_INTERESTED>
	void Visit(TestRefManager<NOT_INTERESTED> &) { }
};

/*============================*
 * Main
 *============================*/
BOOST_AUTO_TEST_CASE(ReferenceTypeListTest)
{
	TypeRefContainer<MyTypes> refContainer;

	A *a[MAX_A_TYPES];
	B *b[MAX_B_TYPES];
	C *c[MAX_C_TYPES];

	print_count(refContainer);

	int aids[] = { 11, 21, 36 };
	for (int i = 0; i < MAX_A_TYPES; i++) {
		a[i] = new A(aids[i]);
		refContainer.template insert<A>(a[i]);
		assert(a[i]->is_valid());
	}

	BOOST_CHECK_EQUAL(refContainer.count<A>(), MAX_A_TYPES);
	BOOST_CHECK_EQUAL(refContainer.count<B>(), 0);
	BOOST_CHECK_EQUAL(refContainer.count<C>(), 0);

	int bids[6] = { 12, 22, 37, 42, 51, 62 };
	for (int i = 0; i < MAX_B_TYPES; i++) {
		b[i] = new B(bids[i]);
		refContainer.template insert<B>(b[i]);
		assert(b[i]->is_valid());
	}
	BOOST_CHECK_EQUAL(refContainer.count<A>(), MAX_A_TYPES);
	BOOST_CHECK_EQUAL(refContainer.count<B>(), MAX_B_TYPES);
	BOOST_CHECK_EQUAL(refContainer.count<C>(), 0);

	int cids[9] = { 13, 23, 38, 43, 52, 63, 71, 87, 99 };
	for (int i = 0; i < MAX_C_TYPES; i++) {
		c[i] = new C(cids[i]);
		refContainer.template insert<C>(c[i]);
		assert(c[i]->is_valid());
	}

	BOOST_CHECK_EQUAL(refContainer.count<A>(), MAX_A_TYPES);
	BOOST_CHECK_EQUAL(refContainer.count<B>(), MAX_B_TYPES);
	BOOST_CHECK_EQUAL(refContainer.count<C>(), MAX_C_TYPES);

	print_count(refContainer);

	/**
	 * Searcher & Checker tests.
	 */
#define ID_CHECK 42
	GenericTestObject *res = nullptr;
	CompareGenericTestObjectID check(ID_CHECK);
	GenericTestObjectSearcher<CompareGenericTestObjectID> searcher(res, check);
	TypeContainerVisitor<GenericTestObjectSearcher<CompareGenericTestObjectID>, TypeRefContainer<MyTypes>>  id_searcher(searcher);
	id_searcher.Visit(refContainer);

	BOOST_CHECK_EQUAL(res->get_id(), ID_CHECK);

	//printf("Found res of type %c id %d\n", res->get_type(), res->get_id());

	for (int i = 0; i < MAX_A_TYPES; i++) {
		a[i]->remove_reference();
		delete a[i];
	}
	for (int i = 0; i < MAX_B_TYPES; i++) {
		b[i]->remove_reference();
		delete b[i];
	}
	for (int i = 0; i < MAX_C_TYPES; i++) {
		c[i]->remove_reference();
		delete c[i];
	}
#undef ID_CHECK

	BOOST_CHECK_EQUAL(refContainer.count<A>(), 0);
	BOOST_CHECK_EQUAL(refContainer.count<B>(), 0);
	BOOST_CHECK_EQUAL(refContainer.count<C>(), 0);

	print_count(refContainer);
}
