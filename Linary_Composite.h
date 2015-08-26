/*****************************************************************/
/* ���ģʽ�����������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.06.04
/*****************************************************************/


/**	���ģʽ����϶�������γ����Ľṹ���Ա�ʾ�����塪�����֡���ϵ�Ĳ�νṹ��
 *	���ģʽ�Ե�������Ҷ�Ӷ��󣩺���϶����������󣩵�ʹ�þ���һ���ԡ�
 */
#pragma once
#include "stdafx.h"

namespace dp_composite {
	// ���󹹼���
	class Component {
	public:
		// ���ӳ�Ա
		virtual void Add(Component * component) = 0;
		// ɾ����Ա
		virtual void Remove(Component * component) = 0;
		// ���ҳ�Ա
		virtual Component * GetChild(int idx) = 0;
		// ҵ�񷽷�
		virtual void Operation() = 0;
	};

	// Ҷ�ӽڵ���
	class Leaf : public Component {
		// ���ӳ�Ա
		virtual void Add(Component * component) {}
		// ɾ����Ա
		virtual void Remove(Component * component) {}
		// ���ҳ�Ա
		virtual Component * GetChild(int idx) {}
		// ҵ�񷽷�
		virtual void Operation() {
			// Ҷ�ӽڵ��Լ���ҵ�񷽷�
		}
	};

	// �������������
	class Compisite : public Component {
	public:
		// ���ӳ�Ա
		virtual void Add(Component * component) {
			coll.push_back(component);
		}
		// ɾ����Ա
		virtual void Remove(Component * component) {
			coll.remove(component);
		}
		// ���ҳ�Ա
		virtual Component * GetChild(int idx) {
			auto it = coll.begin();
			std::advance(it, idx);
			return *it;
		}
		// ҵ�񷽷�
		virtual void Operation() {
			// Ҷ�ӽڵ��Լ���ҵ�񷽷�
		}
	private:
		std::list<Component *> coll;
	};
};


namespace linary_composite {
	// �����õ���͸�����ģʽ
	// �����ļ���
	class AbstractFile {
	public:
		AbstractFile(const std::string & name) : name(name) {}

		virtual void Add(AbstractFile * file) = 0;
		virtual void Remove(AbstractFile * file) = 0;
		virtual AbstractFile * GetChild(int idx) = 0;
		virtual void KillVirus() = 0;
	protected:
		std::string name;
	};

	// ͼ���ļ���
	class ImageFile : public AbstractFile {
	public:
		ImageFile(const std::string & name) : AbstractFile(name) {}

		virtual void Add(AbstractFile * file) {
			std::cout << "�Բ��𣬲�֧�ָò���" << std::endl;
		}
		virtual void Remove(AbstractFile * file) {
			std::cout << "�Բ��𣬲�֧�ָò���" << std::endl;
		}
		virtual AbstractFile * GetChild(int idx) {
			return NULL;
		}
		virtual void KillVirus() {
			std::cout << "--��ͼ���ļ���" << name << "��ɱ��" << std::endl;
		}
	};

	// �ı��ļ���
	class TextFile : public AbstractFile {
	public:
		TextFile(const std::string & name) : AbstractFile(name) {}

		virtual void Add(AbstractFile * file) {
			std::cout << "�Բ��𣬲�֧�ָò���" << std::endl;
		}
		virtual void Remove(AbstractFile * file) {
			std::cout << "�Բ��𣬲�֧�ָò���" << std::endl;
		}
		virtual AbstractFile * GetChild(int idx) {
			return NULL;
		}
		virtual void KillVirus() {
			std::cout << "--���ı��ļ���" << name << "��ɱ��" << std::endl;
		}
	};

	// �ļ�����
	class Folder : public AbstractFile {
	public:
		Folder(const std::string & name) : AbstractFile(name), coll() {}

		virtual void Add(AbstractFile * file) {
			coll.push_back(file);
		}
		virtual void Remove(AbstractFile * file) {
			coll.remove(file);
		}
		virtual AbstractFile * GetChild(int idx) {
			auto it = coll.begin();
			std::advance(it, idx);
			return *it;
		}
		virtual void KillVirus() {
			std::cout << "���ļ��С�" << name << "��ɱ��" << std::endl;
			// �ݹ���ó�Ա��KillVirus����
			for (auto it = coll.begin(); it != coll.end(); ++it) {
				(*it)->KillVirus();
			}
		}
	private:
		// ����Ӧ�û�������֮������ݽṹ
		std::list<AbstractFile *> coll;
	};


	// ���Դ���
	static void Test_Composite() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     ���ģʽ����     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		// ���ͬ���ĳ����ļ����
		AbstractFile * file1, * file2, * file3, * file4;
		AbstractFile * folder1, * folder2, * folder3;

		folder1 = new Folder("�ҵ��ĵ�");
		folder2 = new Folder("ͼ���ļ�");
		folder3 = new Folder("�ı��ļ�");

		file1 = new ImageFile("С��Ů.jpg");
		file2 = new ImageFile("���޼�.jpg");
		file3 = new TextFile("�������.txt");
		file4 = new TextFile("����������.pdf");

		folder2->Add(file1);
		folder2->Add(file2);
		folder3->Add(file3);
		folder3->Add(file4);
		folder1->Add(folder2);
		folder1->Add(folder3);

		folder1->KillVirus();

		delete folder3;
		delete folder2;
		delete folder1;
		delete file4;
		delete file3;
		delete file2;
		delete file1;

		std::cout << std::endl;
	}
};