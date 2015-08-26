
/*****************************************************************/
/* ���ģʽ��������װ��ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.04.01
/*****************************************************************/

#pragma once

namespace linary_decorator {
	// ����绰�࣬����ڳ��������
	class Phone {
	public:
		// ����Ӧ�õķ���
		virtual void Run() = 0; 
	};

	// ����绰��
	class IPhone : public Phone {
	public:
		virtual void Run() {
			std::cout << "��ӭʹ��IPhone" << std::endl;
		}
	};

	// ����Ӧ���࣬����ڳ���װ������
	class App : public Phone {
	public:
		// ��ʾ��App��װ���ֻ���
		void InstallOn(Phone * phone) {
			this->phone = phone;
		}
		virtual void Run() {
			if (phone != NULL) {
				phone->Run();
			}
		}
	protected:
		Phone * phone;
	};

	// ����Ӧ����
	class Douban : public App {
	public:
		virtual void Run() {
			App::Run();
			SearchMovie();
		}
	private:
		void SearchMovie() {
			std::cout << "������ʹ�ö���������Ӱ" << std::endl;
		}
	};

	// ����Ӧ����
	class Wechat : public App {
	public:
		virtual void Run() {
			App::Run();
			Chat();
		}
	private:
		void Chat() {
			std::cout << "������ʹ��΢������" << std::endl;
		}
	};
	
	// ���Դ���
	static void Test_Decorator() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     װ��ģʽ����     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		IPhone * iphone = new IPhone();
		Douban * douban = new Douban();
		Wechat * wechat = new Wechat();

		douban->InstallOn(iphone);
		wechat->InstallOn(douban);
		wechat->Run();

		delete wechat;
		delete douban;
		delete iphone;

		std::cout << std::endl;
	}
}