/*****************************************************************/
/* ���ģʽ��������������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.06.11
/*****************************************************************/


/**	������ģʽ��
 */
#pragma once
#include "stdafx.h"

// ��������C++��type_traits������ʵ��������STL�ĵ�����

namespace linary_iterator {
	template <typename T>
	class Iterator;

	template <typename T>
	class VectorIterator;

	// ���󼯺���
	template <typename T = int>
	class Collection {
	public:
		virtual ~Collection() {}
		virtual Iterator<T> * GetIterator() = 0;
		// ��ӣ��Ƴ�Ԫ�صĲ���
		virtual bool Add(const T & elem) = 0;
		// �Ƴ��������д
		virtual void Remove(int idx) = 0;
	};

	// ���弯����
	template <typename T>
	class Vector : public Collection<T> {
	public:
		Vector(int size) : cur(0), size(size) {
			ptr = new T[size];
		}
		~Vector() {
			delete []ptr;
		}

		virtual Iterator<T> * GetIterator() {
			return new VectorIterator<T>(*this);
		}

		// ���Ԫ��
		virtual bool Add(const T & elem) {
			if (cur < size) {
				*(ptr + cur) = elem;
				++cur;
				return true;
			} else {
				return false;
			}
		}

		// �Ƴ�Ԫ��
		virtual void Remove(int idx) {
			if (0 <= idx && idx <= cur) {
				*(ptr + idx--) = T();
			}
		}

		// ���ؼ��ϴ�С
		int Size() const {
			return size;
		}
		// ���ؼ�������Ԫ�ظ���
		int Count() const {
			return cur;
		}
		// ����[]������
		T & operator[](int idx) {
			return *(ptr + idx);
		}
	private:
		T * ptr;
		int cur;
		int size;
	};

	// �����������
	template <typename T>
	class Iterator {
	public:
		virtual ~Iterator() {}
		// ����Ԫ�صĲ���
		virtual bool Begin() = 0;
		virtual bool End() = 0;
		virtual void Last() = 0;
		virtual void Next() = 0;
		virtual T & Item() = 0;
	};

	// �����������
	template <typename T>
	class VectorIterator : public Iterator<T> {
	public:
		VectorIterator(Vector<T> & coll) : coll(coll), pivot(0) {}

		virtual bool Begin() {
			return pivot == 0;
		}
		virtual bool End() {
			return pivot == coll.Count();
		}
		virtual void Last() {
			if (pivot > 0) {
				--pivot;
			}
		}
		virtual void Next() {
			if (pivot < coll.Size()) {
				++pivot;
			}
		}
		virtual T & Item() {
			return coll[pivot];
		}
	private:
		// ����һ������ļ��϶���
		Vector<T> coll;
		// ����һ���α꣨����ָ���ã�
		int pivot;
	};


	// ���Դ���
	static void Test_Iterator() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    ������ģʽ����    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Vector<std::string> books(5); 
		books.Add("�������");
		books.Add("���Ӣ�۴�");
		books.Add("Ц������");

		Iterator<std::string> * it = books.GetIterator();
		std::cout << "-->�������..." << std::endl;
		while (!it->End()) {
			std::cout << it->Item() << std::endl;
			it->Next();
		}
		std::cout<< "<--�������..." << std::endl;
		while (!it->Begin()) {
			it->Last();
			std::cout << it->Item() << std::endl;
			
		}

		std::cout << std::endl;
	}
};