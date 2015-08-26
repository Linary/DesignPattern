/*****************************************************************/
/* ���ģʽ���������н���ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.05.30
/*****************************************************************/

#pragma once
#include "stdafx.h"

/**	�н���ģʽ����һ���н��������װһϵ�еĶ��󽻻���
 *	Ч����ʹ�ø�������Ҫ��ʾ���໥���ã��Ӷ�ʹ�������ɢ�����ҿ��Զ����ظı�����֮��Ľ�����
 */

namespace dp_mediator {
	
	// ǰ������
	class Subject;

	// �����н���
	class Mediator {
	public:
		// ����ķ���ֻ�Ǿٸ����ӣ���ʾ�н���ת����Ϣ
		virtual void Transfer(const std::string & msg, Subject * subject) = 0;
	};

	// ����Ŀ����
	// ��ʵ���������û�б�Ҫ����Ϊ�����Ŀ���������ɲ�ͬ��ҵ���߼���
	class Subject {
	public:
		// ���췽�����õ��н��߶���
		Subject(Mediator * mediator) {
			this->mediator = mediator;
		}

	protected:
		Mediator * mediator;
	};

	// ����Ŀ��1
	class ConcreteSubject1 : public Subject {
	public:
		// ���캯�������н���
		ConcreteSubject1(Mediator * mediator) : Subject(mediator) {}

		// ע�⣺������������ȻĿ��1��Ŀ��2��ҵ���߼�������ȫ��һ�������У�
		// ����ʵ�����������������ģ����Բ�Ҫ������ڸ�����
		void SendMsg(const std::string & msg) {
			std::cout << "Ŀ��1��" << msg << std::endl;
			mediator->Transfer(msg, this);
		}

		void RecvMsg(const std::string & msg) {
			std::cout << "Ŀ��1���յ���Ϣ" << std::endl;
		}
	};

	// ����Ŀ��2��ע�⣺��ʵĿ��2��Ŀ��1����û�й��ԣ�
	class ConcreteSubject2 : public Subject {
	public:
		// ���캯�������н���
		ConcreteSubject2(Mediator * mediator) : Subject(mediator) {}

		void SendMsg(const std::string & msg) {
			std::cout << "Ŀ��2��" << msg << std::endl;
			mediator->Transfer(msg, this);
		}

		void RecvMsg(const std::string & msg) {
			std::cout << "Ŀ��2���յ���Ϣ" << std::endl;
		}
	};

	// �����н���
	class ConcreteMediator : public Mediator {
	public:
		// ���ﲻ���ù��췽�����棬�����ⲿû����ʼ��
		void SetConcreteSubject1(ConcreteSubject1 * subject1) {
			this->subject1 = subject1;
		}

		void SetConcreteSubject2(ConcreteSubject2 * subject2) {
			this->subject2 = subject2;
		}

		// ת����Ϣ
		void Transfer(const std::string & msg, Subject * subject) {
			if (subject == subject1) {
				subject2->RecvMsg(msg);
			} else {
				subject1->RecvMsg(msg);
			}
		}

	private:
		ConcreteSubject1 * subject1;
		ConcreteSubject2 * subject2;
	};


	// ���Դ���
	static void Test_Mediator() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    �н���ģʽ����    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		ConcreteMediator * mediator = new ConcreteMediator();
		// ������������ͨ�ŵĶ���
		ConcreteSubject1 * subject1 = new ConcreteSubject1(mediator);
		ConcreteSubject2 * subject2 = new ConcreteSubject2(mediator);
		// ָ���н�����Ҫ��ͣ�Ķ���
		mediator->SetConcreteSubject1(subject1);
		mediator->SetConcreteSubject2(subject2);

		subject1->SendMsg("������һ̨IPhone 7");
		subject2->SendMsg("�Բ��𣬻�û������");

		delete subject2;
		delete subject1;
		delete mediator;

		std::cout << std::endl;
	}
};


namespace linary_mediator {

	class User;

	// �������ƽ̨
	class OnlineStore {
	public:
		// չʾ��Ʒ
		virtual void ShowGoods(User * user) = 0;
	};


	class User {
	protected:
		OnlineStore * store;
	};

	// ��Ʒ������
	class Vendor : public User {
	public:
		// �������
		void ApplyJoining(OnlineStore * store) {
			std::cout << "�����̣�������ס��è�̳�" << std::endl;
			this->store = store;
		}

		// ������Ʒ
		void PutGoods() {
			store->ShowGoods(this);
		};
	};

	// �˿�
	class Consumer : public User {
	public:
		// ���̳�
		void VisitStore(OnlineStore * store) {
			std::cout << "�˿ͣ�������è" << std::endl;
			this->store = store;
		}

		// ѡ����Ʒ
		void BuyGoods() {
			store->ShowGoods(this);
		}
	};

	

	// �����̳�
	class TMall : public OnlineStore {
	public:
		void AcceptJoining(Vendor * vendor) {
			std::cout << "��è�̳ǣ�������ס" << std::endl;
			this->vendor = vendor;
		}

		void GreetConsumer(Consumer * consumer) {
			std::cout << "��è�̳ǣ���ӭѡ��" << std::endl;
			this->consumer = consumer;
		}

		void ShowGoods(User * user) {
			if (user == vendor) {
				std::cout << "��è�̳�չ����������Ʒ" << std::endl;
			} else {
				std::cout << "��è�̳ǹ��û�ѡ����Ʒ" << std::endl;
			}
		}
	private:
		Vendor * vendor;
		Consumer * consumer;
	};


	// ���Դ���
	static void Test_Mediator() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    �н���ģʽ����    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		TMall * tmall = new TMall();
		// �����̺͹˿�
		Vendor * vendor = new Vendor();
		Consumer * consumer = new Consumer();
		// ������������ס��è�̳�
		vendor->ApplyJoining(tmall);
		// ��è�̳�������ס
		tmall->AcceptJoining(vendor);
		// չ����Ʒ
		vendor->PutGoods();
		// �˿ͷ�����è
		consumer->VisitStore(tmall);
		// ��è�̳ǻ�ӭ�˿�
		tmall->GreetConsumer(consumer);
		consumer->BuyGoods();
		

		delete consumer;
		delete vendor;
		delete tmall;

		std::cout << std::endl;
	}
};