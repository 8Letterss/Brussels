import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

//左公共因子提取
public class LeftFactoring {
    private Map<String,List<String>> map = new HashMap<String,List<String>>();//左部和右部
    private ArrayList<String> charList = new ArrayList<String>();//非终结符集合
    public LeftFactoring(Map<String,List<String>> m,ArrayList<String> a){
        map =m;
        charList = a;
    }
    
    public Map<String, List<String>> getMap() {
        return map;
    }

    public ArrayList<String> getCharList() {
        return charList;
    }

    public void leftFactor(){
        int i,j,ii;
        int key=192;//构造新的产生式左部
        int end=1;//结束循环标准
        while(true){
            end = 1;
            //找出左公共因子
            for(i = 0;i<charList.size(); i++){
            	String ai=charList.get(i);
                ArrayList<String> tempProductionAi=new ArrayList<>();//记录公共因子部分或原产生式
                ArrayList<String> tempProductionAj=new ArrayList<>();//记录非公共因子部分
                List<String> productionAi = map.get(ai);//获取和ai产生式右部
                StringBuilder sb=new StringBuilder();//保存公共因子
                int flag = 1;//记录判断产生式个数
                j = 0;//记录判断公共因子个数
                if(productionAi.size() == 1)//ai只有一个产生式
                    continue;
                int ex=1;
                while(ex==1){//找出公共因子
                    flag=0;
                    Map<Character,Integer>m=new HashMap<>();//记录因子出现次数
                    int max=0;//记录因子出现个数和因子
                    char max_k='x';
                    for (ii=0;ii < productionAi.size(); ii++){
                        String current = productionAi.get(ii);//获取单个产生式右边
                        if(current.length()<=j)
                            flag++;
                        else{
                            char c=current.charAt(j);
                            if (m.containsKey(c)){//是否c在Map中
                                int temp=m.get(c);
                                temp++;
                                m.remove(c);
                                m.put(c, temp);//更新c次数
                                if(temp>max){//更新max
                                    max = temp;
                                    max_k = c;
                                    
                                }
                            }else{
                                m.put(c,1);//将c加入Map中
                                if(max<1){
                                    max = 1;
                                    max_k = c;
                                }
                            }
                        }
                    }
                    
                    if(flag==productionAi.size()){
                        break;
                    }else{
                        if(max>1)//将公共因子添加，无公共因子退出
                            sb.append(max_k);
                        else
                            ex=0;
                        j++;
                    }
                }
                
                if(sb.length()!=0) end=0;
                int add=1;//是否更新map标志
                int ises=0;//判断是否要产生e标志
                //将公共因子和非公共因子分类
                for(ii=0;ii<productionAi.size()&&sb.toString().length()!=0;ii++){
                    String current=productionAi.get(ii);
                    String common=sb.toString();
                    int tempL=common.length();//公共因子长度
                    if(current.length()>=tempL){
                        if(current.substring(0,tempL).equals(common)){//存在左公共因子
                            if(add==1){
                                String tempChar=(char)key+"";
                                tempProductionAi.add(common+tempChar);//公共因子+新非终结符
                                add=0;
                            }
                            if(current.length()>tempL)//判断是否要产生e
                                tempProductionAj.add(current.substring(tempL,current.length()));//取非公共因子
                            else {
                                ises=1;
                            }
                        }else{
                            tempProductionAi.add(current);
                        }
                    }else{
                        tempProductionAi.add(current);
                    }
                }
                //关系map
                if(add==0){
                    String tempChar=(char)key+"";
                    map.remove(ai);
                    map.put(ai,tempProductionAi);
                    map.put(tempChar,tempProductionAj);
                    charList.add(tempChar);
                    if(ises==1)
                        tempProductionAj.add("e");
                    end=0;
                }
                key++;
            }
            if(end==1)
                break;
        }
        //输出
        System.out.println("提取左公共因子后");
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
    }
    
}