/*****************************************************************/
/* ���ģʽ����������������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.06.12
/*****************************************************************/


/**	��������ģʽ������һ�����ڴ�������Ľӿڣ��������������һ����ʵ������
 *	����������һ�����ʵ�����ӳٵ����࣬�ֳƹ���ģʽ�����⹹��ģʽ����̬
 *	����ģʽ����һ���ഴ����ģʽ��
 *	˼�������������ܲ���Ϊ��̬������
 */
#pragma once
#include "stdafx.h"

namespace dp_factorymethod {
	// �����Ʒ��
	class Product {

	};

	// �����Ʒ��
	class ConcreteProduct : public Product {

	};

	// ���󹤳���
	class Factory {
	public:
		virtual ~Factory() {}
		// ������������������ʵ��
		virtual Product * FactoryMethod() = 0;
	};

	// ���幤����
	class ConcreteFactoy : public Factory {
	public:
		virtual Product * FactoryMethod() {
			return new ConcreteProduct();
		}
	};
};


namespace linary_factorymethod {
	// �����Ʒ�������Ʒ
	class DigitalProduct {
	public:
		DigitalProduct(const std::string & name) : name(name) {}

		// ��ӡ��Ʒ��Ϣ
		void ShowInfo() {
			std::cout << "��Ʒ���Ϊ��" << name << std::endl;
		}
	protected:
		// ��Ʒ��������
		std::string name;
	};

	// �ֻ��ࣺ�����Ʒ
	class Phone : public DigitalProduct {
	public:
		Phone(const std::string & name) : DigitalProduct(name) {}
	};

	class Player : public DigitalProduct {
	public:
		Player(const std::string & name) : DigitalProduct(name) {}
	};

	// ���빫˾�����󹤳�
	class DigitalCompany {
	public:
		virtual ~DigitalCompany() {}
		// ������Ʒ
		virtual DigitalProduct * CreateProduct() = 0;
	};

	// �ֻ����칫˾
	class PhoneCompany : public DigitalCompany {
	public:
		virtual DigitalProduct * CreateProduct() {
			return new Phone("Phone");
		}
	};

	// ���������칫˾
	class PlayerCompany : public DigitalCompany {
	public:
		virtual DigitalProduct * CreateProduct() {
			return new Player("Player");
		}
	};


	// ���Դ���
	static void Test_FactoryMethod() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--   ��������ģʽ����   --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		// ����һ���ֻ�������
		PhoneCompany * phoneCompany = new PhoneCompany(); 
		// �ӹ����л�ȡһ���ֻ�
		DigitalProduct * phone = phoneCompany->CreateProduct();
		// ��ӡ��Ʒ��Ϣ
		phone->ShowInfo();

		// ����һ��������������
		PlayerCompany * playerCompany = new PlayerCompany();
		// �ӹ����л�ȡһ�����
		DigitalProduct * player = playerCompany->CreateProduct();
		// ��ӡ��Ʒ��Ϣ
		player->ShowInfo();

		delete player;
		delete playerCompany;
		delete phone;
		delete phoneCompany;

		std::cout << std::endl;
	}
};