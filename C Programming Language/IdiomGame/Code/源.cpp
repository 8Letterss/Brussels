#include"Idiom.h"

int main() {
    system("title ������");
    system("color f4");
    system("mode con cols=80 lines=20");
    //system("color 0B");//�޸ı�����������ɫ

    int num1, num2, num3;//���ܳ����������������ܽ��������������������а��û�����
    idiom word[300];   //��ų�������
    idiom* wptr = word;
    user member;       //����û���¼����
    user* mptr = &member;
    record player;      //����û��ɼ�����
    record* pptr = &player;
    record rank[10];    //������а�����
    record* rptr = rank;
    max* maxptr = (max*)malloc(sizeof(max) * 100);
    max* hmaxptr = maxptr;


    printf("\n\n                               ϵͳ��ʼ����....    \n\n\n\n\n");
    //    cartoon();
    system("pause");
    system("cls");
    //    mciSentString("open abc.mp3 alias bkmusic",NULL,0,NULL);
    //    mciSentString("play bkmusic repeat",NULL,0,NULL);
    OutMenu(mptr);//������¼ϵͳ
    strcpy(pptr->name, mptr->name);//����������Ϣ
    num1 = GetData(wptr);//�����������
    num2 = SuperGet(maxptr);
    num3 = RankingList(rptr);
    system("cls");
    //    cartoon();

    player.fre = player.score1 = player.score2 = player.nums = 0;
    while (StartGame(pptr, wptr, num1, maxptr, num3, rptr) != 0) {
        system("pause");//ʹ���굥������ʱ��ͣ
        system("cls");
    }
    free(maxptr);
    //WriteList(pptr, rptr, num3);
    system("cls");
    printf("\n\n                   �����ϴ���...   \n\n\n");
    //    cartoon();
    system("pause");
    MessageBoxA(NULL, "��лʹ��", "�����Ƴ�ϵͳ", MB_ICONINFORMATION | MB_OK);

    return 0;
}

int GetData(idiom* ptr) {
    int num = 0;
    char str[200];//��ʱ��ų�������
    int i;
    FILE* fp;

    fp = fopen("idiom.txt", "r+");
    if (fp == NULL) {
        MessageBoxA(NULL, "�˳�ϵͳ", "�����ݴ���", MB_ICONSTOP | MB_OK);
        exit(0);
    }
    while (!feof(fp)) {
        fgets(str, 200, fp);
        for (i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
            if (str[i] == ':') {//���ַ����ָ�Ϊ���������
                str[8] = '\0';
                break;
            }
        }
        strcpy(ptr->word, str);
        strcpy(ptr->str, (str + 9));
        num++;
        ptr++;
    }
    fclose(fp);
    return num;
}

int SeekWord(idiom* input, idiom* wptr, int num) {
    int idx = -1;
    int i;

    for (i = 0; i < num; i++, wptr++) {
        if (strcmp(input->word, wptr->word) == 0) {
            idx = i;
            break;
        }
    }
    return idx;
}

int SuperGet(max* maxptr) {//����������ݶ�ȡ
    int num = 0;
    char str[10];
    int i;
    FILE* fp;
    max* maxptrTemp = maxptr;

    fp = fopen("word.txt", "r+");
    if (fp == NULL) {
        MessageBoxA(NULL, "�˳�ϵͳ", "��������", MB_ICONSTOP | MB_OK);
        exit(0);
    }
    while (!feof(fp)) {
        fgets(str, 10, fp);
        for (i = 0; str[i] != ' ' && str[i] != '\0' && str[i] != '\n'; i++) {
            if (str[i] == ' ' || str[i] == '\n') {
                str[8] = '\0';
                break;
            }
        }
        strcpy(maxptrTemp->word, str);
        num++;
        maxptrTemp++;
    }
    fclose(fp);
    return num;
}

int SuperSearch(max* maxptr, char str[]) {//�����������
    int idx = -1;
    int i;
    max* maxptrTemp = maxptr;

    for (i = 0; i < 56; i++, maxptrTemp++) {
        maxptrTemp->word[8] = '\0';
        maxptrTemp->word[9] = '\0';
        str[8] = '\0'; str[9] = '\0';
        if (strcmp(str, maxptrTemp->word) == 0) {
            idx = i;
            break;
        }
    }
    return idx;
}

int MatchingIdioms(max* maxptr, char str[]) {//ƥ��������
    int idx = -1;
    int i;
    max* maxptrTemp = maxptr;

    for (i = 0; i < 56; i++, maxptrTemp++) {
        if (maxptrTemp->word[0] == str[6] && maxptrTemp->word[1] == str[7]) {
            idx = i;
            break;
        }
    }
    return idx;
}

int MyRand(int num) {
    srand((int)time(NULL));
    return (rand() % (num));
}

int StartGame(record* player, idiom* wptr, int num, max* mptr, int num2, record* rptr) {
    int select;//�洢�û�ѡ����
    int flag = 1;//��Ϸ�Ƿ����
    int select2;//�洢�û�ѡ�����ģʽ

    system("title ��ʼ��Ϸ");
    system("color f4");
    system("mode con cols=45 lines=35");

    printf("==========��ѡ��ʹ�ù���==========\n");
    printf("\n[1]����ʵ�\n");
    printf("\n[2]�������\n");
    printf("\n[3]�������\n");
    printf("\n[4]���а�\n");
    printf("\n[5]�˳���Ϸ\n");
    printf("==================================\n\n");
    scanf("%d", &select);
    rewind(stdin);//��ջ�����

    switch (select) {
    case 1:
        player->fre += OpenDictionary(wptr, num);
        break;
    case 2:
        system("cls");
        printf("==========��ѡ�����ģʽ==========\n");
        printf("\n[1]Ů洲���\n");
        printf("\n[2]��������\n");
        printf("\n[3]����\n");
        printf("==================================\n\n");
        scanf("%d", &select2);
        rewind(stdin);//��ջ�����

        switch (select2) {
        case 1:
            player->score1 = PlayTest(wptr, num);
            break;
        case 2:
            player->score2 = PlayTest2(wptr, num);
            break;
        case 3:
            break;
        default:
            printf("\n������󣬷���\n\n");
            break;
        }
        break;
    case 3:
        player->nums = ManMachineWar(mptr, num);
        break;
    case 4:
        InList(rptr, num2);
        break;
    case 5:
        flag = 0;
        break;
    default:
        printf("\n������󣬷���\n\n");
        break;
    }

    return flag;
}

int OpenDictionary(idiom* wptr, int num) {
    idiom input;
    int idx;
    int i;
    int judge = 1;
    int count = 0;

    system("title ����ʵ�");
    system("color f4");
    system("mode con cols=100 lines=18");
    system("cls");
    MessageBoxA(NULL, "������ʹ�õ��ǹ���һ������ʵ�", "ģʽѡ��", MB_OK);
    MessageBoxA(NULL, "��������Ҫ��ѯ�ĳ��ϵͳ���ڳ������Ϊ��ƥ�䣬ƥ��ɹ�����ʾ��������", "ʹ��˵��", MB_OK);
    while (judge == 1) {
        system("cls");
        printf("==========����ʵ�==========\n\n");
        printf("��������Ҫ��ѯ�ĳ�� ");
        rewind(stdin);
        fgets(input.word, 9, stdin);
        input.word[8] = '\0';
        idx = SeekWord(&input, wptr, num);
        if (idx == -1) {
            printf("\n(��_��;) �ó��ﻹδ��¼Ŷ (��_��;)\n\n");
        }
        else {
            printf("\n����ҵĳ�����˼�ǣ�\n\n  %s\n", (wptr + idx)->str);
        }
        Sleep(1000);
        judge = MessageBoxA(NULL, "�Ƿ������ѯ", "��ʾ", MB_OKCANCEL);
        if (judge == 2) {//ѡ��ȡ��
            judge = 0;
        }
        count++;
    }
    return count;
}

int PlayTest(idiom* wptr, int num) {
    begin_menu();

    //MessageBoxA(NULL, "������ʹ�õ��ǹ��ܶ�������֪ʶ����", "ģʽѡ��", MB_OK);
    //printf("��������������������������������������������������Ů洲��������ԣ���������������������������������������������\n");
    //printf("\nl.ϵͳ���������һ��������ǻ���ȥ�����֣�����Ҫ����������������������;\n");
    //printf("\n2.ϵͳһ������20�⣬ÿ�����ÿ������ֻ��һ�λ�������;\n");
    //printf("\n3.ÿ���ֵĴ���ʱ��Ϊ15���ӣ���ʱ���𲻼���ɼ���\n");
    //printf("\n4.һ���ַ���Ϊ5�֣�ÿ�������Ժ�ϵͳ���Զ�������������\n");
    
    return 0;//�����û�����
}

int ManMachineWar(max* maxptr, int num) {//����������˻���ս
    int turn = 0;//��¼�����ִ�
    char putout[10];//�洢����ը����������
    char getin[10];//�洢�û���������
    int idx1, idx2;//���ղ�ѯ���
    int i;
    char allr[20][10];
    int r = 0;

    system("title �������");
    system("color f4");
    system("mode con cols=55 lines=44");

    srand(time(NULL));//�����������
    system("cls");
    MessageBoxA(NULL, "������ʹ�õ��ǹ���������������˻���ս", "ģʽѡ��", MB_OK);
    printf("==================��������˻���ս==================\n");
    printf("\n  �������㽫���˹����ܡ���ը������һ���˻���ս��\n");
    printf("\n==================================================\n");
    Sleep(2000);//����ʾ����ʾ��ʾ��Ϣ���Ż�����

    MessageBoxA(NULL, "���ȷ����ʼ�˻���ս��", "������ʼ��ս", MB_OK);
    printf("����ɱ�ң�\n\n");//�������Ż�����
    Sleep(1000);
    printf("�����Ҫ���ܽ�ס��10�����\n\n");
    Sleep(1000);
    printf("�ҵ�����������ڴ����Ե� ���p�������\n");
    Sleep(1000);
    idx1 = MyRand(15) * 2;//����������ʼ����
    printf("\n���аɣ�%s\n", (maxptr + idx1)->word);
    strcpy(putout, (maxptr + idx1)->word);
    strcpy(allr[r++], putout);
    while (1) {
        printf("\n�ֵ����ˣ�");
        rewind(stdin);//�����������ջ�����
        fgets(getin, 9, stdin);
        getin[8] = '\0';//��������
        idx1 = SuperSearch(maxptr, getin);//����û��Ƿ�����
        if (idx1 == -1) {//û���ҵ���˵�����ǳ������
            printf("\n��ը�����Ȼ��ƭ�ң���������ǳ�������ˣ�\n\n");
            break;
        }
        if (getin[0] != putout[6] || getin[1] != putout[7]) {//�û��ó������𣬵����޷�����
            printf("\n��ը���Ӳ����˰ɣ������������ˣ�\n\n");
            break;
        }//���û������ѭ����˵�������ɹ�����Ϸ����
        turn++;//�����ִμ�
        idx2 = MatchingIdioms(maxptr, getin);
        if (idx2 == -1) {//�������һ���֣������Ƿ��г�����Խ���
            printf("\n��ը���Ҵ����Ӯ�ˣ�\n\n");
            break;
        }else {//�ҵ���д���ַ���������������Ϸ����
            strcpy(allr[r++], getin);
            strcpy(putout, (maxptr + idx2)->word);
            strcpy(allr[r++], putout);
            printf("\n��ը������һ�ӣ�%s\n", putout);
        }
        if (turn == 10) {
            MessageBoxA(NULL, "������ǿ(�s#-_-)�s~~~~~~~~~~~~~~~~~�k�T�k ", "��Ӯ�ˣ�", MB_OK);
            break;
        }
    }
    Sleep(2000);
    system("cls");
    printf("\n\n-----------��Ϸ����------------");//���������Ϣ
    printf("\n\n������%d������\n\n", turn);
    printf("����������:");
    for (i = 0; i <r; i++) {
        printf("\n              %s    ", allr[i]);
    }
    printf("\n");
    return turn;//���ؽ����ִ�
}

int PlayTest2(idiom* wptr, int num) {
    int grade = 100;//��ʼ�ܷ�100��.ʵ�п۷���
    int i = 0;
    int oneBegin = 0; //�洢�û�һ���⿪ʼ����ʱ��
    int oneEnd = 0;   //�洢�û�һ�����������ʱ��
    char answer[9];//�洢�û�����
    char putout[9];//�洢�������Ŀ
    char meaning[200];
    int idx;//���ղ�ѯ���
    int deduct;//��¼���˼���
    char allr[10][9];
    char allw[10][9];
    int r = 0, w = 0;

    system("title ����ʵ�");
    system("color f4");
    system("mode con cols=120 lines=30");

    srand(time(NULL));//�����������
    putout[8] = '\0';//��������
    system("cls");
    MessageBoxA(NULL, "������ʹ�õ��ǹ��ܶ�������֪ʶ����", "ģʽѡ��", MB_OK);
    printf("���������������������������������������������������������������ԣ���������������������������������������������\n");
    printf("\nl.ϵͳ���������һ���������壬����Ҫ�������������������;\n");
    printf("\n2.ϵͳһ������10�⣬ÿ������ֻ��һ�λ�������;\n");
    printf("\n3.ÿ���ֵĴ���ʱ��Ϊ15���ӣ���ʱ���𲻼���ɼ���\n");
    printf("\n4.һ���������Ϊ10�֣�ÿ�������Ժ�ϵͳ���Զ�������������\n");
    printf("\n5.��������ϵͳ��������������壬�Թ�ѧϰ��\n");
    printf("\n������������\n\n");
    Sleep(2000);
    MessageBoxA(NULL, "���ȷ����ʼ���⡣", "������ʼ����", MB_OK);//����ʾ���Ż��û�����
    printf("����׼��\n\n3...\n\n");
    Sleep(1000);
    printf("2...\n\n");
    Sleep(1000);
    printf("1...\n\n");
    Sleep(1000);
    printf("���Կ�ʼ��");

    for (i = 1; i <= 10; i++) {
        deduct = 0;//��λ�۷����
        oneBegin = time(NULL);//ץȡ��ʼʱ��
        printf("\n\n==========��Ŀ%d����========\n\n", i);
        idx = MyRand(num);//�����������
        strcpy(putout, (wptr + idx)->word);//��ԭ����д���ַ���
        strcpy(meaning, (wptr + idx)->str);//��ԭ����д���ַ���
        puts(meaning);//�����Ŀ
        printf("\n\n������");
        rewind(stdin);//�����������ջ�����
        fgets(answer, 9, stdin);
        answer[8] = '\0';//��������
        oneEnd = time(NULL);//ץȡ�������ʱ��
        if (oneEnd - oneBegin > 30)
            deduct = 10;//��ʱֱ�ӿ�10��
        else {
            if (strcmp(answer, putout) != 0)
                deduct += 10;//�жϵ�һ���֣�����5��
        }
        if (deduct == 0) {
            strcpy(allr[r++], putout);
            printf("\n\n�ش���ȷ������Ϊ��");//ȫ�ԣ��������
            printf("\n\n %s", (wptr + idx)->str);
        }
        else {//��������
            strcpy(allw[w++], putout);
            printf("\n\n�ش������ȷ��Ϊ��%s", (wptr + idx)->word);
            printf("\n\n %s", (wptr + idx)->str);
        }
        grade -= deduct;//�������
        Sleep(1000);//ͣ��1�룬�Ż�����
    }
    system("cls");
    printf("\n\n-���Խ���-");//���������Ϣ
    printf("\n\n������%d������ܷ�Ϊ%d�֣�\n\n", grade / 10, grade);
    printf("���������:");
    for (i = 0; i < w; i++) {
        printf("%s     ", allw[i]);
    }
    printf("\n\n���Ե�����:");
    for (i = 0; i < r; i++){
        printf("%s     ", allr[i]);
    }
    return grade;//�����û�����
}

int RankingList(record* rptr) {//��ȡ���а�����
    FILE* fp;
    record* playerTemp = rptr;

    int num = 0;
    fp = fopen("ranking.txt", "r+");
    if (fp == NULL) {
        MessageBoxA(NULL, "�˳�ϵͳ", "�����ݴ���", MB_ICONSTOP | MB_OK);
        exit(0);
    }
    while (!feof(fp)) {
        fscanf(fp, "%s %d %d %d %d\n", &playerTemp->name, &playerTemp->fre, &playerTemp->score1, &playerTemp->score2, &playerTemp->nums);
        playerTemp++;
        num++;
    }
    fclose(fp);
    return num;
}

void InList(record* player, int num) {//��ʾ���а�
    int i;
    system("title ���а�");
    system("color f4");
    system("mode con cols=70 lines=20");
    record* playerTemp = player;
    printf("�û�����     ���Ҵ���     Ů洲���     ��������    �������\n");
    for (i = 0; i < num; i++, playerTemp++) {
        printf("%10s %10d %10d %10d %10d\n", playerTemp->name, playerTemp->fre, playerTemp->score1, playerTemp->score2, playerTemp->nums);
    }

}

void WriteList(record* player, record* rptr, int num) {//�����а�д������
    FILE* fp;
    int i;
    int f1ag = 1;//ȷ���Ƿ��аѱ��εĳɼ�д��
    fp = fopen("ranking.txt", "w");//�ع����а���Ϣ
    for (i = 0; i < 10; i++) {
        if ((player->score1 + player->score2) >= (rptr->score1 + rptr->score2) && f1ag == 1) {//ʹ�ü��׵Ĳ�������
            f1ag = 0;//�رտ���
            fprintf(fp, "%s %d %d %d %d", player->name, player->fre, player->score1, player->score2, player->nums);
            i++;//���ԭ�����ݵ�����һλ�û�������
        }
        fprintf(fp, "%s %d %d %d %d", rptr->name, rptr->fre, rptr->score1, player->score2, rptr->nums);
        rptr++;
   }
    fclose(fp);
}

void OutMenu(user* member) {//��¼ϵͳ����
    int judge;//�жϵ�¼��ע��
    int judge2;//�ж��Ƿ��ٴε�¼
    int judge3;//�ж��Ƿ�ע��

    judge = MessageBoxA(NULL, "��ӭ��������ɱ�������������䳡���Ƿ��¼��", "��¼ϵͳ", MB_YESNOCANCEL);
    system("title ��¼����");
    system("color f4");
    system("mode con cols=40 lines=10");
    if (judge == 6) {//ѡ���½
        while (SingIn(member) == 0) {//�ظ���¼ϵͳ��ʾ
            judge2 = MessageBoxA(NULL, "��ȷ���û��������������Ƿ���ȷ", "��¼ʧ�ܣ�", MB_ICONINFORMATION | MB_YESNOCANCEL);
            system("cls");//����
            if (judge2 == 7) {//û��ȷ�ϣ��˳�
                MessageBoxA(NULL, "��ѡ���˳�ϵͳ��", "�˳�ϵͳ", MB_ICONINFORMATION | MB_OK);
                exit(0);
            }
        }
    }
    else if (judge == 7) {
        judge3 = MessageBoxA(NULL, "ѡ���ǡ�����ע�ᣬ�����˳�����", "�Ƿ�ע�᣿", MB_YESNOCANCEL);
        if (judge3 == 7) {//û��ȷ�ϣ��˳�
            MessageBoxA(NULL, "��ѡ���˳�ϵͳ��", "�˳�ϵͳ", MB_ICONINFORMATION | MB_OK);
            exit(0);
        }
        IsRegister(member);
    }
    else {
        MessageBoxA(NULL, "��ѡ���˳�ϵͳ��", "�˳�ϵͳ", MB_ICONINFORMATION | MB_OK);
        exit(0);//ѡ��ȡ�����˳�
    }
    printf("\n\n        ���ݼ�����...   \n\n");
    system("pause");
    system("cls");
}

int SingIn(user* member) {//��¼����
    int i;
    int flag = 0;
    char ch;
    user compare;//���������Ϣ

    FILE* fp;
    fp = fopen("user.txt", "r");
    if (fp == NULL) {
        MessageBoxA(NULL, "�˳�ϵͳ", "��������", MB_ICONSTOP | MB_OK);
        exit(0);
    }
    printf("�û����� ");
    rewind(stdin);
    fgets(member->name, 6, stdin);
    for (i = 0; i < 6; i++) {
        if (member->name[i] == '\n') {
            member->name[i] = '\0';
            break;
        }
    }
    rewind(stdin);

    printf("\n���룺");
    member->password[20] = '\0';
    for (i = 0; i < 20; i++) {
        ch = getch();
        member->password[i] = ch;
        if (ch == '\r') {
            member->password[i] = '\0';
            rewind(stdin);
            break;
        }
        printf("*");
    }
    printf("\n");

    while (!(feof(fp))) {
        fscanf(fp, "%s %s\n", compare.name, compare.password);
        if (strcmp(member->name, compare.name) == 0 && strcmp(member->password, compare.password) == 0) {
            flag = 1;
            MessageBoxA(NULL, "��ӭʹ��", "��֤�ɹ�", MB_OK);
            break;
        }
    }
    fclose(fp);
    if (flag == 1) return 1;
    else if (flag == 0) return 0;
}

int IsRegister(user* member) {
    user storage;
    int i;
    int flag;


    system("title ע�����");
    system("color f4");
    system("mode con cols=50 lines=10");

    FILE* fp;
    fp = fopen("user.txt", "r+");
    if (fp == NULL) {
        MessageBoxA(NULL, "�˳�ϵͳ", "��������", MB_ICONSTOP | MB_OK);
        exit(0);
    }
    while (1) {
        flag = 1;
        printf("���������û���(������5���ַ�)��");
        fgets(member->name, 6, stdin);
        for (i = 0; i < 6; i++) {
            if (member->name[i] == '\n') {
                member->name[i] = '\0';
                break;
            }
        }
        printf("\n");
        rewind(stdin);

        while (!(feof(fp))) {//�˶��û���Ϣ����ֹ����
            fscanf(fp, "%s%s", storage.name, storage.password);
            if (strcmp(member->name, storage.name) == 0)
                flag = 0;
        }
        if (flag == 1) {
            break;
        }
        MessageBoxA(NULL, "�û����Ѵ���", "ע��ʧ��", MB_ICONEXCLAMATION | MB_OK);
        system("cls");
        rewind(stdin);
    }

    printf("�������������(������20λ)��");
    member->password[20] = '\0';
    fgets(member->password, 20, stdin);
    for (i = 0; i < 20; i++) {
        if (member->password[i] == '\n') {
            member->password[i] = '\0';
            break;
        }
    }
    rewind(stdin);

    printf("\n");
    fprintf(fp, "%s %s\n", member->name, member->password);
    MessageBoxA(NULL, "��ӭ����", "ע��ɹ�", MB_OK);

    fclose(fp);

    return flag;
}


//��ȷ����
void RightAns() {
    IMAGE rightImg;
    loadimage(&rightImg, _T("RightAns.png"), 831, 731);
    putimage(0, 0, &rightImg);
}
//��������
void Gameover(wchar_t rightAns[21][9], int rightCnt, wchar_t wrongAns[200][9], int wrongCnt) {
    IMAGE overImg1, overImg2;
    MOUSEMSG mouse;

    loadimage(&overImg1, _T("over1.png"), 1300, 561);
    putimage(0, 0, &overImg1);
    loadimage(&overImg1, _T("over2.png"), 1300, 171);
    putimage(0, 561, &overImg1);
    settextstyle(30, 0, _T("����"));
    settextcolor(BLACK);

    while (true){
        if (MouseHit() == true){
            mouse = GetMouseMsg();
            if (mouse.uMsg == WM_LBUTTONDOWN){
                if (mouse.x >= 111 && mouse.x <= 343 && mouse.y >= 573 && mouse.y <= 626){
                    IMAGE right;
                    loadimage(&right, _T("right.png"), 1300, 561);
                    putimage(0, 0, &right);
                    int idx = 0;
                    for (int i = 0; i < rightCnt; i++){
                        if (idx % 7 == 0) {
                            idx = 0;
                        }
                        outtextxy(230 + idx * 130, 141 + (i / 7) * 35, rightAns[i]);
                        idx++;
                    }
                }
                if (mouse.x >= 447 && mouse.x <= 733 && mouse.y >= 573 && mouse.y <= 626){//����������
                    //begin_menu();
                    break;
                }
                if (mouse.x >= 864 && mouse.x <= 1081 && mouse.y >= 573 && mouse.y <= 626){
                    IMAGE wrong;
                    loadimage(&wrong, _T("wrong.png"), 1300, 561);
                    putimage(0, 0, &wrong);
                    int idx = 0;
                    for (int i = 0; i < wrongCnt; i++)
                    {
                        if (idx % 7 == 0) {
                            idx = 0;
                        }
                        outtextxy(230 + idx * 130, 141 + (i / 7) * 35, wrongAns[i]);
                        idx++;
                    }
                }
            }
        }

    }

}
//��ʼ����
void begin_menu() {
    initgraph(1300, 731);
    IMAGE menu;
    loadimage(&menu, _T("begin_menu.png"), 1300, 731);
    IMAGE shuoming;
    loadimage(&shuoming, _T("introduction.png"), 1300, 731);
    putimage(0, 0, &menu);

    setbkmode(TRANSPARENT);

    MOUSEMSG mouse;
    MOUSEMSG mouse2;
    int x, y;
    int x2, y2;

    while (1) {
        mouse = GetMouseMsg();
        if (mouse.uMsg == WM_LBUTTONDOWN) {
            x = mouse.x;
            y = mouse.y;
            if (x <= 743 && x >= 452 && y >= 237 && y <= 310) {
                cleardevice;
                plays_hard();
                break;
            }else if (x <= 635 && x >= 461 && y >= 389 && y <= 465) {
                cleardevice;
                putimage(0, 0, &shuoming);
                while (1){
                    mouse2 = GetMouseMsg();
                    if (mouse2.uMsg == WM_LBUTTONDOWN) {
                        mouse2 = GetMouseMsg();
                        x2 = mouse2.x;
                        y2 = mouse2.y;
                        if (x2 <= 671 && x2 >= 483 && y2 >= 635 && y2 <= 708) {
                            putimage(0, 0, &menu);
                            break;
                        }
                    }
                    Sleep(10);
                }
                continue;
            }
        }
        Sleep(10);
    }
    closegraph();
}
// charת���ַ�
void CharToWCharT(char* putQuestion, wchar_t* wp) {
    int bufSize = MultiByteToWideChar(CP_ACP, 0, putQuestion, -1, NULL, 0);
    MultiByteToWideChar(CP_ACP, 0, putQuestion, -1, wp, bufSize);
}
//��Ļ����ʾ����
void number_write(int number_size, int x, int y, int number, COLORREF color) {
    TCHAR s[30];
    _stprintf_s(s, _T("%d"), number);
    settextstyle(number_size, 0, _T("����"));
    settextcolor(color);
    outtextxy(x, y, s);
}
//Ů洲���
void plays_hard() {
    initgraph(1300, 731);
    IMAGE ground1, ground2;
    loadimage(&ground1, _T("play_background1.png"), 831, 731);
    loadimage(&ground2, _T("play_background2.png"), 470, 731);
    putimage(0, 0, &ground1);
    putimage(831, 0, &ground2);

    EasyTextBox txtName1, txtName2; //�����
    MOUSEMSG mouse, mouse1;
    int x, y;//��������±�

    wchar_t rightAns[20][9];
    wchar_t wrongAns[20][9];//��ȷ�ʹ�����Ŀ

    int score = 0; //����
    number_write(30, 1060, 156, score, WHITE);
    int rightCnt = 0;
    number_write(30, 1060, 430, rightCnt, WHITE);
    int wrongCnt = 0;
    number_write(30, 1060, 558, wrongCnt, WHITE);

    clock_t start, end;
    clock_t pauStart = 0, pauEnd = 0, pauTime = 0;
    start = clock();

    int num; //��������
    char putQuestion[9];
    int rNum[2];
    idiom word[300]; //��ų�������
    idiom* wptr = word;
    num = GetData(wptr);

    int rand = getQuestion_hard(wptr, num, putQuestion, rNum);
    wchar_t* wp = new wchar_t[9];
    CharToWCharT(putQuestion, wp);

    setbkcolor(0xeeeeee);
    settextstyle(100, 0, _T("����"));
    settextcolor(YELLOW);
    outtextxy(370, 300, wp);

    settextcolor(BLACK);
    txtName1.Create(370 + rNum[0] * 100, 300, 470 + rNum[0] * 100, 395, 2);
    txtName2.Create(370 + rNum[1] * 100, 300, 470 + rNum[1] * 100, 395, 2);

    int count = 0;
    while (1){
        if (MouseHit() == true) {
            mouse = GetMouseMsg();
            if (mouse.uMsg == WM_LBUTTONDOWN) {
                if (mouse.x >= 956 && mouse.x <= 1200 && mouse.y >= 600 && mouse.y <= 666)
                {//��ͣ
                    outtextxy(1030, 680, L"��ͣ��");
                    pauStart = clock();
                    while (true){
                        if (MouseHit() == true) {
                            mouse1 = GetMouseMsg();
                            if (mouse1.uMsg == WM_LBUTTONDOWN) {
                                if (mouse1.x >= 956 && mouse1.x <= 1200 && mouse1.y >= 600 && mouse1.y <= 666) {
                                    pauEnd = clock();
                                    outtextxy(1030, 680, L"��Ϸ��");
                                    pauTime += (pauEnd - pauStart);
                                    break;
                                }
                            }
                        }
                    }
                }

                if (txtName1.Check(mouse.x, mouse.y))	txtName1.OnMessage(start, pauTime);
                if (txtName2.Check(mouse.x, mouse.y))	txtName2.OnMessage(start, pauTime);

                if (mouse.x >= 25 && mouse.x <= 176 && mouse.y >= 635 && mouse.y <= 704){//�˳���Ϸ
                    cleardevice;
                    begin_menu();
                }

                if (mouse.x >= 434 && mouse.x <= 602 && mouse.y >= 500 && mouse.y <= 562){//�ύ ���жϣ�
                    CharToWCharT((wptr + rand)->word, wp);
                    pauStart = clock();
                    count++;
                    if (wp[rNum[0]] != txtName1.Text() || wp[rNum[1]] != txtName2.Text())
                    {   //����
                        wcscpy(wrongAns[wrongCnt++], wp);
                        //setbkcolor(0xeeeeee);
                        settextstyle(70, 0, _T("����"));
                        settextcolor(RED);
                        outtextxy(300, 150, L"���ˣ���ȷ��:");
                        settextstyle(100, 0, _T("����"));
                        settextcolor(YELLOW);
                        outtextxy(370 + rNum[0] * 100, 300, wp[rNum[0]]);
                        outtextxy(370 + rNum[1] * 100, 300, wp[rNum[1]]);
                    }
                    else{   //��ȷ
                        score += 5;
                        wcscpy(rightAns[rightCnt++], wp);
                        RightAns();
                    }

                    Sleep(1000);
                    putimage(0, 0, &ground1);

                    rand = getQuestion_hard(wptr, num, putQuestion, rNum);
                    CharToWCharT(putQuestion, wp);

                    setbkcolor(0xeeeeee);
                    settextstyle(100, 0, _T("����"));
                    settextcolor(YELLOW);
                    outtextxy(370, 300, wp);
                    //setbkcolor(0xeeeeee);

                    settextcolor(BLACK);
                    txtName1.Create(370 + rNum[0] * 100, 300, 470 + rNum[0] * 100, 395, 2);
                    txtName2.Create(370 + rNum[1] * 100, 300, 470 + rNum[1] * 100, 395, 2);
                    pauEnd = clock();
                    pauTime += (pauEnd - pauStart);
                }
            }
        }

        if (count == 5) {
            Gameover(rightAns, rightCnt, wrongAns, wrongCnt);
            break;
        }

        end = clock();
        int time = (int)((end - start - pauTime) / CLK_TCK);
        pauStart = 0;
        pauEnd = 0;
        setbkcolor(WHITE);
        number_write(35, 1060, 275, time, BLACK);
        number_write(30, 1060, 156, score, BLACK);
        number_write(30, 1060, 430, rightCnt, BLACK);
        number_write(30, 1060, 558, wrongCnt, BLACK);
    }
}

int getQuestion_hard(idiom* wptr, int num, char question[9], int rNum[]){
    int rand;  //�����ȡ���
    int rNum1;  //�����ȥ�ĵ�һ���ֵ�λ��
    int rNum2;  //�����ȥ�Ķ����ֵ�λ��

    static int usedQues[300];

    srand(time(NULL)); //�����������
    question[8] = '\0'; // ������ƴ���ַ���

    //��֤ÿ����Ŀ��ͬ
    do {
        rand = MyRand(num);
    } while (usedQues[rand] == 1);
    //��¼�Ѿ����ֹ������
    usedQues[rand] = 1;

    strcpy(question, (wptr + rand)->word); //ԭ����д�������ַ���

    //����Ҫ��ȥ��λ�õ������
    rNum1 = MyRand(4);
    do {
        rNum2 = MyRand(4);
    } while (rNum1 == rNum2);

    //��֤rNum2����rNum1
    if (rNum2 < rNum1) {
        int temp = rNum1;
        rNum1 = rNum2;
        rNum2 = temp;
    }
    //Ҫ��ȥ�����滻Ϊ�»���
    question[2 * rNum1] = question[2 * rNum1 + 1] = '_';
    question[2 * rNum2] = question[2 * rNum2 + 1] = '_';
    rNum[0] = rNum1;
    rNum[1] = rNum2;

    return rand;
}