#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define Data 100				//ѵ����������
#define TestData 50				//������������
#define In 4					//�������Ԫ���������೤�ȣ������ȣ����곤�ȣ������ȣ�
#define Out 3					//�������Ԫ����������Ϊ�����β���Ŀ����ԣ�0-1����
#define Neuron 5				//��������Ԫ����
#define TrainC 40000			//���ѵ������
#define WAlta 0.1				//Ȩֵw��ѧϰ��
#define VAlta 0.1				//Ȩֵv��ѧϰ��

struct node {
	double in[In];
	double out[Out];
};

struct node iris[TestData + Data];//�洢������������
double d_in[Data][In];			//ѵ����������
double d_out[Data][Out];		//ѵ���������
double t_in[TestData][In];		//������������
double t_out[TestData][Out];	//�����������
double pre[TestData][Out];		//Ԥ��������ʵ�����
double v[Neuron][In];			//����㵽�������Ȩֵ
double y[Neuron];				//������
double w[Out][Neuron];			//�����㵽������Ȩֵ
double Maxin[In], Minin[In];	//������������ֵ����Сֵ
double Maxout[Out],Minout[Out];	//������������ֵ����Сֵ
double OutputData[Out];			//����������
double dw[Neuron][Out], dv[Neuron][In];//Ȩֵw��v��������
const char* Name[3] = { "Iris-setosa","Iris-versicolor","Iris-virginica" };//�β�����������
double mse;						//�������
double rmse;
double ermse;					//���������

void ReadData() {				//��ȡ�ļ��е�����
	srand(time(NULL));
	FILE* fp;
	char ch;
	char name[20];
	if ((fp = fopen("data.txt", "rb")) == NULL) {
		printf("���ܴ�data.txt�ļ�\n");
		exit(0);
	}
	int n = TestData + Data;
	for (int i = 0; i <n ; ++i) {	//ת�����ݵ��ṹ������
		for (int j = 0; j < In; ++j) {
			fscanf(fp,"%lf,", &iris[i].in[j]);
		}
//		fscanf(fp, "%c", &ch);
		fscanf(fp, "%s", name);
		memset(iris[i].out,0, sizeof(iris[i].out));
		for (int k = 0; k < 3; ++k) {	//����ά�ȵ����ݱ任
			if (strcmp(Name[k],name)==0) {
				iris[i].out[k] =1;
				break;
			}
		}
	}
	struct node tmp;
	int t=0;
	for (int i = 0; i < n; ++i) {		//��������
		t = rand() % n;
		tmp = iris[i];
		iris[i] = iris[t];
		iris[t] = tmp;
	}
	for (int i = 0; i < Data; ++i) {	//���ݻ���Ϊѵ�������������������Լ�����������
		for (int j = 0; j < In; ++j) {
			d_in[i][j] = iris[i].in[j];
		}
		for (int j = 0; j < Out; ++j) {
			d_out[i][j] = iris[i].out[j];
		}
	}
	for (int i = Data; i < TestData+Data; ++i) {
		for (int j = 0; j < In; ++j) {
			t_in[i-Data][j] = iris[i].in[j];
		}
		for (int j = 0; j < Out; ++j) {
			t_out[i-Data][j] = iris[i].out[j];
		}
	}
	fclose(fp);
}

void InitBPNetwork() {
	srand(time(NULL));
	for (int i = 0; i < In; ++i) {				//Ѱ��������������ֵ
		Maxin[i] = Minin[i] = d_in[0][i];
		for (int j = 0; j < Data; ++j) {
			Maxin[i] = Maxin[i] > d_in[j][i] ? Maxin[i] : d_in[j][i];
			Minin[i] = Minin[i] < d_in[j][i] ? Minin[i] : d_in[j][i];
		}
	}
	Maxout[0] = Maxout[1] = Maxout[2] = 1;		//������Ϊ1����С����Ϊ0
	Minout[0] = Minout[1] = Minout[2] = 0;
	for (int i = 0; i < In; ++i) {				//���������Сֵ�����ݽ��й�һ��
		for (int j = 0; j < Data; ++j) {
			d_in[j][i] = (d_in[j][i] - Minin[i]) / (Maxin[i] - Minin[i]);
		}
	}
	for (int i = 0; i < Out; ++i) {				//��һ��
		for (int j = 0; j < Data; ++j) {
			d_out[j][i] = (d_out[j][i] - Minout[i]) / (Maxout[i] - Minout[i]);
		}
	}
	for (int i = 0; i < Neuron; ++i) {			//ʹ�����ֵ��ʼ��Ȩֵ
		for (int j = 0; j < In; ++j) {
			v[i][j] = rand() * 2.0 / RAND_MAX - 1;
			dv[i][j] = 0;
		}
	}
	for (int i = 0; i < Out; ++i) {				//ʹ�����ֵ��ʼ��Ȩֵ
		for (int j = 0; j < Neuron; ++j) {
			w[i][j] = rand() * 2.0 / RAND_MAX - 1;
			dw[j][i] = 0;
		}
	}
}

void ComputO(int var) {					//ǰ�򴫲�
	double sum;
	for (int i = 0; i < Neuron; ++i) {
		sum = 0;						//�洢�ۼӺ�
		for (int j = 0; j < In; ++j) {	//����������ÿ����Ԫ�����
			sum += v[i][j] * d_in[var][j];
		}
		y[i] = 1 / (1 + exp(-1 * sum));
	}
	for (int i = 0; i < Out; ++i) {		//���������ÿ����Ԫ�����
		sum = 0;
		for (int j = 0; j < Neuron; ++j) {
			sum += w[i][j] * y[j];
		}
		OutputData[i] = 1 / (1 + exp(-1 * sum));
	}
}

void BackUpdata(int var) {				//���򴫲���Ȩֵ����
	double t;
	for (int i = 0; i < Neuron; ++i) {
		t = 0;
		for (int j = 0; j < Out; ++j) {	//�����������������֮��ĸ�Ȩֵ
			dw[j][i] = WAlta * (d_out[var][j] - OutputData[j]) * OutputData[j] * (1 - OutputData[j]) * y[i];
			t += (d_out[var][j] - OutputData[j]) * OutputData[j] * (1 - OutputData[j]) * w[j][i];
			w[j][i] += dw[j][i];
		}
		for (int j = 0; j < In; ++j) {	//�����������������֮��ĸ�Ȩֵ
			dv[i][j] = VAlta * t * y[i] * (1 - y[i]) * d_in[var][j];
			v[i][j]+=dv[i][j];
		}
	}
}

void TrainNetwork() {					//�������ѵ��
	int count = 1;						//��¼ѵ������
	do {
		mse = 0;						//�����������Ϊ0
		for (int i = 0; i < Data; ++i) {//����ѵ������һ��ѵ��
			ComputO(i);					//ǰ�򴫲�
			BackUpdata(i);				//���򴫲�������Ȩֵ
			for (int j = 0; j < Out; ++j) {	//���㵥���������
				double tmp1 = OutputData[j] * (Maxout[j] - Minout[j]) + Minout[j];
				double tmp2 = d_out[i][j] * (Maxout[j] - Minout[j]) + Minout[j];
				mse += pow(tmp1 - tmp2, 2.0);
			}
		}
		mse /= (double)Data * Out;		//����������
		if (count % 1000 == 0) {		//ÿ1000��ѵ������ʾһ��ѵ�����Ա�۲�
			printf("%d  %lf\n", count, mse);
		}
		count++;
	} while (count <= TrainC && mse >= 0.01);//ѵ��������ﵽҪ��ѵ������
	printf("ѵ������\n");
	printf("ѵ������:%d\n", count);
}

void TestNetwork() {			//������ģ������
	for (int i = 0; i < In; ++i) {	//Ԥ�����ݹ�һ��
		for (int j = 0; j < TestData; ++j) {
			t_in[j][i] = (t_in[j][i] - Minin[i]) / (Maxin[i] - Minin[i]);
		}
	}
	double sum;
	int m = 0;
	for (int k = 0; k < TestData; ++k) {//����ÿһ��������Ԥ����
		for (int i = 0; i < Neuron; ++i) {//�������������
			sum = 0;
			for (int j = 0; j < In; ++j) {
				sum += v[i][j] * t_in[k][j];
			}
			y[i] = 1 / (1 + exp(-1 * sum));
		}
		for (int i = 0; i < Out; ++i) {//����������Ԥ����
			sum = 0;
			for (int j = 0; j < Neuron; ++j) {
				sum += w[i][j] * y[j];
			}
			pre[k][i] = 1 / (1 + exp(-1 * sum)) * (Maxout[i] - Minout[i]) + Minout[i];
		}
		double max = 0;
		int t=0;
		printf("\n���:%d\n",k);		//���жԱ�
		printf("Ԥ��ֵ:");
		for (int i = 0; i < Out; ++i) {
			printf("%lf ", pre[k][i]);
			if (pre[k][i] > max) {
				max = pre[k][i];
				t = i;
			}
		}
		if (t_out[k][t] == 1) {
			m++;
		}
		printf("\nʵ��ֵ:");
		for (int i = 0; i < Out; ++i) {
			printf("%lf ", t_out[k][i]);
		}
	}
	double summse=0.0;
	for (int i = 0; i < Out; ++i) {	//�����������Ԥ��׼ȷ��
		double t = 0.0;
		for (int k = 0; k < TestData; ++k) {
			t +=pow(pre[k][i] - t_out[k][i], 2.0);
		}
		summse += sqrt(t / TestData);
	}
	rmse = summse / Out;
	printf("\nrmse: %.4lf,׼ȷ��:%lf\n", rmse,(double)m/TestData);
}

int main() {//������
	ReadData();
	InitBPNetwork();
	TrainNetwork();
	TestNetwork();
	return 0;
}
