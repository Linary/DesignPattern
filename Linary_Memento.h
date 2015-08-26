/*****************************************************************/
/* ���ģʽ������������¼ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.06.02
/*****************************************************************/


/**	����¼ģʽ���ڲ��ƻ���װ�Ե�ǰ���£�����һ��������ڲ�״̬�����ڸ�
 *	����֮�Ᵽ�����״̬�������������Ժ󽫶���ָ���֮ǰ�����״̬��
 */
#pragma once
#include "stdafx.h"
namespace linary_memento {

	// ����¼��
	class Memento {
	public:
		Memento(const std::string & label, int x, int y) : label(label), x(x), y(y) {}

		// ȫ��get/set����
		void SetLabel(const std::string & label) {
			this->label = label;
		}

		std::string GetLabel() const {
			return this->label;
		}

		void SetX(int x) {
			this->x = x;
		}

		int GetX() const {
			return this->x;
		}

		void SetY(int y) {
			this->y = y;
		}

		int GetY() const {
			return this->y;
		}
	private:
		std::string label;
		int x;
		int y;
	};


	// �����࣬�䵱ԭ����
	class Chess {
	public:
		Chess(const std::string & label, int x, int y) : label(label), x(x), y(y) {}

		// ȫ��get/set����
		void SetLabel(const std::string & label) {
			this->label = label;
		}

		std::string GetLabel() const {
			return this->label;
		}

		void SetX(int x) {
			this->x = x;
		}

		int GetX() const {
			return this->x;
		}

		void SetY(int y) {
			this->y = y;
		}

		int GetY() const {
			return this->y;
		}

		// ��ӡ����״̬
		void Print() const {
			std::cout << "���� " << label << " λ�� " << x << " �� " << y << " ��" << std::endl;
		}

		// ����״̬
		Memento * Save() {
			return new Memento(label, x, y);
		}

		// �ָ�״̬
		void Restore(Memento * memento) {
			this->label = memento->GetLabel();
			this->x = memento->GetX();
			this->y = memento->GetY();
		}
	private:
		std::string label;
		int x;
		int y;
	};


	// ����¼�������࣬�д���չ��ʵ�ֶಽ�������Լ�ȡ������
	class CareTaker {
	public:
		CareTaker() : memento(NULL) {}

		// ������״̬ʱ���ǵð�֮ǰ�Ķ�������
		void SetMemento(Memento * memento) {
			if (this->memento != NULL) {
				delete this->memento;
			}
			this->memento = memento;
		}

		Memento * GetMemento() const {
			return this->memento;
		}
	private:
		Memento * memento;
	};


	// ���Դ���
	static void Test_Memento() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    ����¼ģʽ����    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		CareTaker careTaker;
		Chess * chess = new Chess("��", 1, 1);
		chess->Print();
		// ����״̬
		careTaker.SetMemento(chess->Save());
		chess->SetX(4);
		chess->Print();
		// ����״̬
		careTaker.SetMemento(chess->Save());
		chess->SetY(6);
		chess->Print();
		// �ָ�״̬
		chess->Restore(careTaker.GetMemento());
		chess->Print();

		delete chess;
		std::cout << std::endl;
	}
};