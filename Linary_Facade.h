
/*****************************************************************/
/* ���ģʽ�����������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.04.03
/*****************************************************************/

#pragma once

namespace linary_facade {
	// ������
	class Compiler {
	public:
		void Compile() {
			std::cout << "1������Դ����" << std::endl;
		}
	};

	// ������
	class Linker {
	public:
		void Link() {
			std::cout << "2�����Ӷ����ļ�" << std::endl;
		}
	};

	// ����̨
	class Consoler {
	public:
		void Print() {
			std::cout << "3����ӡ���" << std::endl;
		}
	};

	// ���ɿ�����������������������������ִ����
	class IDE {
	public:
		// ���ɿ��������Ĺ��캯��
		IDE() {
			compiler = new Compiler();
			linker   = new Linker();
			consoler = new Consoler();
		}
		// ���ɿ�����������������
		~IDE() {
			delete consoler;
			delete linker;
			delete compiler;
		}
		// ������
		void Compile() {
			compiler->Compile();
		}
		// ���ɽ������������ + ���ӣ�
		void GenerateSolution() {
			compiler->Compile();
			linker->Link();
		}
		// ���У����� + ���� + ��ӡ�����
		void Run() {
			compiler->Compile();
			linker->Link();
			consoler->Print();
		}

	private:
		Compiler * compiler;
		Linker   * linker;
		Consoler * consoler;
	};

	// ���Դ���
	static void Test_Facade() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     ���ģʽ����     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		IDE * VS2010 = new IDE();
		VS2010->Compile();
		VS2010->GenerateSolution();
		VS2010->Run();

		delete VS2010;

		std::cout << std::endl;
	}
}