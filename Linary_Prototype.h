/*****************************************************************/
/* ���ģʽ��������ԭ��ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.06.01
/*****************************************************************/


/**	ԭ��ģʽ��ʹ��ԭ��ʵ��ָ��������������࣬����ͨ����¡��Щԭ�ʹ����µĶ���
 */
#pragma once
#include "stdafx.h"

namespace linary_prototype {
	// ����ԭ����
	class Frame {
	public:
		// ���캯��
		Frame(const std::string & title) : title(title) {}
		// �������캯����ע�����ﲻ�Ǵ�ָ�룬���Ƕ�������
		Frame(Frame & frame) {
			*this = frame;
		}

		virtual Frame * Clone() = 0;

		// ���ò���
		void SetTitle(const std::string & title) {
			this->title = title;
		}

		// ��ӡ��Ϣ
		virtual void Print() {
			std::cout << "��ͼ���⣺" << title << std::endl;
		}
	protected:
		std::string title;
	};


	// ButtonҲ��Ҫ�ܱ���¡
	class Button {
	public:
		Button(const std::string & label) : label(label) {}
		// �������캯��
		Button(Button & button) {
			*this = button;
		}
		// Set����
		void SetLabel(const std::string & label) {
			this->label = label;
		}

		// ��¡����
		Button * Clone() {
			return new Button(*this);
		}

		// 
		void Print() {
			std::cout << "��ť��ǩ��" << this->label << std::endl;
		}
	private:
		std::string label;
	};


	// ������֮ǰanimation�����õ���ģ����˼��
	class ContainerView : public Frame {
	public:
		ContainerView(const std::string & title, const std::string & label) : Frame(title) {
			button = new Button(label);
		}
		// ǧ�����������
		~ContainerView() {
			delete button;
		}
		// ʵ��clone����
		virtual ContainerView * Clone() {
			ContainerView * containerView = new ContainerView(*this);
			Button * button = this->button->Clone();

			containerView->button = button;
			return containerView;
		}

		// ���ð�ť��ǩ
		void SetBtnLabel(const std::string & label) {
			button->SetLabel(label);
		}

		// ��ӡ��Ϣ
		virtual void Print() {
			Frame::Print();
			button->Print();
		}
	protected:
		Button * button;
	};


	// ���Դ���
	static void Test_Prototype() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     ԭ��ģʽ����     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		ContainerView * studyContainer = new ContainerView("ѧϰ", "��ʼѧϰ");
		ContainerView * examContainer = studyContainer->Clone();

		examContainer->SetTitle("����");
		examContainer->SetBtnLabel("��ʼ����");
		studyContainer->Print();
		examContainer->Print();

		std::cout << (studyContainer == examContainer ? "true" : "false") << std::endl;

		delete examContainer;
		delete studyContainer;

		std::cout << std::endl;
	}
};