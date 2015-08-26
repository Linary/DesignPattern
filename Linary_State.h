/*****************************************************************/
/* ���ģʽ��������״̬ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.06.07
/*****************************************************************/


/**	״̬ģʽ��
 */
#pragma once
#include "stdafx.h"

namespace dp_state {
	// ����״̬��
	class State {
	public:
		virtual void Handle() = 0;
	};

	// ����״̬��
	class ConcreteState : public State {
	public:
		virtual void Hanlde() {
			// ��������ʵ�ִ���
		}
	};

	// �����࣬��ӵ�ж���״̬�Ķ���
	class Context {
	public:
		// ״̬����
		void SetState(State * state) {
			this->state = state;
		}

		// ������
		void Request() {
			// ����״̬�����ҵ�񷽷�
			state->Handle();
		}
	private:
		State * state;
	};
};

namespace linary_state {
	// ����״̬��
	class State {
	public:
		State(int times) : times(times) {}
		int GetTimes() const {
			return times;
		}

		virtual void Display() = 0;
	protected:
		// ��Ļ�Ŵ���
		int times;
	};

	// ����״̬��
	class NormalState : public State {
	public:
		NormalState() : State(1) {}
		virtual void Display() {
			std::cout << "������С" <<std::endl;
		}
	};

	// 2��״̬��
	class LargerState : public State {
	public:
		LargerState() : State(2) {}
		virtual void Display() {
			std::cout << "2 ����С" <<std::endl;
		}
	};

	// 4��״̬��
	class LargestState : public State {
	public:
		LargestState() : State(4) {}
		virtual void Display() {
			std::cout << "4 ����С" <<std::endl;
		}
	};

	// ��Ļ��������
	class Screen {
	public:
		Screen() {
			// ��������״̬����
			state = new NormalState();
			state->Display();
		}
		~Screen() {
			delete state;
		}
		void SetState(State * state) {
			this->state = state;
		}
		// �����¼�����������װ�˶�״̬����ҵ�񷽷��ĵ��ú�״̬��ת��
		void OnClick() {
			State * temp = state;
			if (state->GetTimes() == 1) {
				SetState(new LargerState());
			} else if (state->GetTimes() == 2) {
				SetState(new LargestState());
			} else {
				SetState(new NormalState());
			}
			delete temp;
			this->state->Display();
		}
	private:
		// ���е�״̬��
		State * state;
	};


	// ���Դ���
	static void Test_State() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     ״̬ģʽ����     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Screen screen;
		screen.OnClick();
		screen.OnClick();
		screen.OnClick();

		std::cout << std::endl;
	}
};