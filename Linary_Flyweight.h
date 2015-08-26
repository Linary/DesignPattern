/*****************************************************************/
/* ���ģʽ����������Ԫģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.05.27
/*****************************************************************/


/**	��Ԫģʽ��
 */
#pragma once
#include "stdafx.h"
namespace linary_flyweight {
	// ���ݿ����ӳص�Ӧ�ã�ÿ�����ӵ�IP��Port�����ݿⶼ��һ���ģ�������Ϊ�ڲ�״̬
	// ����һ����������Ϊ��Ԫ���ⲿ״̬
	class Connection {
	public:
		// ��Ԫ��������ⲿ״̬
		Connection(const std::string & tablename) : hostport("127.0.0.1:5432"), database("postgres"), 
			tablename(tablename), visituser("δ֪") {}

		void SetVisitUser(const std::string & visituser) {
			this->visituser = visituser;
		}

		void PrintInfo() {
			std::cout << "����&�˿ڣ� " << hostport << std::endl;
			std::cout << "��ǰ��   �� " << tablename << std::endl;
			std::cout << "�����û� �� " << visituser << std::endl;
		}
	protected:
		// �������������ģʽ�޹أ���Ϊ�˱������ݿ����ӣ����Ǽ���
		const std::string hostport;
		const std::string database;
		// �ڲ�״̬���ڲ�״̬����˵�������ж�һģһ�������ԣ�����ָ��Щ���Ե�ȡֵ������ǹ̶��ģ��ǿ�����ٵ�
		// ����ĳ����Ŀ�����У������Ŀ����Ӧ������Ŀ�ǿ�����ٵ�
		const std::string tablename;
		// �ⲿ״̬��ÿ���¼����п��ܲ�һ����ֵ���滷���ı���ı䣬���޷���ٵģ�����˵û�б�Ҫ��ٳ�����
		std::string visituser;
	};

	

	// ���ӳ��࣬�䵱��Ԫ����
	class ConnectionPool {
	public:
		ConnectionPool(int maxNum) : maxNum(maxNum), avlNum(maxNum) {}
		// ������������٣���Ȼ���ڴ�й©
		~ConnectionPool() {
			for (auto it = pool.begin(); it != pool.end(); ++it) {
				delete it->second;
				it->second = NULL;
			}
			pool.clear();
		}

		// ��ȡһ������
		Connection * GetConnection(const std::string & tablename) {
			// ����������Ѵ����ֵ������NULL
			if (avlNum == 0) {
				return NULL;
			}

			if (!pool.count(tablename)) {
				// ���δ�ҵ���Ӧ���������ӣ��ȴ���һ�����ӣ��ٷ���
				pool.insert(std::make_pair(tablename, new Connection(tablename)));
			} 
			std::cout << "--------------------------" << std::endl;
			std::cout << "�������� �� " << --avlNum << std::endl;
			// ����ҵ���Ӧ���������ӣ�ֱ�ӷ���
			return pool[tablename];
		}
	private:
		// ���������
		int maxNum;
		// ����������
		int avlNum;
		// ���ӳ�����
		std::map<std::string, Connection *> pool;
	};


	// ���Դ���
	static void Test_Flyweight() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     ��Ԫģʽ����     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		// �½�һ�����ӳع���
		ConnectionPool connectionPool(5);
		// ����һ���û������
		Connection * userConnection1 = connectionPool.GetConnection("st_user");
		userConnection1->SetVisitUser("Linary");
		userConnection1->PrintInfo();
		// ����һ���γ̱����
		Connection * lessonConnection = connectionPool.GetConnection("st_lesson");
		lessonConnection->SetVisitUser("Cindy");
		lessonConnection->PrintInfo();
		// ����һ���û������
		Connection * userConnection2 = connectionPool.GetConnection("st_user");
		userConnection2->SetVisitUser("Frank");
		userConnection2->PrintInfo();

		std::cout << std::endl;
	}
};