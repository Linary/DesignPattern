/*****************************************************************/
/* ���ģʽ������������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.05.30
/*****************************************************************/

#pragma once
#include "stdafx.h"

/**	����ģʽ��Ϊ���������ṩһ�ִ����Կ��ƶ��������ķ���
 *	�ŵ㣺1��ְ��������2������չ�ԣ�3�����ܻ�����̬����
 *	������չ��
 *	1����ͨ����Ҫ��ͻ���ֻ�ܷ��ʴ����ɫ�������ܷ�����ʵ��ɫ��
 *	2��
 */

namespace dp_proxy {
	// ����������
	class Subject {
	public:
		// ����һ������
		virtual void Request() = 0;
	};

	// ��ʵ������
	class RealSubject : public Subject {
	public:
		// ʵ��һ������
		void Request() {}
	};
		
	// ������
	class Proxy : public Subject {
	public:
		// ͨ�����캯�����ݱ�������
		Proxy(Subject * subject) {
			this->subject = subject;
		}

		// ʵ�ַ���
		void Request() {
			PreProcess();
			subject->Request();
			PostProcess();
		}
	protected:
		// Ԥ����
		void PreProcess() {
			// do something
		}
		// ����
		void PostProcess() {
			// do something
		}
	private:
		Subject * subject;
	};
};


namespace linary_proxy {
	// �����ļ���ȡ��
	class FileReader {
	public:
		FileReader() {}
		FileReader(const std::string & filePath) : infile(filePath) {
			// ����ļ�·���д��׳��쳣
			/*if (!infile) {
				throw "can't find the file";
			}*/
		}

		// �������Ҫ�õ�ģ�巽��ģʽ
		std::vector<float> GetDataByCol(const std::string & colName) {
			// ����һ�����ݴ洢����
			std::vector<float> dataColl(GetDataTotalLine(), float());
			// �ļ�ָ���ƶ�����������
			SeekToDataHeadLine();
			std::cout << infile.get() << "+++++" << std::endl;

			return dataColl;
		}
	protected:
		// ��λ��������
		virtual void SeekToPropertyLine(){}
		// ��λ����������
		virtual void SeekToDataHeadLine(){}
		// ���ݵ�������
		int GetDataTotalLine() {
			return 10;
		}

		// �ƶ�����һ����ͬλ��
		int MoveToNextLine() {
			std::cout << "�ƶ�����һ�е���ͬλ��" << std::endl;
		}

	protected:
		// �ļ���ȡ��
		std::ifstream infile;
	};

	// �����ļ���ȡ��
	
	class AscFileReader : public FileReader {
	public:
		// ����������й���
		AscFileReader(const std::string & filePath) : FileReader(filePath) {}

		// ��λ��������
		virtual void SeekToPropertyLine() {
			
			std::cout << "��λ��������" << std::endl;
		}
		// ��λ����������
		virtual void SeekToDataHeadLine() {
			infile.seekg(8);

			std::cout << "��λ����������" << std::endl;
		}
	private:
	};

	// ������
	template <typename FileType>
	class FileReaderProxy : public FileReader {
	public:
		// ͨ�����캯������Ҫ��ʲô�ļ����Ͷ������
		FileReaderProxy<FileType>(const std::string & filePath) {
			// �������дһ���ļ���ʽ��ȡ����
			// ��������һ��ģ��
			fileReader = new FileType(filePath);
		}
		// ��������
		~FileReaderProxy() {
			delete fileReader;
		}
	private:
		FileType * fileReader;
	};

	// ���Դ���
	static void Test_Proxy() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     ����ģʽ����     --" << std::endl;
		std::cout << "--------------------------" << std::endl;
		// ����һ���ļ���ȡ�����࣬�����¶��һЩϸ��
		FileReaderProxy<AscFileReader> proxy("../xxx.txt");
		proxy.GetDataByCol("Sum");
	
		std::cout << std::endl;
	}
};