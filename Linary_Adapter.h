/*****************************************************************/
/* ���ģʽ��������������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.06.04
/*****************************************************************/


/**	������ģʽ��
 */
#pragma once
#include "stdafx.h"
namespace linary_adapter {
	// �㷨���е���
	// ���ֲ�����
	class BinarySearch {
	public:
		// ������չ�ɷ��͵�
		int Run(int * coll, int len, int key) {
			int low = 0;
			int high = len - 1;
			int mid = 0;
			while (low <= high) {
				mid = (low + high) / 2;
				if (coll[mid] < key) {
					low = mid + 1;
				} else if (coll[mid] > key) {
					high = mid - 1;
				} else {
					return mid;
				}
			}
			// ���û�ҵ�
			return -1;
		}
	};

	// ����������
	class QuickSort {
	public:
		// ִ���㷨����ں���
		void Run(int * coll, int begin, int end) {
			// ������α��λ�ô��ڵ������α꣬���˳��ݹ�
			if (begin >= end) {
				return ;
			}

			// ���������α�
			int lp = begin;
			int rp = end;
			// ����
			int key = coll[lp];

			while (lp < rp) {
				while ((coll[rp] >= key) && (lp < rp)) {
					rp--;
				}
				// �ѱ� key С�����Ƶ����
				coll[lp] = coll[rp];
				while ((coll[lp] <= key) && (lp < rp)) {
					lp++;
				}
				// �ѱ� key ������Ƶ��ұ�
				coll[rp] = coll[lp];
			}
			// �����α��Ѿ���ͷ���� key �ŵ����ʵ�λ��
			coll[lp] = key;
			// �����ӿ�����������
			Run(coll, begin, lp - 1);
			// �����ӿ�����������
			Run(coll, lp + 1, end);
		}
	};

	// ����ɼ������ࣺĿ��ӿ�
	class ScoreOperation {
	public:
		virtual void ScoreSort(int * coll, int len) = 0;
		virtual int ScoreSearch(int * coll, int len, int key) = 0;
	};

	// ������������������
	class OperationAdapter : public ScoreOperation {
	public:
		OperationAdapter() {
			sortObj = new QuickSort();
			searchObj = new BinarySearch();
		}

		~OperationAdapter() {
			delete searchObj;
			delete sortObj;
		}

		void ScoreSort(int * coll, int len) {
			sortObj->Run(coll, 0, len - 1);
		};

		int ScoreSearch(int * coll, int len, int key) {
			return searchObj->Run(coll, len, key);
		}
	private:
		QuickSort * sortObj;
		BinarySearch * searchObj;
	};


	// ���Դ���
	static void Test_Adapter() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    ������ģʽ����    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		ScoreOperation * operation = new OperationAdapter();
		int scores[] = {84, 76, 50, 69, 90, 88};
		int score;
		std::cout << "ԭʼ�ɼ�Ϊ��" << std::endl;
		std::copy(scores, scores + 6, std::ostream_iterator<int>(std::cout, "\t"));
		std::cout << std::endl;
		operation->ScoreSort(scores, 6);
		std::cout << "�����ɼ���" << std::endl;
		std::copy(scores, scores + 6, std::ostream_iterator<int>(std::cout, "\t"));
		std::cout << std::endl;
		std::cout << "���ҳɼ�90��" << std::endl;
		score = operation->ScoreSearch(scores, 6, 90);
		std::cout << (score >= 0 ? "�ҵ�" : "δ�ҵ�") << std::endl;
		delete operation;

		std::cout << std::endl;
	}
};