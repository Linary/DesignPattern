/*****************************************************************/
/* ���ģʽ������������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.05.29
/*****************************************************************/

#pragma once
#include "stdafx.h"
namespace linary_sigleton {

	// Ӧ����
	class App {
	public:
		virtual void Run() = 0;
	};

	// ΢���� 
	class WeChat : public App {
	public:
		static WeChat * GetWeChatInstance() {
			if (m_instance == NULL) {
				m_instance = new WeChat();
			}
			return m_instance;
		}

		void Run() {
			std::cout << "΢����������..." << std::endl;
		}
	protected:
		WeChat() {}
	private:
		static WeChat * m_instance;
	};
	WeChat * WeChat::m_instance = NULL;


	// ֪����
	class ZhiHu : public App {
	public:
		static ZhiHu * GetZhiHuInstance() {
			if (m_instance == NULL) {
				m_instance = new ZhiHu();
			}
			return m_instance;
		}

		void Run() {
			std::cout << "֪����������..." << std::endl;
		}
	protected:
		ZhiHu() {}
	private:
		static ZhiHu * m_instance;
	};
	ZhiHu * ZhiHu::m_instance = NULL;


	// ���м�����̬����
	class IPhone {
	public:
		IPhone() {
			std::cout << "IPhone�ѽ���" << std::endl;
		}

		// �򵥹���ģʽ
		App * GetAppInstance(const std::string & app) {
			if (app == "wechat") {
				return WeChat::GetWeChatInstance();
			} else if (app == "zhihu") {
				return ZhiHu::GetZhiHuInstance();
			} else {
				return NULL;
			}
		}
	};


	// ���Դ���
	static void Test_Singleton() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     ����ģʽ����     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		IPhone * iPhone = new IPhone();
		WeChat * wechat = WeChat::GetWeChatInstance();
		wechat->Run();
		ZhiHu  * zhihu  = ZhiHu::GetZhiHuInstance();
		zhihu->Run();

		delete zhihu;
		delete wechat;
		delete iPhone;
		std::cout << std::endl;
	}
};