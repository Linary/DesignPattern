
/*****************************************************************/
/* ���ģʽ��������������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.04.02
/*****************************************************************/
#pragma once

namespace linary_visitor {
	// ǰ������
	class Counter;
	class AppleCounter;
	class NokiaCounter;
	// �����ߡ���������
	class Consumer {
	public:
		virtual void VisitAppleCounter(AppleCounter * appleCounter) = 0;
		virtual void VisitNokiaCounter(NokiaCounter * nokiaCounter) = 0;
	};

	// ��̨����Ԫ��
	class Counter {
	public:
		// ���������ߣ������ߣ��ķ���
		virtual void Accept(Consumer * consumer) = 0;
	};

	// �����ߡ������������1
	class Buyer : public Consumer {
		virtual void VisitAppleCounter(AppleCounter * appleCounter) {
			std::cout << "������һ̨iPhone 6 Plus" << std::endl;
			// ����Ӧ����һЩ��֮��appleCounter�Ĳ���
			// ����һ����벻����ô��
			std::cout << "ƻ����̨��Ա���õģ�6288Ԫ" << std::endl;
		}

		virtual void VisitNokiaCounter(NokiaCounter * nokiaCounter) {
			std::cout << "������һ̨Lumia 925" << std::endl;
			std::cout << "ŵ���ǹ�̨��Ա���õģ�3288Ԫ" << std::endl;
		}
	};

	// �˻��ߡ������������2
	class Returner : public Consumer {
		virtual void VisitAppleCounter(AppleCounter * appleCounter) {
			std::cout << "������һ̨iPhone 6 Plus" << std::endl;
			std::cout << "ƻ����̨��Ա���õģ�����6288" << std::endl;
		}

		virtual void VisitNokiaCounter(NokiaCounter * nokiaCounter) {
			std::cout << "������һ̨Lumia 925" << std::endl;
			std::cout << "ŵ���ǹ�̨��Ա���Բ��𣬲�֧���������˻�" << std::endl;
		}
	};

	// �����ߡ������������3
	class Repairer : public Consumer {
		virtual void VisitAppleCounter(AppleCounter * appleCounter) {
			std::cout << "������һ̨iPhone 6 Plus" << std::endl;
			std::cout << "ƻ����̨��Ա������ֱ�Ӹ��㻻һ̨" << std::endl;
		}

		virtual void VisitNokiaCounter(NokiaCounter * nokiaCounter) {
			std::cout << "������һ̨Lumia 925" << std::endl;
			std::cout << "ŵ���ǹ�̨��Ա���õģ����Ҫ��������" << std::endl;
		}
	};

	// ƻ����̨��������Ԫ��1
	class AppleCounter : public Counter {
	public:
		virtual void Accept(Consumer * consumer) {
			consumer->VisitAppleCounter(this);
		}
	};
	// ŵ���ǹ�̨��������Ԫ��2
	class NokiaCounter : public Counter {
	public:
		virtual void Accept(Consumer * consumer) {
			consumer->VisitNokiaCounter(this);
		}
	};

	// �̵ꡪ�����󼯺�
	class Store {
	public:
		// �����µĹ�̨
		void Attach(Counter * counter) {
			counters.push_back(counter);
		}
		// �Ƴ�һ����̨
		void Detach(Counter * counter) {
			auto iter = std::find(counters.begin(), counters.end(), counter);
			if (iter != counters.end()) {
				if (*iter != NULL) {
					delete *iter;
				}
				// ��֪�������ɾ��������ڴ�й©
				counters.erase(iter);
			}
		}
		// �Ƴ����й�̨
		void DetachAll() {
			auto iter = counters.begin();
			for (; iter != counters.end(); ++iter) {
				if (*iter != NULL) {
					delete *iter;
				}
			}
		}
		// �ṩһ�����߲���õ��÷����߷��ʵĽӿ�
		void Accept(Consumer * consumer) {
			// �����㷨 for_each �ӷº�����֪����ô���
			// for_each(counters.begin(), counters.end(), Accept(consumer));
			auto iter = counters.begin();
			for (; iter != counters.end(); ++iter) {
				(*iter)->Accept(consumer);
			}
		}
	private:
		std::vector<Counter *> counters;
	};


	// ���Դ���
	static void Test_Visitor() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    ������ģʽ����    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Store * store = new Store();
		store->Attach(new AppleCounter());
		store->Attach(new NokiaCounter());

		Buyer * buyer = new Buyer();
		Returner * returner = new Returner();
		Repairer * repairer = new Repairer();
		store->Accept(buyer);
		store->Accept(returner);
		store->Accept(repairer);

		store->DetachAll();
		delete repairer;
		delete returner;
		delete buyer;
		delete store;

		std::cout << std::endl;
	}
}