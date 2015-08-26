
/*****************************************************************/
/* ���ģʽ���������۲���ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.04.01
/*****************************************************************/

#pragma once

namespace linary_observer {
	typedef enum {On, Flight, Off} State;
	// ����App�ࣨObserver��
	class App {
	public:
		virtual void Update(State state) = 0;
	};

	// ����绰�ࣨSubject��
	class Phone {
	public:
		// ��װӦ��
		void Install(App * app) {
			apps.push_back(app);
		}
		// ж��Ӧ��
		void Uninstall(App * app) {
			auto iter = std::find(apps.begin(), apps.end(), app);
			if (iter != apps.end()) {
				apps.erase(iter);
			}
		}
		// �����е�App������Ϣ
		void Notify() {
			auto iter = apps.begin();
			for(; iter != apps.end(); ++iter) {
				(*iter)->Update(state);
			}
		}
		// �л��ֻ�״̬
		void SwitchState(State state) {
			this->state = state;
		}
		State GetState() const {
			return state;
		}
	protected:
		State state;
	private:
		typedef std::vector<App *> Apps;
		Apps apps;
	};

	// ����绰�ࣨConcreteSubject��
	class IPhone : public Phone {
	public:
		
	};

	// ����ʱ��App��
	class Clock : public App {
	public:
		virtual void Update(State state) {
			switch (state) {
			case On : 
				std::cout << "�绰���ڿ���״̬��";
				break;
			case Flight :
				std::cout << "�绰���ڷ���ģʽ��";
				break;
			case Off :
				std::cout << "�绰���ڹػ�״̬��";
				break;
			}
			std::cout << "ʱ�ӿ���" << std::endl;
		}
	};

	// ��������App��
	class Weather : public App {
	public:
		virtual void Update(State state) {
			switch (state) {
			case On : 
				std::cout << "�绰���ڿ���״̬����������" << std::endl;
				break;
			case Flight :
				std::cout << "�绰���ڷ���ģʽ����������" << std::endl;
				break;
			case Off :
				std::cout << "�绰���ڹػ�״̬������������" << std::endl;
				break;
			}
		}
	};	

	// ���岦����App��
	class Dialer : public App {
	public:
		virtual void Update(State state) {
			switch (state) {
			case On : 
				std::cout << "�绰���ڿ���״̬������ͨ��" << std::endl;
				break;
			case Flight :
				std::cout << "�绰���ڷ���ģʽ������ͨ��" << std::endl;
				break;
			case Off :
				std::cout << "�绰���ڹػ�״̬������ͨ��" << std::endl;
				break;
			}
		}
	};


	// ���Դ���
	static void Test_Observer() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    �۲���ģʽ����    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		IPhone  * iphone  = new IPhone();
		Weather * weather = new Weather();
		Clock	* clock	  = new Clock();
		Dialer	* dialer  = new Dialer();

		iphone->Install(weather);
		iphone->Install(clock);
		iphone->Install(dialer);
		// ����
		iphone->SwitchState(On);
		iphone->Notify();
		// �л�������ģʽ
		iphone->SwitchState(Flight);
		iphone->Notify();
		// �ػ�
		iphone->SwitchState(Off);
		iphone->Notify();

		delete dialer;
		delete clock;
		delete weather;
		delete iphone;

		std::cout << std::endl;
	}
}