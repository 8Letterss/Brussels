import java.io.*;
import java.util.*;
import static javafx.application.Platform.exit;
import static javafx.application.Platform.isImplicitExit;

public class Main {
    public static void main(String[] args) {
        Stack<String> stack = new Stack<>();//创建栈
        int i,j,k,n;
        ArrayList<String> production =new ArrayList<String>();//创建产生式列表
        Map<String,List<String>> map = new HashMap<String,List<String>>();
        ArrayList<String> charList = new ArrayList<String>();//创建非终结符列表
        Scanner scanner = null;
        try{
            scanner = new Scanner(new File("E:\\eclipse\\file\\LLParser\\input1.txt"));
        } catch (FileNotFoundException e1) {
            e1.printStackTrace();
        }
        n=0;//记录产生式个数
        if(scanner!=null){
            n= scanner.nextInt();
        }
        for(i=0;i<n;i++){
            production.add(scanner.next());
            ArrayList<String> tempProduction = new ArrayList<String>();
            String current = production.get(i);				//获取当前产生式
            String c= current.charAt(0)+"";					
            charList.add(c);								//将产生式左部非终结符加入集合
            StringBuilder stringBuilder = new StringBuilder();
            j=3;
            while(j<current.length()){
                if(current.charAt(j) == '|'){				//按|分割
                    tempProduction.add(stringBuilder.toString());
                    stringBuilder = new StringBuilder();
                }else{
                    stringBuilder.append(current.charAt(j));
                }
                j++;
            }
            tempProduction.add(stringBuilder.toString());
            map.put(c,tempProduction);						//将产生式左部与右边连接
        }
        
        LeftFactoring Lf = new LeftFactoring(map,charList);
        Lf.leftFactor();//左公共因子提取
        map=Lf.getMap();//更新提取后数据
        charList=Lf.getCharList();
        
       //消除左递归
       for(i=0;i<charList.size();i++){//按产生式左部依存分析
           String ai=charList.get(i);
           for(j=0;j<i;j++){
               String aj=charList.get(j);
               List<String> tempProductionAi=map.get(ai);
               int len=tempProductionAi.size();
               List<String> temp=new ArrayList<>();
               List<String> chk=map.get(aj+"");
               int move=0;//判断之前产生式右部头部是否与产生式左部因子相同
               for(k=0;k<chk.size();k++){
                   if(ai.equals(chk.get(k).charAt(0)+"")){
                       move=1;
                   }
               }
               
               if(move==1){//消除A->Bc;B->Ab;递归
                   for(k=0;k<len;k++){
                       if(aj.equals(tempProductionAi.get(k).charAt(0)+"")) {
                           String gama = tempProductionAi.get(k);
                           gama = gama.substring(1, gama.length());
                           List<String> tempProductionAj = map.get(aj);
                           temp.add(tempProductionAj.get(0) + gama);
                           for(int ii = 1;ii<tempProductionAj.size();ii++){
                               temp.add(tempProductionAj.get(ii) + gama);
                           }
                       }else{
                           temp.add(tempProductionAi.get(k));
                       }
                   }
                   map.remove(ai);
                   map.put(ai, temp);
               }
           }
       }
       int len=charList.size();
       int key=200;
       //消除A->Aa递归
       for(i=0;i<len;i++){
           ArrayList<String> beta=new ArrayList<>();
           ArrayList<String> alpha=new ArrayList<>();
           String ai=charList.get(i);
           List<String> productionAi=map.get(ai);
           for(j=0;j<productionAi.size();j++){
               String temp=productionAi.get(j);
               if(ai.equals(temp.charAt(0)+"")){
                   String tempKey=(char)key+"";
                   alpha.add(temp.substring(1,temp.length())+tempKey);
               }else{
                   String tempKey=(char)key+"";
                   if(temp.equals("e"))
                       temp="";
                   beta.add(temp+tempKey);
               }
           }
           
           if(beta.size() <productionAi.size()){
               String tempKey = (char)key+"";
               alpha.add("e");
               charList.add(tempKey);
               map.put(tempKey,alpha);
               map.remove(ai);
               if(beta.size()==0)
                   beta.add(tempKey);
               map.put(ai,beta);
           }
           key++;
       }
       //输出
       System.out.println("\n消除左递归");
       for(i=0;i<charList.size();i++){
            System.out.print(charList.get(i)+"-> ");
            List<String> out=map.get(charList.get(i));
            for(j=0;j< out.size();j++){
                System.out.print(out.get(j));
                if(j<out.size()-1)
                    System.out.print(" | ");
            }
            System.out.println();
        }
        
        //构造First和Follow集
        Utility.charList=charList;
        Utility.map=map;
        Utility.initialiseTerminals();
        FirstAndFollowSet Fs=new FirstAndFollowSet(map,charList);
        Fs.firstAndFollowSet();
        Map<String, ArrayList<String>> first=new HashMap<>(); // First Set
        Map<String, ArrayList<String>> follow=new HashMap<>();// Follow Set
        first = Fs.getFirst();
        follow = Fs.getFollow();
        System.out.println("\nFirst集");
        for (i = 0; i < charList.size(); i++){
            System.out.print("First(" + charList.get(i) + ") = ");
            System.out.println(first.get(charList.get(i)));
        }
        System.out.println("\nFollow集");
        for(i=0;i<charList.size();i++){
            System.out.print("Follow("+charList.get(i)+") = ");
            System.out.println(follow.get(charList.get(i)));
        }

        Scanner scanner1 = new Scanner(System.in);
        LL1Check ll1Check=new LL1Check(charList,map);
        PredictiveParser predictiveParser = new PredictiveParser(charList,map);
        predictiveParser.computeParseTable();
        if(ll1Check.isLL1()){//判断是否是LL1文法
            System.out.println("该语法是LL1文法\n");
            System.out.println("请输入要分析的句子");
            String string = scanner1.next();
            System.out.println(predictiveParser.isParseAble(string));//分析句子
        }
        else{
            System.out.println("该语法不是LL1文法");
        }
        scanner1.close();
    }
}