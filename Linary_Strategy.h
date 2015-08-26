/*****************************************************************/
/* ���ģʽ������������ģʽ
/* ���ߣ�������	
/* ʱ�䣺2015.06.07
/*****************************************************************/


/**	����ģʽ������һϵ���㷨�࣬��ÿһ���㷨��װ�������������ǿ����໥�滻��
 *	����ģʽ���㷨������ʹ�����Ŀͻ��˶��仯����һ�ֶ�����Ϊ��ģʽ��
 */

#pragma once
#include "stdafx.h"

namespace dp_strategy {
	// ���������
	class Strategy {
	public:
		// �㷨
		virtual void Algorithm() = 0;
	};

	// �����㷨A
	class ConcreteStrategyA : public Strategy {
	public:
		virtual void Algorithm() {}
	};

	// �����㷨B
	class ConcreteStrategyB : public Strategy {
	public:
		virtual void Algorithm() {}
	};

	// ������
	class Context {
	public:
		void Algorithm() {
			return strategy->Algorithm();
		}
	private:
		Strategy * strategy;
	};
};

namespace linary_strategy {
	

	// ѵ��ģ�ͣ����������
	class TrainModel {
	public:
		// ����ѵ���㷨
		virtual void Train() = 0;
	};

	// RBMģ�ͣ��������
	class RBM : public TrainModel {
	public:
		virtual void Train() {
			std::cout << "��RBMģ��ѵ��" << std::endl;
		}
	};

	// CNNģ�ͣ��������
	class CNN : public TrainModel {
	public:
		virtual void Train() {
			std::cout << "��CNNģ��ѵ��" << std::endl;
		}
	};

	// ����ģ�ͣ����������
	class ClassifyModel {
	public:
		// ��������㷨
		virtual void Classify() = 0;
	};

	// SVMģ�ͣ��������
	class SVM : public ClassifyModel {
	public:
		virtual void Classify() {
			std::cout << "��SVMģ�ͷ���" << std::endl;
		}
	};

	// KMeansģ�ͣ��������
	class KMeans : public ClassifyModel {
	public:
		virtual void Classify() {
			std::cout << "��KMeansģ�ͷ���" << std::endl;
		}
	};

	// ���ѧϰ�㷨�ࣺ������
	class DeepLearning {
	public:
		// ����������
		DeepLearning() {}
		~DeepLearning() {
			delete classifyModel;
			delete trainModel;
		}

		void SetTrainModel(TrainModel * trainModel) {
			this->trainModel = trainModel;
		}

		void SetClassifyModel(ClassifyModel * classifyModel) {
			this->classifyModel = classifyModel;
		}

		// ����ģ�巽��ģʽ��Ӧ��
		void Run() {
			std::cout << "��ʼִ�����ѧϰ..." << std::endl;
			Train();
			Classify();
		}

		// ����ģ������㷨
		void Train() {
			trainModel->Train();
		}

		void Classify() {
			classifyModel->Classify();
		}

	private:
		// ... Ԥ����
		TrainModel * trainModel;
		ClassifyModel * classifyModel;
		// ... ����
	};


	// ���Դ���
	static void Test_Strategy() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     ����ģʽ����     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		DeepLearning deepLearning;
		deepLearning.SetTrainModel(new RBM());
		deepLearning.SetClassifyModel(new SVM());
		deepLearning.Run();

		std::cout << std::endl;
	}
};