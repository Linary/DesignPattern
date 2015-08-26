
/*****************************************************************/
/* ���ģʽ��������������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.04.01
/*****************************************************************/
#pragma once

namespace linary_builder {
	// �绰�࣬����ڲ�Ʒ��
	class Phone {
	public:
		// չʾ����
		void ShowConfig() {
			std::cout << "--  ����  --" << std::endl;
			std::copy(widgets.begin(), widgets.end(), 
				 std::ostream_iterator<std::string>(std::cout, "\n"));
		}
		// ��װ
		void Assemble(const std::string & widget) {
			widgets.push_back(widget);
		}
	private:
		// �绰�Ĳ���
		std::vector<std::string> widgets;
	};

	// ���������̣�����ڳ�������
	class Manufacturer {
	public:
		// ��ʼ��װPhone
		virtual void BeginAssemble() = 0;
		// ������װ�䣨���죩����
		virtual void AssembleBoard() = 0;
		virtual void AssembleChip() = 0;
		virtual void AssembleScreen() = 0;
		// ���ز�Ʒ
		virtual Phone * GetProduct() = 0;
	};

	// ���������̣���ʿ����������ھ��彨����A
	class Foxconn : public Manufacturer {
	public:
		virtual void BeginAssemble() {
			this->phone = new Phone();
		}

		virtual void AssembleBoard() {
			this->phone->Assemble("��������");
		}

		virtual void AssembleChip() {
			this->phone->Assemble("��ͨоƬ");
		}

		virtual void AssembleScreen() {
			this->phone->Assemble("������ʾ��");
		}

		virtual Phone * GetProduct() {
			return this->phone;
		}
	private:
		Phone * phone;
	};

	// ���������̣���˶��������ھ��彨����B
	class Asus : public Manufacturer {
	public:
		virtual void BeginAssemble() {
			this->phone = new Phone();
		}

		virtual void AssembleBoard() {
			this->phone->Assemble("��˶����");
		}

		virtual void AssembleChip() {
			this->phone->Assemble("������оƬ");
		}

		virtual void AssembleScreen() {
			this->phone->Assemble("��������ʾ��");
		}

		virtual Phone * GetProduct() {
			return this->phone;
		}
	private:
		Phone * phone;
	};

	// ָ���ߣ�ֻ����ָ�ӽ��죬�����𽻸���Ʒ
	class Director {
	public:
		void ChooseManufacturer(Manufacturer * manufacturer) {
			this->manufacturer = manufacturer;
		}
		void Construct() {
			manufacturer->BeginAssemble();
			manufacturer->AssembleBoard();
			manufacturer->AssembleChip();
			manufacturer->AssembleScreen();
		}
	private:
		Manufacturer * manufacturer;
	};

	static void Test_Builder() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    ������ģʽ����    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Director * director = new Director();
		Manufacturer * foxconn = new Foxconn();
		Manufacturer * asus = new Asus();

		director->ChooseManufacturer(foxconn);
		director->Construct();
		Phone * phone = foxconn->GetProduct();
		phone->ShowConfig();

		delete phone;
		delete asus;
		delete foxconn;
		delete director;

		std::cout << std::endl;
	}
}