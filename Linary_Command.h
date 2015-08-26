/*****************************************************************/
/* ���ģʽ������������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.06.08
/*****************************************************************/


/**	����ģʽ����һ�������װΪһ�����󣬴Ӷ����ò�ͬ������Կͻ����в�������
 *	�������Ŷӻ��߼�¼��־���Լ�֧�ֿɳ����Ĳ�������һ�ֶ�����Ϊ��ģʽ��
 */
#pragma once
#include "stdafx.h"

namespace dp_command {
	// ����������
	class Command {
	public:
		virtual void Execute() = 0;
	};

	// ������
	class Invoker {
	public:
		// ����ע��
		Invoker(Command * command) {
			this->command = command;
		}

		// ����ע��
		void SetInvoker(Command * command) {
			this->command = command;
		}

		// ���÷���
		void Call() {
			command->Execute();
		}
	private:
		Command * command;
	};

	// �����ߣ�һ��������������У�
	class Receiver {
	public:
		void Action() {
			// ִ�о������
		}
	};

	// ����������
	class ConcreteCommand : public Command {
	public:
		virtual void Execute() { 
			// ���ý����ߵ�ҵ������
			receiver->Action();
		}
	private:
		// ����һ��������
		Receiver * receiver;
	};
};

namespace linary_command {
	// 3�����������
	class Opener {
	public:
		void open() {
			std::cout << "��һ���ļ�" << std::endl;
		}
	};

	class Saver {
	public:
		void save() {
			std::cout << "����һ���ļ�" << std::endl;
		}
	};

	class Exiter {
	public:
		void exit() {
			std::cout << "�ر�һ���ļ�" << std::endl;
		}
	};

	// ����������
	class Command {
	public:
		Command(const std::string & function) : function(function) {} 
		virtual void Execute() = 0;
		const std::string & GetFunction() const {
			return function;
		}
	protected:
		std::string function;
	};

	// ������
	class OpenCommand : public Command {
	public:
		// ���캯��
		OpenCommand() : Command("��") {
			opener = new Opener();
		}
		// ����
		~OpenCommand() {
			delete opener;
		}
		virtual void Execute() {
			opener->open();
		}
	private:
		Opener * opener;
	};

	// ��������
	class SaveCommand : public Command {
	public:
		// ���캯��
		SaveCommand() : Command("����") {
			saver = new Saver();
		}
		// ����
		~SaveCommand() {
			delete saver;
		}
		virtual void Execute() {
			saver->save();
		}
	private:
		Saver * saver;
	};

	// �˳�����
	class ExitCommand : public Command {
	public:
		// ���캯��
		ExitCommand() : Command("�˳�") {
			exiter = new Exiter();
		}
		// ����
		~ExitCommand() {
			delete exiter;
		}
		virtual void Execute() {
			exiter->exit();
		}
	private:
		Exiter * exiter;
	};

	// ��ť�ࣺ��������
	class Button {
	public:
		Button(const std::string & label) : label(label) {}

		// get/set����
		const std::string & GetLabel() const {
			return label;
		}

		void SetLabel(const std::string & label) {
			this->label = label;
		}

		// Ϊ���ܼ�ע������
		void SetCommand(Command * command) {
			this->command = command;
		}

		// �õ���������
		const std::string & GetFunction() const {
			return command->GetFunction();
		}

		// ��������
		void OnClick() {
			command->Execute();
		}
	private:
		// ��ť��ǩ
		std::string label;
		// ά��һ���������
		Command * command;
	};

	// �����ࣺ���е��κν�ɫ��������ҵ�񻷾�����Ҫ
	class Window {
	public:
		// ����
		Window(const std::string & title) : title(title) {
			for (int i = 0; i < 3; i++) {
				std::stringstream ss;
				ss << "����" << i + 1; 
				buttons[i] = new Button(ss.str());
			}
		}
		// ����
		~Window() {
			for (int i = 2; i >= 0 ; --i) {
				delete buttons[i];
			}
		}

		// ��ָ����ť���ù��ܼ�
		void SetBtnFunction(int idx, Command * command) {
			if (1 <= idx && idx <= 3) {
				buttons[idx - 1]->SetCommand(command);
			} else {
				std::cout << "��Ч��ť" << std::endl;
			}
			
		}

		// ������ڵİ�ť
		void ClickBtn(int idx) {
			std::cout << "�����ť" << idx << "��";
			buttons[idx - 1]->OnClick();
		}

		// ��ʾ
		void Display() {
			std::cout << "--------------------------" << std::endl;
			std::cout << "��ʾ���ڣ�" << this->title << std::endl;
			std::cout << "���ܼ���" << std::endl;
			std::cout << "--------------------------" << std::endl;
			for (int i = 0; i < 3; i++) {
				std::cout << buttons[i]->GetLabel() << "��" << buttons[i]->GetFunction() << std::endl;
			}
			std::cout << "--------------------------" << std::endl;
		}
	private:
		// ���ڱ���
		std::string title;
		// ��ť����
		Button * buttons[3];
	};

	
	// ���Դ���
	static void Test_Command() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     ����ģʽ����     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Window * window = new Window("�Զ��幦�ܼ�");
		Command * openCommand = new OpenCommand(); 
		Command * saveCommand = new SaveCommand();
		Command * exitCommand = new ExitCommand();
		// �Զ��幦�ܼ�
		window->SetBtnFunction(1, openCommand);
		window->SetBtnFunction(2, saveCommand);
		window->SetBtnFunction(3, exitCommand);
		// ��ʾ
		window->Display();
		// �����ť
		window->ClickBtn(1);
		window->ClickBtn(2);
		window->ClickBtn(3);

		// �Զ��幦�ܼ�
		window->SetBtnFunction(1, saveCommand);
		window->SetBtnFunction(2, openCommand);
		window->SetBtnFunction(3, exitCommand);
		// ��ʾ
		window->Display();
		window->ClickBtn(1);
		window->ClickBtn(2);
		window->ClickBtn(3);

		delete exitCommand;
		delete saveCommand;
		delete openCommand;
		delete window;

		std::cout << std::endl;
	}
};