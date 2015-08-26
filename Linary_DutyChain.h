/*****************************************************************/
/* ���ģʽ��������ְ����ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.06.05
/*****************************************************************/


/**	ְ����ģʽ��
 */
#pragma once
#include "stdafx.h"

// ԭ���ǣ�Chain of Responsibility��
namespace dp_dutychain {
	// �����࣬���Գ���
	class Request {
	public:
	private:
	};

	// ����������
	class Handler {
	public:
		// ���ú����
		void SetSuccessor(Handler * successor) {
			this->successor = successor;
		}
		// ��������
		virtual void Handle(Request * request) = 0;
	protected:
		// ����һ�������
		Handler * successor;
	};

	// ���崦����
	class ConcreteHandlerA : public Handler {
	public:
		virtual void Handle(Request * request) {
			// ���A�ܴ���request
				// ��������
			// ����
				// ת������
		}
	};
};

namespace linary_dutychain {
	// �ɹ�����������
	class PurchaseRequest {
	public:
		PurchaseRequest(int number, double amount, const std::string & purpose) 
			: number(number), amount(amount), purpose(purpose) {}
		// get
		int GetNumber() const {
			return number;
		}

		double GetAmount() const {
			return amount;
		}

		const std::string & GetPurpose() const {
			return purpose;
		}
	private:
		// �ɹ������
		int number;
		// �ɹ����
		double amount;
		// �ɹ�Ŀ��
		const std::string purpose;
	};

	// �������ࣺ��������
	class Approver {
	public:
		// ���캯��
		Approver(const std::string & name) : name(name), successor(NULL) {}
		// ���ú����
		void SetSuccessor(Approver * successor) {
			this->successor = successor;
		}
		// �����ɹ�������������
		virtual void Approve(PurchaseRequest * request) = 0; 
	protected:
		const std::string name; 
		Approver * successor;
	};

	// ������
	class Manager : public Approver {
	public:
		Manager(const std::string & name) : Approver(name) {}
		// ���崦�����󷽷�
		virtual void Approve(PurchaseRequest * request) {
			if (request->GetAmount() < 100000) {
				std::cout << "ִ��CEO��" << name << std::endl;
				std::cout << "������Ŀ��" << request->GetPurpose() << std::endl;
				std::cout << "��Ŀ��" << request->GetAmount() << "Ԫ" << std::endl;
			} else {
				// ת������
				successor->Approve(request);
			}
		}
	};

	// ������
	class President : public Approver {
	public:
		President(const std::string & name) : Approver(name) {}
		// ���崦�����󷽷�
		virtual void Approve(PurchaseRequest * request) {
			if (request->GetAmount() < 500000) {
				std::cout << "��	����ϯ��" << name << std::endl;
				std::cout << "������Ŀ��" << request->GetPurpose() << std::endl;
				std::cout << "��Ŀ��" << request->GetAmount() << "Ԫ" << std::endl;
			} else {
				// ת������
				successor->Approve(request);
			}
		}
	};

	// ���»���
	class Congress : public Approver {
	public:
		Congress(const std::string & name) : Approver(name) {}
		// ���崦�����󷽷�
		virtual void Approve(PurchaseRequest * request) {
			// ���һ����������ת��
			std::cout << "���»᣺" << name << std::endl;
			std::cout << "������Ŀ��" << request->GetPurpose() << std::endl;
			std::cout << "��Ŀ��" << request->GetAmount() << "Ԫ" << std::endl;
		}
	};


	// ���Դ���
	static void Test_DutyChain() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    ������ģʽ����    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Approver * lzx = new Manager("½����");
		Approver * my = new President("����");
		Approver * meeting = new Congress("�ɶ����");

		lzx->SetSuccessor(my);
		my->SetSuccessor(meeting);

		// �½��ɹ���
		PurchaseRequest * pr1 = new PurchaseRequest(10000, 99998.0, "��ɵεδ�");
		// ���ȶ���CEO������
		lzx->Approve(pr1);

		PurchaseRequest * pr2 = new PurchaseRequest(10002, 468000.0, "��ɹ��ݺ��");
		lzx->Approve(pr2);

		PurchaseRequest * pr3 = new PurchaseRequest(10003, 800000.0, "�ջ�3000���");
		lzx->Approve(pr3);

		delete pr3;
		delete pr2;
		delete pr1;
		delete meeting;
		delete my;
		delete lzx;

		std::cout << std::endl;
	}
};