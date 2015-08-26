/*****************************************************************/
/* ���ģʽ������������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.05.26
/*****************************************************************/


/**	����ģʽ���������ʵ�ֽ��ʹ�����߿��Զ����仯
 *	һ��ʵ��ϵͳ�ܴӶ���Ƕ�ȥ���࣬ÿ�ַ��඼���ܱ仯��
 *	�ǾͰ����ֶ�Ƕȷ�����������Ƕ����仯
 */
#pragma once

namespace linary_bridge {
	/**
	 *	ƻ���ֻ�Ӳ�����ò��ߣ�������ϵͳ�ã������ֻ�Ӳ�����øߣ�������ϵͳ��
	 *	�������������仯�����ֻ�Ʒ�ƣ�Ӳ��������ϵͳ
	 */

	class Hardware {
	public:
		// Ӳ������Ҫ���ֻ�����
		virtual void BeCarried() = 0; 
	};


	class OperSystem {
	public:
		// ����ϵͳ����������
		virtual void Run() = 0;
	};

	// ����
	class PhoneBrand {
	public:
		//PhoneBrand() {}
		PhoneBrand(Hardware * hardware, OperSystem * operSystem) {
			this->hardware = hardware;
			this->operSystem = operSystem;
		}
		// �������Ϊ
		void Use() {
			hardware->BeCarried();
			operSystem->Run();
		}
	private:
		Hardware * hardware; 
		OperSystem * operSystem;
	};

	// һ���Ӳ������
	class CommonHardware : public Hardware {
	public:
		void BeCarried() {
			std::cout << "1G RAM��Apple A7 CPU" << std::endl;
		}
	};

	// �߶˵�Ӳ������
	class AdvancedHardware : public Hardware {
	public:
		void BeCarried() {
			std::cout << "4G RAM����ͨ X7500 CPU" << std::endl;
		}
	};

	// IOS����ϵͳ
	class IOS : public OperSystem {
	public:
		void Run() {
			std::cout << "�����������޿���" << std::endl;
		}
	};

	// Android����ϵͳ
	class Android : public OperSystem {
		void Run() {
			std::cout << "���о�������" << std::endl;
		}
	};

	// ƻ���ֻ�
	class IPhone : public PhoneBrand {
	public:
		// �����ض����͵Ĳ��������ø��๹�췽��
		IPhone(CommonHardware * hardware, IOS * operSystem) : PhoneBrand(hardware, operSystem){}

		void Use() {
			// ���������ʹ����Ϊ
			PhoneBrand::Use();
			std::cout << "ƻ���û��ܿ���" << std::endl;
		}
	};

	// �����ֻ�
	class Note4 : public PhoneBrand {
	public:
		// �����ض����͵Ĳ��������ø��๹�췽��
		Note4(AdvancedHardware * hardware, Android * operSystem) : PhoneBrand(hardware, operSystem) {}
			
		void Use() {
			// ���������ʹ����Ϊ
			PhoneBrand::Use();
			std::cout << "��׿�û��ܷ�ŭ" << std::endl;
		}
	};


	// ���Դ���
	static void Test_Bridge() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     �Ž�ģʽ����     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		// ����ʵ�ֻ���ɫ
		CommonHardware * commonHardware = new CommonHardware();
		AdvancedHardware * advancedHardware = new AdvancedHardware();

		IOS * ios = new IOS();
		Android * android = new Android();

		// ������󻯽�ɫ
		IPhone * iPhone = new IPhone(commonHardware, ios);
		Note4 * note4 = new Note4(advancedHardware, android);

		iPhone->Use();
		note4->Use();

		delete note4;
		delete iPhone;
		delete android;
		delete ios;
		delete advancedHardware;
		delete commonHardware;

		std::cout << std::endl;
	}
};