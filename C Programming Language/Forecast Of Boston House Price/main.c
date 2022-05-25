#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<math.h>
#define bool int
#define false 0
#define true 1
#define FeatureMax 20  //�궨�����������ֵ���ø�����
#define DataMax 600    //������Ŀ�����������
#define TrainNum 9999      //ѵ������
#define LearnV 0.04         //ѧϰ��


double data[DataMax][FeatureMax]; //�洢�������ݼ�������
double max[FeatureMax];   //�����ֵ�������ݹ�һ��
double min[FeatureMax];   //����Сֵ�������ݹ�һ��
int dataNum; //������Ŀ
int trdataNum;  //ѵ��������Ŀ
int featureNum;//������Ŀ
int n;     //�ֶ���(featureNum+1)

double sumXY[FeatureMax];//x*y�����
double sumX[FeatureMax]; //x�����
double sumY;//y�����
double everageX[FeatureMax];  //xƽ��
double everageY; //yƽ��
double varianceX[FeatureMax]; //x����
double varianceY; //y����
double recoef[FeatureMax];  //������Ƥ��ѷ���ϵ��

int p;   //Ҫѡ�����������������������˵��4��
int pos[FeatureMax];   //��¼ѡ����Ǽ���������ԭ���ݼ�������
double datase[DataMax][FeatureMax]; //�������Է��̵����ݼ�����������
double coef[TrainNum+1][FeatureMax];  //ϵ������,���һ����ѵ��������ϵ�����

double rmse;  //���Լ��еľ��������

double realcoef[FeatureMax];  //������ϵ�������һ�����

struct Feature {
	char* name[FeatureMax];//���������ַ���
	double coef[FeatureMax];  //����ϵ��
};
struct Feature Feain, Feaout;  //���������ѡ�������

bool Inputs();
void Init();
void SortSelect();
void LineReg();
void Text();
void ReInit();
void Outputs();

int main() {
	if (Inputs() == false) return 0;
//	for (int i = 0; i < dataNum; i++) {
//		for (int j = 1; j < n; j++) {
//			printf("%lf",data[i][j]);
//		}
//	}
	Init();
	SortSelect();
	LineReg();
	Text();
	ReInit();
	Outputs();
	return 0;
}

//���ݶ���
bool Inputs() {
	int i;
	for (i = 0; i < FeatureMax; i++) {
		Feain.name[i] = (char*)malloc(sizeof(char) * 10);
		Feaout.name[i] = (char*)malloc(sizeof(char) * 10);
	}

	//char fname[256];//�ļ���
	//printf("�����������ݵ��ļ����� ");
	//scanf("%s", fname);
	printf("������ݵ��ļ�����housing.txt\n");
	printf("\n������ĿdataNum��\n");   //506
	scanf("%d", &dataNum);
	printf("\n������ĿfeatureNum:\n");  //���Ϸ��� 14
	scanf("%d", &featureNum);
	n = featureNum + 1;
	trdataNum = dataNum * 7 / 10;   //������ѵ�������������ݼ�����!!!

	FILE* fp = fopen("housing.txt", "rb");//Ϊ��ÿ�����в���������������
	if (fp == NULL) {
		printf("���ܴ�������ļ�\n");
		fprintf(stderr, "open file error: %s", strerror(errno));  //����ԭ��
		return false;
	}

	Feain.name[0] = '\0';
	Feaout.name[0] = '\0';
	for (i = 1; i < n; i++) {
		fscanf(fp, "%s", Feain.name[i]);
	}

	memset(max, 0, sizeof(max));//��ʼ��������鶼Ϊ0
	memset(min, 0x7f7f7f7f, sizeof(min));//�����
	for ( i = 0; i < dataNum; i++) {
		data[i][0] = 1; //  ���ʼϵ��Ϊ1��x0��1
		for (int j = 1; j < n; j++) {
			fscanf(fp, "%lf", &data[i][j]);    //�����ݵ�ͬʱ�Ҹ����������Сֵ
			if (data[i][j] > max[j])
				max[j] = data[i][j];
			if (data[i][j] < min[j])
				min[j] = data[i][j];

		}
	}
	fclose(fp);

	return true;
}

//��ʼ��  ���ݹ�һ��
void Init() {
	for (int i = 0; i < dataNum; i++) {
		for (int j = 1; j < n; j++) {
			data[i][j] = 1.0*(data[i][j] - min[j]) / (max[j] - min[j]);
		}
	}
}

//����ѡ������������ϵ��������ѡ���������ά�ȣ�
void SortSelect() {
	int i, j;
	sumY = 0;
	for (i = 0; i < dataNum; i++) {
		sumY += data[i][featureNum];

	}
	//printf("\n sumY=%f", sumY);
	for (j = 1;j < featureNum; j++) {
		sumX[j] = 0;
		sumXY[j] = 0;
		for (i = 0; i < dataNum; i++) {
			sumX[j] += data[i][j];
			sumXY[j] += data[i][j] * data[i][featureNum];
		}
		//printf("\n sumX[%d]=%f", j,sumX[j]);
		//printf("\n sumXY[%d]=%f", j, sumXY[j]);
	}

	everageY = 1.0*sumY / dataNum;
	//printf("\n everageY=%f", everageY);
	double t = 0;
	for (i = 0; i < dataNum; i++) {
		t += pow(data[i][featureNum] - everageY, 2);
	}
	varianceY = 1.0*t / dataNum;
	//printf("\n varianceY=%f", varianceY);
	for (j = 1; j < featureNum; j++) {
		everageX[j] = 1.0*sumX[j] / dataNum;
		t = 0;
		for (i = 0; i < dataNum; i++) {
			t += pow(data[i][j] - everageX[j], 2);
		}
		varianceX[j] = 1.0*t / dataNum;
		//printf("\n varianceX[%d]=%f", j, varianceX[j]);
	}
	printf("\n���������ϵ����\n");
	for (j = 1; j < featureNum; j++) {
		recoef[j] = 1.0*(1.0*sumXY[j] / dataNum - everageX[j] * everageY) / sqrt(varianceX[j] * varianceY);
		//printf("\n recoef[%d]=%f", j, recoef[j]);
		printf("%s\t%f\n", Feain.name[j], recoef[j]);
	}
	//��Ϊ�и�����ϵ��������ѡ����Ҫ����temp���飻
	double temp[FeatureMax];
	for (j = 1; j < featureNum; j++) {
		temp[j] = fabs(recoef[j]);
	}
	printf("\n������ѡ������������ĸ�����1<=p<featureNum��\n");
	scanf_s("%d", &p);
	int k=1;
	int m = 1;
	while (k <= p) {
		int  max = 1;
		for (j = 1; j < featureNum; j++) {
			if (temp[j] > temp[max]) {
				max = j;
			}
		}
		temp[max] = 0;   //��0������Ƚ���
		pos[m++] = max;
		strcpy(Feaout.name[k], Feain.name[max]);
		for (i = 0; i < dataNum; i++) {
			datase[i][k] = data[i][max];
		}
		k++;
	}
	for (i = 0; i < dataNum; i++) {    //��Ҫ���˻��з�����һ��
		datase[i][0] = 1;
		datase[i][p+1] = data[i][featureNum];
	}
//	for (i = 0; i < dataNum; i++) {
//		for (j = 0; j <=(p + 1); j++) {
//			printf("%f ", datase[i][j]);
//		}
//		printf("\n");
//	}
	//ѡ�������͹���һ���µ����ݼ���
}

//���Իع�  �ݶ��½� ѵ��1000�Σ��� �����Է���
void LineReg() {
	int i,j,k,l;
	//for (i = 0; i < TrainNum; i++) { //ϵ����ʼ��Ϊ1
		for (j = 0; j < p+1; j++) {
			coef[0][j] = 1;
		}
	//}
	for (i = 1; i <=TrainNum; i++) {
		for (j = 0; j < p+1; j++) {
			double t1=0;
			for (l = 0; l < trdataNum; l++) {
				double t2 = 0;
				for (k = 0; k < p+1; k++) {
					t2 += (coef[i - 1][k] * datase[l][k]);

				}
				t1 += ((t2  - datase[l][p+1])* datase[l][j]);
			}
			coef[i][j] = coef[i-1][j]-(1.0*LearnV*t1/trdataNum);
			//printf("\ncoef[%d][%d]=%f\n", i, j, coef[i][j]);
		}

	}

	printf("\nѵ��%d�κ����Է�������Ӧ��ϵ��(δ����һ��)��\n",TrainNum,p);
	for (i = 0; i < p + 1; i++) {
		printf("%10s : %10f\n", Feaout.name[i], coef[TrainNum][i]);
	}
}

void Text() {
	int i, j;
	double t1 = 0;
	for (i = trdataNum; i < dataNum; i++) {
		double t2 = 0;
		for (j = 0; j < p+1; j++) {
			t2 += coef[TrainNum][j] * datase[i][j];
		}
		t2 =pow(t2-datase[i][p+1],2);
		t1 += t2;
	}
	//printf("\n t1=%f \n", t1);
	double num = (double)dataNum - trdataNum;
	rmse = sqrt(1.0*t1 / num);
	printf("\nѵ��%d�κ��RMSEΪ��%f\n",TrainNum,rmse);
}
//ϵ������һ��
void ReInit() {
	int i;
	for (i = 0; i < p + 1; i++) {
		realcoef[i] = coef[TrainNum][i];
	}
	for (i = 1; i <= p; i++) {//�ȼ���w0����ʵֵ
		realcoef[0] -= (1.0 * coef[TrainNum][i] * min[pos[i]] / (max[pos[i]] - min[pos[i]]));
	}
	realcoef[0] = realcoef[0] * (max[featureNum] - min[featureNum]) + min[featureNum];
	int j;
	for (j = 1; j < p+1; j++) {
		realcoef[j] *= (1.0 * (max[featureNum] - min[featureNum]) / (max[pos[j]] - min[pos[j]]));
	}
	printf("\nѵ��%d�κ����Է�������Ӧ��ϵ��(�ѷ���һ��)��\n",TrainNum, p);
	for (i = 0; i < p + 1; i++) {
		printf("%10s : %10f\n", Feaout.name[i], realcoef[i]);
	}
}

//���
void Outputs() {
	printf("\n�������ɽ��з���Ԥ��\n");
	int i;
	double x[FeatureMax];
	x[0] = 1;
	for (i = 1; i < p + 1; i++) {
		printf("������%s��ֵ:\n", Feaout.name[i]);
		scanf_s("%lf", &x[i]);
	}
	double result=0;
	for (i = 0; i < p + 1;i++) {
		result += realcoef[i] * x[i];
	}
	printf("Ԥ����Ϊ��%f", result);
}

