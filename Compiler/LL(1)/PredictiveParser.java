import java.util.*;

//预测分析
public class PredictiveParser {
    private HashMap<String,HashMap<String,String>> table = new HashMap<>();
    private Map<String,List<String>> map = new HashMap<String,List<String>>();
    private ArrayList<String> charList = new ArrayList<String>();

    public PredictiveParser(ArrayList<String> charList, Map<String, List<String>> map) {
        this.map = map;
        this.charList = charList;
    }
    
    void computeParseTable(){
        int i,j,k;
        System.out.print(" ");
        for(i=0;i<Utility.terminalList.size();i++) {
        	System.out.printf("%10s",Utility.terminalList.get(i));
        }
        System.out.println("         "+"$");
        for(i=0;i<charList.size();i++){
            String currentAi = charList.get(i);
            List<String> productionAi = map.get(currentAi);
            for (j = 0; j < productionAi.size(); j++){
                HashMap<String,String> tempArray = new HashMap<>();
                if(table.containsKey(currentAi))
                    tempArray = table.get(currentAi);
                String currentClause = productionAi.get(j);
                ArrayList<String> firstSet = Utility.firstSet(currentClause);
                for (k=0;k<firstSet.size();k++)
                {
                    if(!firstSet.get(k).equals("e"))
                    tempArray.put(firstSet.get(k),currentClause);
                }
                if (firstSet.contains("e"))
                {
                    ArrayList<String> followSet = Utility.followSet(currentAi);
                    for(k=0;k<followSet.size();k++)
                    {
                        if(!charList.contains(followSet.get(k)))
                        {
                            tempArray.put(followSet.get(k),currentClause);
                        }
                    }
                }
                table.put(currentAi,tempArray);
            }
            System.out.print(currentAi+"");
//            System.out.print("    ");
        	for(int n=0;n<Utility.terminalList.size();n++) {
            	System.out.printf("%10s",table.get(currentAi).get(Utility.terminalList.get(n)));
            }
            System.out.printf("%10s",table.get(currentAi).get("$"));
            System.out.println();
//            System.out.println(table.get(currentAi));
        }

    }
    
    //判断该句子是否正确
    boolean isParseAble(String input){
        int i,j;
        boolean out =false;
        Stack<String> stack = new Stack<>();
        stack.push("$");
        stack.push(charList.get(0));
        input = input+"$";
        i=0;
        String str = "";
        while (i<input.length()){
            String current = input.charAt(i)+"";
            String topStack = stack.peek();
            if(topStack.equals("$") && current.equals("$")){
                out = true;
                break;
            }else if(topStack.equals(current)){
            	str+=current+"";
            	System.out.printf("匹配 %s\t\t",current);
                stack.pop();
                i++;
            }else{
                if(table.containsKey(topStack)){
                    if(table.get(topStack).containsKey(current)){
                        String tempProduction = table.get(topStack).get(current);
                        StringBuilder stringBuilder = new StringBuilder(tempProduction);
                        stringBuilder =stringBuilder.reverse();
                        tempProduction = stringBuilder.toString();
                        stack.pop();
                        if(!tempProduction.equals("e")){
                        	System.out.printf("输出 %s->",topStack);
                            for (j=0;j<tempProduction.length();j++){
                                //stack.add(tempProduction);
                                stack.push(tempProduction.charAt(j)+"");
                                System.out.printf("%s",tempProduction.charAt(j));
                            }
                            System.out.print("\t");
                        }else {
                        	System.out.printf("输出 %s->e\t",topStack);
                        }
                    }
                    else{
                        out = false;
                        break;
                    }
                }
                else{
                    out = false;
                    break;
                }
            }

            System.out.printf("%-30s",stack);
            System.out.printf("已匹配:%-15s\t",str);
            String tt;
            int mm=input.indexOf(str);
            tt=input.substring(0,mm)+input.substring(str.length());
            System.out.printf("%10s\n",tt);
        }
        return out;
    }
}