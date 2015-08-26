/*****************************************************************/
/* ���ģʽ�����������󹤳�ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.06.12
/*****************************************************************/


/**	���󹤳�ģʽ���ṩһ������һϵ����ػ��໥��������Ľӿڣ�������ָ��
 *	���Ǿ�����ࡣ���󹤳�ģʽ�ֳ� KIT ģʽ����һ�ֶ��󴴽���ģʽ��
 *	��Ʒ�壺����һϵ�еĲ�ͬ���Ĳ�Ʒ���������ϵ����ᡣ
 *			һ����Ʒ���Ӧһ�����幤����
 *	��Ʒ�ȼ�������һϵ�еĲ�Ʒ�ȼ����������ϵĺ��ᡣ
 *			һ����Ʒ�ȼ���Ӧһ����Ʒ��
 *	˼������ģʽ�Ƿ���Ͽ���ԭ�򣬴Ӳ�Ʒ��Ͳ�Ʒ�ȼ������濼��
 */
#pragma once
#include "stdafx.h"

namespace dp_abstractfactory {
	// �����Ʒ��
	class AbstractProduct {
	public:
		// �����ƷӦ�е�ҵ�񷽷�
	};

	// �����ƷA��
	class ProductA : public AbstractProduct {
	public:
	};

	// �����ƷB��
	class ProductB : public AbstractProduct {
	public:
	};
	

	// ���󹤳�
	class AbstractFactory {
	public:
		// �����麯��Ӧ��������������
		virtual ~AbstractFactory() {}
		// ������������ƷA
		virtual ProductA * CreateProductA() = 0;
		// ������������ƷB
		virtual ProductB * CreateProductB() = 0;
	};

	// ����1
	class Factory1 : public AbstractFactory {
	public:
		// ������������ƷA
		virtual ProductA * CreateProductA() {
			return new ProductA();
		}
		// ������������ƷB
		virtual ProductB * CreateProductB() {
			return new ProductB();
		}
	};

	// ����2
	class Factory2 : public AbstractFactory {
	public:
		// ������������ƷA
		virtual ProductA * CreateProductA() {
			return new ProductA();
		}
		// ������������ƷB
		virtual ProductB * CreateProductB() {
			return new ProductB();
		}
	};
};


namespace linary_abstractfactory {
	// �����Ʒ�������Ʒ
	class DigitalProduct {
	public:
		DigitalProduct(const std::string & band) : band(band) {}
		virtual ~DigitalProduct() {}

		// ��ӡ����Ʒ��Ϣ
		virtual void ShowInfo() = 0;
	protected:
		// ���Ӳ�Ʒ��Ʒ����
		std::string band;
	};

	// �ֻ��������ƷA
	class Phone : public DigitalProduct {
	public:
		Phone(const std::string & band) : DigitalProduct(band) {}

		virtual void ShowInfo() {
			std::cout << "�ֻ�Ʒ�ƣ�" << band << std::endl;
		}
	};

	// �������������ƷB
	class Player : public DigitalProduct {
	public:
		Player(const std::string & band) : DigitalProduct(band) {}

		virtual void ShowInfo() {
			std::cout << "������Ʒ�ƣ�" << band << std::endl;
		}
	};

	// ���빫˾�����󹤳�
	class DigitalCompany {
	public:
		virtual ~DigitalCompany() {}
		// �����ֻ�
		virtual Phone * CreatePhone() = 0;
		// ����������
		virtual Player * CreatePlayer() = 0;
	};

	// ƻ����˾
	class Apple : public DigitalCompany {
	public:
		virtual Phone * CreatePhone() {
			return new Phone("IPhone 6 Plus");
		}

		virtual Player * CreatePlayer() {
			return new Player("IPod Shuffle");
		}
	};

	// ���ǹ�˾
	class Samsung : public DigitalCompany {
	public:
		virtual Phone * CreatePhone() {
			return new Phone("Note 4");
		}

		virtual Player * CreatePlayer() {
			return new Player("Altius");
		}
	};


	// ���Դ���
	static void Test_AbstractFactory() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--   ���󹤳�ģʽ����   --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		// ����һ����˾
		DigitalCompany * company = new Apple();
		// ��˾����һ���ֻ�
		Phone * phone =  company->CreatePhone();
		phone->ShowInfo();
		// ��˾����һ�����
		Player * player = company->CreatePlayer(); 
		player->ShowInfo();

		delete player;
		delete phone;
		delete company;

		std::cout << std::endl;
	}
};