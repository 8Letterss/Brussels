#include"Idiom.h"

int main() {
    system("title 主界面");
    system("color f4");
    system("mode con cols=80 lines=20");
    //system("color 0B");//修改背景和字体颜色

    int num1, num2, num3;//接受成语释义数量；接受接龙成语数量；接受排行榜用户数量
    idiom word[300];   //存放成语数据
    idiom* wptr = word;
    user member;       //存放用户登录数据
    user* mptr = &member;
    record player;      //存放用户成绩数据
    record* pptr = &player;
    record rank[10];    //存放排行榜数据
    record* rptr = rank;
    max* maxptr = (max*)malloc(sizeof(max) * 100);
    max* hmaxptr = maxptr;


    printf("\n\n                               系统初始化中....    \n\n\n\n\n");
    //    cartoon();
    system("pause");
    system("cls");
    //    mciSentString("open abc.mp3 alias bkmusic",NULL,0,NULL);
    //    mciSentString("play bkmusic repeat",NULL,0,NULL);
    OutMenu(mptr);//启动登录系统
    strcpy(pptr->name, mptr->name);//导入名字信息
    num1 = GetData(wptr);//导入成语数据
    num2 = SuperGet(maxptr);
    num3 = RankingList(rptr);
    system("cls");
    //    cartoon();

    player.fre = player.score1 = player.score2 = player.nums = 0;
    while (StartGame(pptr, wptr, num1, maxptr, num3, rptr) != 0) {
        system("pause");//使用完单个功能时暂停
        system("cls");
    }
    free(maxptr);
    //WriteList(pptr, rptr, num3);
    system("cls");
    printf("\n\n                   数据上传中...   \n\n\n");
    //    cartoon();
    system("pause");
    MessageBoxA(NULL, "感谢使用", "即将推出系统", MB_ICONINFORMATION | MB_OK);

    return 0;
}

int GetData(idiom* ptr) {
    int num = 0;
    char str[200];//临时存放成语数据
    int i;
    FILE* fp;

    fp = fopen("idiom.txt", "r+");
    if (fp == NULL) {
        MessageBoxA(NULL, "退出系统", "读数据错误", MB_ICONSTOP | MB_OK);
        exit(0);
    }
    while (!feof(fp)) {
        fgets(str, 200, fp);
        for (i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
            if (str[i] == ':') {//将字符串分割为成语和释义
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

int SuperGet(max* maxptr) {//成语接龙数据读取
    int num = 0;
    char str[10];
    int i;
    FILE* fp;
    max* maxptrTemp = maxptr;

    fp = fopen("word.txt", "r+");
    if (fp == NULL) {
        MessageBoxA(NULL, "退出系统", "发生错误", MB_ICONSTOP | MB_OK);
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

int SuperSearch(max* maxptr, char str[]) {//成语接龙检索
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

int MatchingIdioms(max* maxptr, char str[]) {//匹配成语接龙
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
    int select;//存储用户选择功能
    int flag = 1;//游戏是否继续
    int select2;//存储用户选择测试模式

    system("title 开始游戏");
    system("color f4");
    system("mode con cols=45 lines=35");

    printf("==========请选择使用功能==========\n");
    printf("\n[1]成语词典\n");
    printf("\n[2]成语填空\n");
    printf("\n[3]成语接龙\n");
    printf("\n[4]排行榜\n");
    printf("\n[5]退出游戏\n");
    printf("==================================\n\n");
    scanf("%d", &select);
    rewind(stdin);//清空缓冲区

    switch (select) {
    case 1:
        player->fre += OpenDictionary(wptr, num);
        break;
    case 2:
        system("cls");
        printf("==========请选择测试模式==========\n");
        printf("\n[1]女娲补天\n");
        printf("\n[2]望文生义\n");
        printf("\n[3]返回\n");
        printf("==================================\n\n");
        scanf("%d", &select2);
        rewind(stdin);//清空缓冲区

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
            printf("\n输入错误，返回\n\n");
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
        printf("\n输入错误，返回\n\n");
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

    system("title 成语词典");
    system("color f4");
    system("mode con cols=100 lines=18");
    system("cls");
    MessageBoxA(NULL, "您正在使用的是功能一：成语词典", "模式选择", MB_OK);
    MessageBoxA(NULL, "输入你想要查询的成语，系统将在成语库中为你匹配，匹配成功将显示成语释义", "使用说明", MB_OK);
    while (judge == 1) {
        system("cls");
        printf("==========成语词典==========\n\n");
        printf("请输入想要查询的成语： ");
        rewind(stdin);
        fgets(input.word, 9, stdin);
        input.word[8] = '\0';
        idx = SeekWord(&input, wptr, num);
        if (idx == -1) {
            printf("\n(＠_＠;) 该成语还未收录哦 (＠_＠;)\n\n");
        }
        else {
            printf("\n你查找的成语意思是：\n\n  %s\n", (wptr + idx)->str);
        }
        Sleep(1000);
        judge = MessageBoxA(NULL, "是否继续查询", "提示", MB_OKCANCEL);
        if (judge == 2) {//选择取消
            judge = 0;
        }
        count++;
    }
    return count;
}

int PlayTest(idiom* wptr, int num) {
    begin_menu();

    //MessageBoxA(NULL, "您正在使用的是功能二：成语知识测试", "模式选择", MB_OK);
    //printf("＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝女娲补天成语测试＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n");
    //printf("\nl.系统会随机给出一个成语，但是会隐去两个字，你需要输入两个字来完成这个成语;\n");
    //printf("\n2.系统一共给出20题，每道题的每个字你只有一次机会作答;\n");
    //printf("\n3.每个字的答题时间为15秒钟，超时作答不计入成绩；\n");
    //printf("\n4.一个字分数为5分，每次作答以后，系统会自动结算答题情况：\n");
    
    return 0;//返回用户分数
}

int ManMachineWar(max* maxptr, int num) {//成语接龙，人机大战
    int turn = 0;//记录接龙轮次
    char putout[10];//存储“王炸”接龙成语
    char getin[10];//存储用户接龙成语
    int idx1, idx2;//接收查询结果
    int i;
    char allr[20][10];
    int r = 0;

    system("title 成语接龙");
    system("color f4");
    system("mode con cols=55 lines=44");

    srand(time(NULL));//调用随机种子
    system("cls");
    MessageBoxA(NULL, "您正在使用的是功能三：成语接龙人机大战", "模式选择", MB_OK);
    printf("==================成语接龙人机大战==================\n");
    printf("\n  接下来你将与人工智能“王炸”进行一场人机大战。\n");
    printf("\n==================================================\n");
    Sleep(2000);//用提示框显示提示信息，优化体验

    MessageBoxA(NULL, "点击确定开始人机大战。", "即将开始决战", MB_OK);
    printf("你秒杀我？\n\n");//互动，优化体验
    Sleep(1000);
    printf("你今天要是能接住我10个成语，\n\n");
    Sleep(1000);
    printf("我当场，把这个内存条吃掉 （╬￣皿￣）\n");
    Sleep(1000);
    idx1 = MyRand(15) * 2;//随机先输出初始成语
    printf("\n接招吧！%s\n", (maxptr + idx1)->word);
    strcpy(putout, (maxptr + idx1)->word);
    strcpy(allr[r++], putout);
    while (1) {
        printf("\n轮到你了：");
        rewind(stdin);//遇到输入就清空缓冲区
        fgets(getin, 9, stdin);
        getin[8] = '\0';//保护数据
        idx1 = SuperSearch(maxptr, getin);//检查用户是否作弊
        if (idx1 == -1) {//没有找到，说明不是成语，报错
            printf("\n王炸：你居然敢骗我，这根本不是成语！你输了！\n\n");
            break;
        }
        if (getin[0] != putout[6] || getin[1] != putout[7]) {//用户用成语作答，但是无法接上
            printf("\n王炸：接不上了吧，哈哈，你输了！\n\n");
            break;
        }//如果没有跳出循环，说明接龙成功，游戏继续
        turn++;//接龙轮次加
        idx2 = MatchingIdioms(maxptr, getin);
        if (idx2 == -1) {//传入最后一个字，搜索是否有成语可以接上
            printf("\n王炸：我词穷，你赢了！\n\n");
            break;
        }else {//找到，写入字符串，并输出成语，游戏继续
            strcpy(allr[r++], getin);
            strcpy(putout, (maxptr + idx2)->word);
            strcpy(allr[r++], putout);
            printf("\n王炸：这个我会接！%s\n", putout);
        }
        if (turn == 10) {
            MessageBoxA(NULL, "还是你强(╯#-_-)╯~~~~~~~~~~~~~~~~~╧═╧ ", "你赢了！", MB_OK);
            break;
        }
    }
    Sleep(2000);
    system("cls");
    printf("\n\n-----------游戏结束------------");//输出结算信息
    printf("\n\n你答对了%d个成语\n\n", turn);
    printf("成语接龙结果:");
    for (i = 0; i <r; i++) {
        printf("\n              %s    ", allr[i]);
    }
    printf("\n");
    return turn;//返回接龙轮次
}

int PlayTest2(idiom* wptr, int num) {
    int grade = 100;//初始总分100分.实行扣分制
    int i = 0;
    int oneBegin = 0; //存储用户一道题开始作答时间
    int oneEnd = 0;   //存储用户一道题结束作答时间
    char answer[9];//存储用户作答
    char putout[9];//存储输出的题目
    char meaning[200];
    int idx;//接收查询结果
    int deduct;//记录扣了几分
    char allr[10][9];
    char allw[10][9];
    int r = 0, w = 0;

    system("title 成语词典");
    system("color f4");
    system("mode con cols=120 lines=30");

    srand(time(NULL));//调用随机种子
    putout[8] = '\0';//保护数据
    system("cls");
    MessageBoxA(NULL, "您正在使用的是功能二：成语知识测试", "模式选择", MB_OK);
    printf("＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝望文生义成语测试＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n");
    printf("\nl.系统会随机给出一个成语释义，你需要根据释义输入这个成语;\n");
    printf("\n2.系统一共给出10题，每道题你只有一次机会作答;\n");
    printf("\n3.每个字的答题时间为15秒钟，超时作答不计入成绩；\n");
    printf("\n4.一个成语分数为10分，每次作答以后，系统会自动结算答题情况：\n");
    printf("\n5.无论正误，系统都会给出成语释义，以供学习。\n");
    printf("\n＝＝＝＝＝＝\n\n");
    Sleep(2000);
    MessageBoxA(NULL, "点击确定开始答题。", "即将开始测试", MB_OK);//用提示框优化用户体验
    printf("答题准备\n\n3...\n\n");
    Sleep(1000);
    printf("2...\n\n");
    Sleep(1000);
    printf("1...\n\n");
    Sleep(1000);
    printf("测试开始！");

    for (i = 1; i <= 10; i++) {
        deduct = 0;//复位扣分情况
        oneBegin = time(NULL);//抓取开始时间
        printf("\n\n==========题目%d＝＝========\n\n", i);
        idx = MyRand(num);//用随机数出题
        strcpy(putout, (wptr + idx)->word);//将原成语写入字符串
        strcpy(meaning, (wptr + idx)->str);//将原成语写入字符串
        puts(meaning);//输出题目
        printf("\n\n请作答：");
        rewind(stdin);//遇到输入就清空缓冲区
        fgets(answer, 9, stdin);
        answer[8] = '\0';//保护数据
        oneEnd = time(NULL);//抓取作答完毕时间
        if (oneEnd - oneBegin > 30)
            deduct = 10;//超时直接扣10分
        else {
            if (strcmp(answer, putout) != 0)
                deduct += 10;//判断第一个字，答错扣5分
        }
        if (deduct == 0) {
            strcpy(allr[r++], putout);
            printf("\n\n回答正确，释义为：");//全对，输出释义
            printf("\n\n %s", (wptr + idx)->str);
        }
        else {//答错，输出答案
            strcpy(allw[w++], putout);
            printf("\n\n回答错误，正确答案为：%s", (wptr + idx)->word);
            printf("\n\n %s", (wptr + idx)->str);
        }
        grade -= deduct;//计算分数
        Sleep(1000);//停顿1秒，优化体验
    }
    system("cls");
    printf("\n\n-测试结束-");//输出结算信息
    printf("\n\n你答对了%d个成语，总分为%d分！\n\n", grade / 10, grade);
    printf("你答错的题有:");
    for (i = 0; i < w; i++) {
        printf("%s     ", allw[i]);
    }
    printf("\n\n你答对的题有:");
    for (i = 0; i < r; i++){
        printf("%s     ", allr[i]);
    }
    return grade;//返回用户分数
}

int RankingList(record* rptr) {//读取排行榜数据
    FILE* fp;
    record* playerTemp = rptr;

    int num = 0;
    fp = fopen("ranking.txt", "r+");
    if (fp == NULL) {
        MessageBoxA(NULL, "退出系统", "读数据错误", MB_ICONSTOP | MB_OK);
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

void InList(record* player, int num) {//显示排行榜
    int i;
    system("title 排行榜");
    system("color f4");
    system("mode con cols=70 lines=20");
    record* playerTemp = player;
    printf("用户姓名     查找次数     女娲补天     望文生义    成语接龙\n");
    for (i = 0; i < num; i++, playerTemp++) {
        printf("%10s %10d %10d %10d %10d\n", playerTemp->name, playerTemp->fre, playerTemp->score1, playerTemp->score2, playerTemp->nums);
    }

}

void WriteList(record* player, record* rptr, int num) {//向排行榜写入数据
    FILE* fp;
    int i;
    int f1ag = 1;//确认是否有把本次的成绩写入
    fp = fopen("ranking.txt", "w");//重构排行榜信息
    for (i = 0; i < 10; i++) {
        if ((player->score1 + player->score2) >= (rptr->score1 + rptr->score2) && f1ag == 1) {//使用简易的插入排序
            f1ag = 0;//关闭开关
            fprintf(fp, "%s %d %d %d %d", player->name, player->fre, player->score1, player->score2, player->nums);
            i++;//打掉原有数据的左右一位用户的数据
        }
        fprintf(fp, "%s %d %d %d %d", rptr->name, rptr->fre, rptr->score1, player->score2, rptr->nums);
        rptr++;
   }
    fclose(fp);
}

void OutMenu(user* member) {//登录系统中枢
    int judge;//判断登录或注册
    int judge2;//判断是否再次登录
    int judge3;//判断是否注册

    judge = MessageBoxA(NULL, "欢迎来到“轰杀至渣”成语演武场！是否登录？", "登录系统", MB_YESNOCANCEL);
    system("title 登录界面");
    system("color f4");
    system("mode con cols=40 lines=10");
    if (judge == 6) {//选择登陆
        while (SingIn(member) == 0) {//重复登录系统显示
            judge2 = MessageBoxA(NULL, "请确认用户名、密码输入是否正确", "登录失败！", MB_ICONINFORMATION | MB_YESNOCANCEL);
            system("cls");//清屏
            if (judge2 == 7) {//没有确认，退出
                MessageBoxA(NULL, "你选择退出系统！", "退出系统", MB_ICONINFORMATION | MB_OK);
                exit(0);
            }
        }
    }
    else if (judge == 7) {
        judge3 = MessageBoxA(NULL, "选择“是”进入注册，否则退出程序。", "是否注册？", MB_YESNOCANCEL);
        if (judge3 == 7) {//没有确认，退出
            MessageBoxA(NULL, "你选择退出系统！", "退出系统", MB_ICONINFORMATION | MB_OK);
            exit(0);
        }
        IsRegister(member);
    }
    else {
        MessageBoxA(NULL, "你选择退出系统！", "退出系统", MB_ICONINFORMATION | MB_OK);
        exit(0);//选择取消，退出
    }
    printf("\n\n        数据加载中...   \n\n");
    system("pause");
    system("cls");
}

int SingIn(user* member) {//登录操作
    int i;
    int flag = 0;
    char ch;
    user compare;//存放输入信息

    FILE* fp;
    fp = fopen("user.txt", "r");
    if (fp == NULL) {
        MessageBoxA(NULL, "退出系统", "发生错误", MB_ICONSTOP | MB_OK);
        exit(0);
    }
    printf("用户名： ");
    rewind(stdin);
    fgets(member->name, 6, stdin);
    for (i = 0; i < 6; i++) {
        if (member->name[i] == '\n') {
            member->name[i] = '\0';
            break;
        }
    }
    rewind(stdin);

    printf("\n密码：");
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
            MessageBoxA(NULL, "欢迎使用", "验证成功", MB_OK);
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


    system("title 注册界面");
    system("color f4");
    system("mode con cols=50 lines=10");

    FILE* fp;
    fp = fopen("user.txt", "r+");
    if (fp == NULL) {
        MessageBoxA(NULL, "退出系统", "发生错误", MB_ICONSTOP | MB_OK);
        exit(0);
    }
    while (1) {
        flag = 1;
        printf("请输入新用户名(不超过5个字符)：");
        fgets(member->name, 6, stdin);
        for (i = 0; i < 6; i++) {
            if (member->name[i] == '\n') {
                member->name[i] = '\0';
                break;
            }
        }
        printf("\n");
        rewind(stdin);

        while (!(feof(fp))) {//核对用户信息，防止重名
            fscanf(fp, "%s%s", storage.name, storage.password);
            if (strcmp(member->name, storage.name) == 0)
                flag = 0;
        }
        if (flag == 1) {
            break;
        }
        MessageBoxA(NULL, "用户名已存在", "注册失败", MB_ICONEXCLAMATION | MB_OK);
        system("cls");
        rewind(stdin);
    }

    printf("请输入你的密码(不超过20位)：");
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
    MessageBoxA(NULL, "欢迎进入", "注册成功", MB_OK);

    fclose(fp);

    return flag;
}


//正确界面
void RightAns() {
    IMAGE rightImg;
    loadimage(&rightImg, _T("RightAns.png"), 831, 731);
    putimage(0, 0, &rightImg);
}
//结束界面
void Gameover(wchar_t rightAns[21][9], int rightCnt, wchar_t wrongAns[200][9], int wrongCnt) {
    IMAGE overImg1, overImg2;
    MOUSEMSG mouse;

    loadimage(&overImg1, _T("over1.png"), 1300, 561);
    putimage(0, 0, &overImg1);
    loadimage(&overImg1, _T("over2.png"), 1300, 171);
    putimage(0, 561, &overImg1);
    settextstyle(30, 0, _T("楷体"));
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
                if (mouse.x >= 447 && mouse.x <= 733 && mouse.y >= 573 && mouse.y <= 626){//返回主界面
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
//开始界面
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
// char转宽字符
void CharToWCharT(char* putQuestion, wchar_t* wp) {
    int bufSize = MultiByteToWideChar(CP_ACP, 0, putQuestion, -1, NULL, 0);
    MultiByteToWideChar(CP_ACP, 0, putQuestion, -1, wp, bufSize);
}
//屏幕上显示数字
void number_write(int number_size, int x, int y, int number, COLORREF color) {
    TCHAR s[30];
    _stprintf_s(s, _T("%d"), number);
    settextstyle(number_size, 0, _T("楷体"));
    settextcolor(color);
    outtextxy(x, y, s);
}
//女娲补天
void plays_hard() {
    initgraph(1300, 731);
    IMAGE ground1, ground2;
    loadimage(&ground1, _T("play_background1.png"), 831, 731);
    loadimage(&ground2, _T("play_background2.png"), 470, 731);
    putimage(0, 0, &ground1);
    putimage(831, 0, &ground2);

    EasyTextBox txtName1, txtName2; //答题框
    MOUSEMSG mouse, mouse1;
    int x, y;//鼠标数组下标

    wchar_t rightAns[20][9];
    wchar_t wrongAns[20][9];//正确和错误题目

    int score = 0; //分数
    number_write(30, 1060, 156, score, WHITE);
    int rightCnt = 0;
    number_write(30, 1060, 430, rightCnt, WHITE);
    int wrongCnt = 0;
    number_write(30, 1060, 558, wrongCnt, WHITE);

    clock_t start, end;
    clock_t pauStart = 0, pauEnd = 0, pauTime = 0;
    start = clock();

    int num; //成语数量
    char putQuestion[9];
    int rNum[2];
    idiom word[300]; //存放成语数据
    idiom* wptr = word;
    num = GetData(wptr);

    int rand = getQuestion_hard(wptr, num, putQuestion, rNum);
    wchar_t* wp = new wchar_t[9];
    CharToWCharT(putQuestion, wp);

    setbkcolor(0xeeeeee);
    settextstyle(100, 0, _T("楷体"));
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
                {//暂停
                    outtextxy(1030, 680, L"暂停中");
                    pauStart = clock();
                    while (true){
                        if (MouseHit() == true) {
                            mouse1 = GetMouseMsg();
                            if (mouse1.uMsg == WM_LBUTTONDOWN) {
                                if (mouse1.x >= 956 && mouse1.x <= 1200 && mouse1.y >= 600 && mouse1.y <= 666) {
                                    pauEnd = clock();
                                    outtextxy(1030, 680, L"游戏中");
                                    pauTime += (pauEnd - pauStart);
                                    break;
                                }
                            }
                        }
                    }
                }

                if (txtName1.Check(mouse.x, mouse.y))	txtName1.OnMessage(start, pauTime);
                if (txtName2.Check(mouse.x, mouse.y))	txtName2.OnMessage(start, pauTime);

                if (mouse.x >= 25 && mouse.x <= 176 && mouse.y >= 635 && mouse.y <= 704){//退出游戏
                    cleardevice;
                    begin_menu();
                }

                if (mouse.x >= 434 && mouse.x <= 602 && mouse.y >= 500 && mouse.y <= 562){//提交 （判断）
                    CharToWCharT((wptr + rand)->word, wp);
                    pauStart = clock();
                    count++;
                    if (wp[rNum[0]] != txtName1.Text() || wp[rNum[1]] != txtName2.Text())
                    {   //错误
                        wcscpy(wrongAns[wrongCnt++], wp);
                        //setbkcolor(0xeeeeee);
                        settextstyle(70, 0, _T("楷体"));
                        settextcolor(RED);
                        outtextxy(300, 150, L"错了，正确答案:");
                        settextstyle(100, 0, _T("楷体"));
                        settextcolor(YELLOW);
                        outtextxy(370 + rNum[0] * 100, 300, wp[rNum[0]]);
                        outtextxy(370 + rNum[1] * 100, 300, wp[rNum[1]]);
                    }
                    else{   //正确
                        score += 5;
                        wcscpy(rightAns[rightCnt++], wp);
                        RightAns();
                    }

                    Sleep(1000);
                    putimage(0, 0, &ground1);

                    rand = getQuestion_hard(wptr, num, putQuestion, rNum);
                    CharToWCharT(putQuestion, wp);

                    setbkcolor(0xeeeeee);
                    settextstyle(100, 0, _T("楷体"));
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
    int rand;  //随机抽取题号
    int rNum1;  //随机隐去的第一个字的位置
    int rNum2;  //随机隐去的二个字的位置

    static int usedQues[300];

    srand(time(NULL)); //调用随机种子
    question[8] = '\0'; // 将问题拼成字符串

    //保证每次题目不同
    do {
        rand = MyRand(num);
    } while (usedQues[rand] == 1);
    //记录已经出现过的题号
    usedQues[rand] = 1;

    strcpy(question, (wptr + rand)->word); //原成语写入问题字符串

    //产生要隐去的位置的随机数
    rNum1 = MyRand(4);
    do {
        rNum2 = MyRand(4);
    } while (rNum1 == rNum2);

    //保证rNum2后于rNum1
    if (rNum2 < rNum1) {
        int temp = rNum1;
        rNum1 = rNum2;
        rNum2 = temp;
    }
    //要隐去的字替换为下划线
    question[2 * rNum1] = question[2 * rNum1 + 1] = '_';
    question[2 * rNum2] = question[2 * rNum2 + 1] = '_';
    rNum[0] = rNum1;
    rNum[1] = rNum2;

    return rand;
}
