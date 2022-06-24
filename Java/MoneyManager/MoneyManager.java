import java.awt.*;
import java.awt.event.*;
import java.sql.*;
import javax.swing.*;
import java.io.*;
import java.util.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

//空值判断
//日期格式
//删除、修改确定
//收入、支出计算
//修改密码：原密码正确、两次密码一致且与原密码不同

public class MoneyManager {
	public static void main(String[] args) {
		 LoginFrame lf=new LoginFrame();
		 lf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}

//登录界面
class LoginFrame extends JFrame implements ActionListener{
	private JLabel l_user,l_pwd; //用户名标签，密码标签
	private JTextField t_user;//用户名文本框
	private JPasswordField t_pwd; //密码文本框
	private JButton b_ok,b_cancel; //登录按钮，退出按钮
	
	public LoginFrame(){
		super("欢迎使用个人理财账本!");
		l_user=new JLabel("用户名：",JLabel.RIGHT);
		l_pwd=new JLabel(" 密码：",JLabel.RIGHT);
		t_user=new JTextField(31);
		t_pwd=new JPasswordField(31);
		b_ok=new JButton("登录");
		b_cancel=new JButton("退出");
		
		//布局方式FlowLayout，一行排满排下一行
		Container c=this.getContentPane();
		c.setLayout(new FlowLayout()); 
		c.add(l_user);
		c.add(t_user);
		c.add(l_pwd);
		c.add(t_pwd);
		c.add(b_ok);
		c.add(b_cancel);
		//为按钮添加监听事件
		b_ok.addActionListener(this);
		b_cancel.addActionListener(this);
        //界面大小不可调整 
		this.setResizable(false);
		this.setSize(455,150);
		//界面显示居中
		Dimension screen = this.getToolkit().getScreenSize();
	    this.setLocation((screen.width-this.getSize().width)/2,(screen.height-this.getSize().height)/2);
		this.setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e) {
		if(b_cancel==e.getSource()){
		    //添加退出代码
			System.exit(0);
		}else if(b_ok==e.getSource()){
            //添加代码，验证身份成功后显示主界面
		    try {
		    	FileReader fr=new FileReader("E:/pwd.txt");
		    	BufferedReader br=new BufferedReader(fr);
		    	String user=br.readLine();
		    	String upwd=br.readLine();
		    	br.close();
		    	fr.close();
		    	if(t_user.getText().isEmpty() ||t_pwd.getText().isEmpty()) {
		    		JOptionPane.showMessageDialog(null,"用户名密码不能为空", "警告", JOptionPane.ERROR_MESSAGE);
		    	}else if(t_user.getText().trim().equals(user)&&new String(t_pwd.getPassword()).equals(upwd)){
		    		new MainFrame(t_user.getText().trim());
		    	}else{
		    		JOptionPane.showMessageDialog(null,"用户名密码出错", "警告", JOptionPane.ERROR_MESSAGE);
		    	}
//	    	}catch(FileNotFoundException e1) {
//		 		e1.printStackTrace();
		 	}catch(IOException e1) {
		 		JOptionPane.showMessageDialog(null,"读取错误", "警告", JOptionPane.ERROR_MESSAGE);
		 		e1.printStackTrace();
		 	}catch (Exception e1) {
		 		e1.printStackTrace();
		 	}
		}
		
	}	
	
}

//主界面
class MainFrame extends JFrame implements ActionListener{
	private JMenuBar mb=new JMenuBar();
	private JMenu m_system=new JMenu("系统管理");
	private JMenu m_fm=new JMenu("收支管理");
	private JMenuItem mI[]={new JMenuItem("密码重置"),new JMenuItem("退出系统")};
	private JMenuItem m_FMEdit=new JMenuItem("收支编辑");
	private JLabel l_type,l_fromdate,l_todate,l_bal,l_ps;  
	private JTextField t_fromdate,t_todate; 
	//private JButton t_fromdate,t_todate;
	private JButton b_select1,b_select2;
	private JComboBox c_type;
	private JPanel p_condition,p_detail;
	private String s1[]={"收入","支出"};
	private double bal1,bal2;	
	private JTable table;
	private String username;
	
	public MainFrame(String username){
		super(username+",欢迎使用个人理财账本!");
		this.username=username;
		Container c=this.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(mb,"North");
		mb.add(m_system);
		mb.add(m_fm);
		m_system.add(mI[0]);
		m_system.add(mI[1]);
		m_fm.add(m_FMEdit);
		m_FMEdit.addActionListener(this);
	    mI[0].addActionListener(this);
	    mI[1].addActionListener(this);
	    
	    l_type=new JLabel("收支类型：");	
	    c_type=new JComboBox(s1);
	    b_select1=new JButton("查询");
		l_fromdate=new JLabel("起始时间");
        t_fromdate=new JTextField(8);
		l_todate=new JLabel("终止时间");
        t_todate=new JTextField(8);
		b_select2=new JButton("查询");
		l_ps = new JLabel("注意：时间格式为YYYY-MM-DD，例如：2015-09-01");
		p_condition=new JPanel();
		p_condition.setLayout(new GridLayout(3,1));
		p_condition.setBorder(BorderFactory.createCompoundBorder(
	    BorderFactory.createTitledBorder("输入查询条件"), 
	    BorderFactory.createEmptyBorder(5,5,5,5)));
		
		JPanel p1 = new JPanel();
	    JPanel p2 = new JPanel();
	    JPanel p3 = new JPanel();
	    p1.add(l_type);
	    p1.add(c_type);
	    p1.add(b_select1);
	    p2.add(l_fromdate);
		p2.add(t_fromdate);
		p2.add(l_todate);
		p2.add(t_todate);
		p2.add(b_select2);
		p3.add(l_ps);
		p_condition.add(p1);
	    p_condition.add(p2);
	    p_condition.add(p3);
        c.add(p_condition,"Center");
        
        b_select1.addActionListener(this);
        b_select2.addActionListener(this);
        
        p_detail=new JPanel();
        p_detail.setBorder(BorderFactory.createCompoundBorder(
	    BorderFactory.createTitledBorder("收支明细信息"), 
	    BorderFactory.createEmptyBorder(5,5,5,5)));
        l_bal=new JLabel();
        String[] cloum = {"编号", "日期", "类型","内容","金额",};
		Object[][] row = new Object[50][5];
		
		table = new JTable(row, cloum);
		JScrollPane scrollpane = new JScrollPane(table);
		scrollpane.setPreferredSize(new Dimension(580,350));
		scrollpane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		scrollpane.setViewportView(table);
		p_detail.add(l_bal);
		p_detail.add(scrollpane);
		c.add(p_detail,"South");
		
		//添加代码
		method m=new method();
		m.showDetail(row);
		
		bal1=0;
		double b;
		ArrayList<MyAccount> a1=new ArrayList<MyAccount>();
		a1=m.loadList(a1);
		for(int i=0;i<a1.size();i++) {
			b=Double.parseDouble(a1.get(i).getAmount());
			if(a1.get(i).getType().equals("收入")) {				
				bal1+=b;
			}else {
				bal1-=b;
			}
		}

	    if(bal1<0)
		    l_bal.setText("个人总收支余额为"+bal1+"元。您已超支，请适度消费！");	
		else  		
			l_bal.setText("个人总收支余额为"+bal1+"元。");   					 	
        this.setResizable(false);
		this.setSize(600,580);
		Dimension screen = this.getToolkit().getScreenSize();
	    this.setLocation((screen.width-this.getSize().width)/2,(screen.height-this.getSize().height)/2);
		this.setVisible(true);
	}
	
	//主界面构造函数重载
	public MainFrame(String username,ArrayList<MyAccount> a1){
		super(username+",欢迎使用个人理财账本!");
		this.username=username;
		Container c=this.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(mb,"North");
		mb.add(m_system);
		mb.add(m_fm);
		m_system.add(mI[0]);
		m_system.add(mI[1]);
		m_fm.add(m_FMEdit);
		m_FMEdit.addActionListener(this);
	    mI[0].addActionListener(this);
	    mI[1].addActionListener(this);
	    
	    l_type=new JLabel("收支类型：");	
	    c_type=new JComboBox(s1);
	    b_select1=new JButton("查询");
		l_fromdate=new JLabel("起始时间");
        t_fromdate=new JTextField(8);
		l_todate=new JLabel("终止时间");
        t_todate=new JTextField(8);
		b_select2=new JButton("查询");
		l_ps = new JLabel("注意：时间格式为YYYY-MM-DD，例如：2015-09-01");
		p_condition=new JPanel();
		p_condition.setLayout(new GridLayout(3,1));
		p_condition.setBorder(BorderFactory.createCompoundBorder(
	    BorderFactory.createTitledBorder("输入查询条件"), 
	    BorderFactory.createEmptyBorder(5,5,5,5)));
		
		JPanel p1 = new JPanel();
	    JPanel p2 = new JPanel();
	    JPanel p3 = new JPanel();
	    p1.add(l_type);
	    p1.add(c_type);
	    p1.add(b_select1);
	    p2.add(l_fromdate);
		p2.add(t_fromdate);
		p2.add(l_todate);
		p2.add(t_todate);
		p2.add(b_select2);
		p3.add(l_ps);
		p_condition.add(p1);
	    p_condition.add(p2);
	    p_condition.add(p3);
        c.add(p_condition,"Center");
        
        b_select1.addActionListener(this);
        b_select2.addActionListener(this);
        
        p_detail=new JPanel();
        p_detail.setBorder(BorderFactory.createCompoundBorder(
	    BorderFactory.createTitledBorder("收支明细信息"), 
	    BorderFactory.createEmptyBorder(5,5,5,5)));
        l_bal=new JLabel();
        String[] cloum = {"编号", "日期", "类型","内容","金额",};
		Object[][] row = new Object[50][5];
		
		table = new JTable(row, cloum);
		JScrollPane scrollpane = new JScrollPane(table);
		scrollpane.setPreferredSize(new Dimension(580,350));
		scrollpane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		scrollpane.setViewportView(table);
		p_detail.add(l_bal);
		p_detail.add(scrollpane);
		c.add(p_detail,"South");
		
		//添加代码
		//主界面显示
		method m=new method();
		m.showDetail(row, a1);
		//
		bal1=0;
		double b;
		a1=m.loadList(a1);
		for(int i=0;i<a1.size();i++) {
			b=Double.parseDouble(a1.get(i).getAmount());
			if(a1.get(i).getType().equals("收入")) {				
				bal1+=b;
			}else {
				bal1-=b;
			}
		}
		
	    if(bal1<0)
		    l_bal.setText("个人总收支余额为"+bal1+"元。您已超支，请适度消费！");	
		else  		
			l_bal.setText("个人总收支余额为"+bal1+"元。");   				
		 	
        this.setResizable(false);
		this.setSize(600,580);
		Dimension screen = this.getToolkit().getScreenSize();
	    this.setLocation((screen.width-this.getSize().width)/2,(screen.height-this.getSize().height)/2);
		this.show();
		this.setVisible(true);
	}

    public void actionPerformed(ActionEvent e) {
	     Object temp=e.getSource();
	     if(temp==mI[0]){
	    	new ModifyPwdFrame(username);
	     }else if(temp==mI[1]){
	    	//添加代码
	    	 System.exit(0);
	     }else if(temp==m_FMEdit){
	    	new BalEditFrame();
	     }else if(temp==b_select1){  //根据收支类型查询	 
	    	//添加代码
	    	 this.dispatchEvent(new WindowEvent(this,WindowEvent.WINDOW_CLOSING) );
	    	 //创建方法类，获得数据
	    	 method m=new method();
	    	 ArrayList<MyAccount> a1=new ArrayList<MyAccount>();
	    	 a1=m.loadList(a1);
	    	 ArrayList<MyAccount> a2=new ArrayList<MyAccount>();//收入
	    	 ArrayList<MyAccount> a3=new ArrayList<MyAccount>();//支出
	    	 double income=0;
	    	 double expend=0;
	    	 for(int i=0;i<a1.size();i++){
	    		 if(a1.get(i).getType().equals("收入")) {
	    			 a2.add(a1.get(i));
	    			 income+=Double.parseDouble(a1.get(i).getAmount());
    			 }else {
    				 a3.add(a1.get(i));
    				 expend+=Double.parseDouble(a1.get(i).getAmount());
    			 }
    		 }
	    	 if(c_type.getSelectedItem().toString().equals("收入")) {
	    		 new MainFrame("Tom",a2);
	    		 JOptionPane.showMessageDialog(null,"总收入为： "+income, "提示", 1);
    		 }else {
    			 new MainFrame("Tom",a3);
    			 JOptionPane.showMessageDialog(null,"总支出为： "+expend, "提示", 1);
    		 }
	     }else if(temp==b_select2){   //根据时间范围查询		 
	    	 //添加代码
	    	 this.dispatchEvent(new WindowEvent(this,WindowEvent.WINDOW_CLOSING) );
	    	 //添加方法类
	    	 method m=new method();
	    	 ArrayList<MyAccount> a1=new ArrayList<MyAccount>();
	    	 a1=m.loadList(a1);
	    	 //按时间获得所需数据，并查询
	    	 int flag=1;
	    	 int flag2=1;
    		 Date datef=new Date();
    		 Date datet=new Date();
    		 if(t_fromdate.getText().isEmpty()||t_todate.getText().isEmpty()){
	    		 flag2=0;
	    	 	 JOptionPane.showMessageDialog(null,"日期输入不能为空", "警告", JOptionPane.ERROR_MESSAGE);
	    	 }else{
	    		 String from=t_fromdate.getText();
		    	 String to=t_todate.getText();
		    	 SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
		    	 try{ 
		    		 datef=sdf.parse(from);
		    		 datet=sdf.parse(to);
		    	 }catch(Exception ei){
		    		 flag2=0;
	    			 JOptionPane.showMessageDialog(null,"日期输入格式错误", "警告", JOptionPane.ERROR_MESSAGE);
	    		 }
	    	 }
	    	 if(flag2==0) {
    			 new MainFrame("Tom");
	    	 }else {
		    	 ArrayList<MyAccount> a2=new ArrayList<MyAccount>();
		    	 for(int i=0;i<a1.size();i++) {
	    			 if(a1.get(i).getDate().compareTo(datef)>=0&&a1.get(i).getDate().compareTo(datet)<=0) {
	    			 a2.add(a1.get(i));
	    			 }
		    	 }	    		 
	    		 new MainFrame("Tom",a2);
	    	 }
	     }
     }
}

//修改密码界面
class ModifyPwdFrame extends JFrame implements ActionListener{
	private JLabel l_oldPWD,l_newPWD,l_newPWDAgain;
	private JPasswordField t_oldPWD,t_newPWD,t_newPWDAgain;
	private JButton b_ok,b_cancel;
	private String username;
	
	public ModifyPwdFrame(String username){
		super("修改密码");
		this.username=username;
		l_oldPWD=new JLabel("旧密码");
		l_newPWD=new JLabel("新密码：");
		l_newPWDAgain=new JLabel("确认新密码：");
		t_oldPWD=new JPasswordField(15);
		t_newPWD=new JPasswordField(15);
		t_newPWDAgain=new JPasswordField(15);
		b_ok=new JButton("确定");
		b_cancel=new JButton("取消");
		Container c=this.getContentPane();
		c.setLayout(new FlowLayout());
		c.add(l_oldPWD);
		c.add(t_oldPWD);
		c.add(l_newPWD);
		c.add(t_newPWD);
		c.add(l_newPWDAgain);
		c.add(t_newPWDAgain);
		c.add(b_ok);
		c.add(b_cancel);
		b_ok.addActionListener(this);
		b_cancel.addActionListener(this);
		this.setResizable(false);
		this.setSize(280,160);
		Dimension screen = this.getToolkit().getScreenSize();
	    this.setLocation((screen.width-this.getSize().width)/2,(screen.height-this.getSize().height)/2);
		this.setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e) {
		if(b_cancel==e.getSource()){
			//this.dispose();
			//添加代码
			this.dispatchEvent(new WindowEvent(this,WindowEvent.WINDOW_CLOSING) );
		}else if(b_ok==e.getSource()){  //修改密码
			//添加代码
			try {
				boolean judge=true;
				BufferedReader br=new BufferedReader(new FileReader("E:/pwd.txt"));
				String user=br.readLine();
				String s= br.readLine();
				if(new String(t_oldPWD.getPassword()).equals(s)==false){
					JOptionPane.showMessageDialog(null,"原密码错误", "警告", JOptionPane.ERROR_MESSAGE);
					judge=false;
				}
				if(new String(t_newPWD.getPassword()).equals(s)){
					JOptionPane.showMessageDialog(null,"新密码与原密码一样", "警告", JOptionPane.ERROR_MESSAGE);
					judge=false;
				}
				if(new String(t_newPWDAgain.getPassword()).contentEquals(new String(t_newPWD.getPassword()))&&judge==true){
					PrintWriter p=new PrintWriter(new BufferedWriter(new FileWriter("e:/pwd.txt")));
					p.println(user);
					p.println(t_newPWD.getPassword());
					p.close();
					JOptionPane.showMessageDialog(null, "修改密码成功","提醒",JOptionPane.INFORMATION_MESSAGE);
					this.dispatchEvent(new WindowEvent(this,WindowEvent.WINDOW_CLOSING) );
					System.exit(0);
				}else if(judge==true&&new String(t_newPWDAgain.getPassword()).contentEquals(new String(t_newPWD.getPassword()))==false) {
					JOptionPane.showMessageDialog(null,"两次新密码不一致！", "警告", JOptionPane.ERROR_MESSAGE);	
				}
				br.close();
			}catch (FileNotFoundException e1) {
				e1.printStackTrace();
			} catch(IOException e1) {
				e1.printStackTrace();
			} catch (Exception e1) {
				e1.printStackTrace();
			}
		}
	}
}

//收支编辑界面
class BalEditFrame extends JFrame implements ActionListener{
	private JLabel l_id,l_date,l_bal,l_type,l_item;
	private JTextField t_id,t_date,t_bal;
	private JComboBox c_type,c_item;
	private JButton b_update,b_delete,b_select,b_new,b_clear;
	private JPanel p1,p2,p3;
	private JScrollPane scrollpane;
	private JTable table;

	public BalEditFrame(){
		super("收支编辑" );
		l_id=new JLabel("编号：");
		l_date=new JLabel("日期：");
		l_bal=new JLabel("金额：");
		l_type=new JLabel("类型：");
		l_item=new JLabel("内容：");
		t_id=new JTextField(8);
		t_date=new JTextField(8);
		t_bal=new JTextField(8);

		String s1[]={"收入","支出"};
		String s2[]={"购物","餐饮","居家","交通","娱乐","人情","工资","奖金","其他"};
		c_type=new JComboBox(s1);
		c_item=new JComboBox(s2);
		
		b_select=new JButton("查询");
		b_update=new JButton("修改");
		b_delete=new JButton("删除");
		b_new=new JButton("录入");
		b_clear=new JButton("清空");
		
		Container c=this.getContentPane();
		c.setLayout(new BorderLayout());
		
		p1=new JPanel();
        p1.setLayout(new GridLayout(5,2,10,10));
        p1.setBorder(BorderFactory.createCompoundBorder(
        BorderFactory.createTitledBorder("编辑收支信息"), 
        BorderFactory.createEmptyBorder(5,5,5,5)));
		p1.add(l_id);
		p1.add(t_id);
		p1.add(l_date);
		p1.add(t_date);
		p1.add(l_type);
		p1.add(c_type);
		p1.add(l_item);
		p1.add(c_item);
		p1.add(l_bal);
		p1.add(t_bal);
		c.add(p1, BorderLayout.WEST);
		
		p2=new JPanel();
		p2.setLayout(new GridLayout(5,1,10,10));
		p2.add(b_new);
		p2.add(b_update);
		p2.add(b_delete);
		p2.add(b_select);
		p2.add(b_clear);
		c.add(p2,BorderLayout.CENTER);	
		
		p3=new JPanel();
		p3.setBorder(BorderFactory.createCompoundBorder(
		BorderFactory.createTitledBorder("显示收支信息"), 
		BorderFactory.createEmptyBorder(5,5,5,5)));
		
		String[] cloum = { "编号", "日期", "类型","内容", "金额"};
		Object[][] row = new Object[50][5];
		
		method m=new method();
		m.showDetail(row);
		table = new JTable(row, cloum);
		scrollpane = new JScrollPane(table);
		scrollpane.setViewportView(table);
		scrollpane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		p3.add(scrollpane);
		c.add(p3,BorderLayout.EAST);		
	 
		b_update.addActionListener(this);
		b_delete.addActionListener(this);
		b_select.addActionListener(this);
		b_new.addActionListener(this);
		b_clear.addActionListener(this);
		
		//添加代码，为table添加鼠标点击事件监听addMouseListener
		table.addMouseListener(new MouseAdapter(){			
			public void mouseClicked(MouseEvent e) {
//				仅当鼠标单击时响应
//				得到选中的行列的索引值
//              得到选中的单元格的值，表格中都是字符串
				int a= table.getSelectedRow();
            	t_id.setText(row[a][0].toString());
            	t_date.setText(row[a][1].toString());
            	c_type.setSelectedItem(row[a][2].toString());  
            	c_item.setSelectedItem(row[a][3].toString());
            	t_bal.setText(row[a][4].toString());            	
            }
        }
		);
	    this.setResizable(false);
		this.setSize(800,300);
		Dimension screen = this.getToolkit().getScreenSize();
	    this.setLocation((screen.width-this.getSize().width)/2,(screen.height-this.getSize().height)/2);
		this.setVisible(true);;
	}
	
	//收支界面构造函数重载，用于刷新收支界面
	public BalEditFrame(ArrayList<MyAccount> a1){
		super("收支编辑" );
		l_id=new JLabel("编号：");
		l_date=new JLabel("日期：");
		l_bal=new JLabel("金额：");
		l_type=new JLabel("类型：");
		l_item=new JLabel("内容：");
		t_id=new JTextField(8);
		t_date=new JTextField(8);
		t_bal=new JTextField(8);

		String s1[]={"收入","支出"};
		String s2[]={"购物","餐饮","居家","交通","娱乐","人情","工资","奖金","其他"};
		c_type=new JComboBox(s1);
		c_item=new JComboBox(s2);
		
		b_select=new JButton("查询");
		b_update=new JButton("修改");
		b_delete=new JButton("删除");
		b_new=new JButton("录入");
		b_clear=new JButton("清空");
		
		Container c=this.getContentPane();
		c.setLayout(new BorderLayout());
		
		p1=new JPanel();
        p1.setLayout(new GridLayout(5,2,10,10));
        p1.setBorder(BorderFactory.createCompoundBorder(
        BorderFactory.createTitledBorder("编辑收支信息"), 
        BorderFactory.createEmptyBorder(5,5,5,5)));
		p1.add(l_id);
		p1.add(t_id);
		p1.add(l_date);
		p1.add(t_date);
		p1.add(l_type);
		p1.add(c_type);
		p1.add(l_item);
		p1.add(c_item);
		p1.add(l_bal);
		p1.add(t_bal);
		c.add(p1, BorderLayout.WEST);
		
		p2=new JPanel();
		p2.setLayout(new GridLayout(5,1,10,10));
		p2.add(b_new);
		p2.add(b_update);
		p2.add(b_delete);
		p2.add(b_select);
		p2.add(b_clear);
	    
		c.add(p2,BorderLayout.CENTER);	
		
		p3=new JPanel();
		p3.setBorder(BorderFactory.createCompoundBorder(
		BorderFactory.createTitledBorder("显示收支信息"), 
		BorderFactory.createEmptyBorder(5,5,5,5)));		
				
		String[] cloum = { "编号", "日期", "类型","内容", "金额"};
		Object[][] row = new Object[50][5];		
		
		//创建方法类
		method m=new method();
		//显示信息			
		m.showDetail(row,a1);
		//
		table = new JTable(row, cloum);
		scrollpane = new JScrollPane(table);
		scrollpane.setViewportView(table);
		scrollpane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		p3.add(scrollpane);
		c.add(p3,BorderLayout.EAST);		
	 
		b_update.addActionListener(this);
		b_delete.addActionListener(this);
		b_select.addActionListener(this);
		b_new.addActionListener(this);
		b_clear.addActionListener(this);
		
		//添加代码，为table添加鼠标点击事件监听addMouseListener
		table.addMouseListener(new MouseAdapter(){			
			public void mouseClicked(MouseEvent e) {
//					仅当鼠标单击时响应
//					得到选中的行列的索引值
//	              得到选中的单元格的值，表格中都是字符串
				int a= table.getSelectedRow();
            	t_id.setText(row[a][0].toString());
            	t_date.setText(row[a][1].toString()); 
            	c_type.setSelectedItem(row[a][2].toString());  
            	c_item.setSelectedItem(row[a][3].toString());
            	t_bal.setText(row[a][4].toString());  
            	t_id.setEditable(false);
            }
        }
		);
		
	    this.setResizable(false);
		this.setSize(800,300);
		Dimension screen = this.getToolkit().getScreenSize();
	    this.setLocation((screen.width-this.getSize().width)/2,(screen.height-this.getSize().height)/2);
		this.setVisible(true);
	}

	public void actionPerformed(ActionEvent e) {
		if(b_select==e.getSource()){  //查询所有收支信息
			//添加代码
			this.dispatchEvent(new WindowEvent(this,WindowEvent.WINDOW_CLOSING) );
			new BalEditFrame();
		}else if(b_update==e.getSource()){  // 修改某条收支信息
			//添加代码
			final int op=0;
			if(op==JOptionPane.showConfirmDialog(null,"确定修改？", "提示",JOptionPane.OK_CANCEL_OPTION))
			{
				method m=new method();
				ArrayList<MyAccount> a1=new ArrayList<MyAccount>();
				a1=m.loadList(a1);
				SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
				int b=Integer.parseInt(t_id.getText());
				a1.remove(b-1);
				try {
					a1.add(b-1,new MyAccount(t_id.getText(),sdf.parse(t_date.getText()),c_type.getSelectedItem().toString(),c_item.getSelectedItem().toString(),t_bal.getText()));
				}catch (ParseException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
					JOptionPane.showMessageDialog(null,"日期输入格式错误", "警告", JOptionPane.ERROR_MESSAGE);
				}
				this.dispatchEvent(new WindowEvent(this,WindowEvent.WINDOW_CLOSING) );	
				m.delete();
				m.update(a1);
				a1=m.loadList(a1);			
				new BalEditFrame(a1);
			}
		}else if(b_delete==e.getSource()){   //删除某条收支信息
			//添加代码
			final int op=0;
			if(op==JOptionPane.showConfirmDialog(null,"确定修改？", "提示",JOptionPane.OK_CANCEL_OPTION))
			{
				//写的方法类
				method m=new method();
				ArrayList<MyAccount> a1=new ArrayList<MyAccount>();
				//方法读取文件对象，返回一个ArrayList<MyAccount>
				a1=m.loadList(a1);
				//读取编号项
				int b=Integer.parseInt(t_id.getText());
				//删除对应项
				a1.remove(b-1);
				//删除原界面
				this.dispatchEvent(new WindowEvent(this,WindowEvent.WINDOW_CLOSING) );
				//删除原文件，构建新文件
				m.delete();
				m.update(a1);
				//同步更新编辑界面
				a1=m.loadList(a1);			
				new BalEditFrame(a1);			
				//添加代码	
			}			
		}else if(b_new==e.getSource()){   //新增某条收支信息 	
			//添加代码
			SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
			method m=new method();
			ArrayList<MyAccount> a1=new ArrayList<MyAccount>();
			a1=m.loadList(a1);
			int flag=1;
			for(int i=0;i<a1.size();i++) {
				if(t_id.getText().equals(a1.get(i).getId())){					
					flag=0;
					break;
				}				
			}
			if(flag==1) {
				if(t_id.getText().isEmpty()||t_date.getText().isEmpty()||t_bal.getText().isEmpty()) {
					JOptionPane.showMessageDialog(null,"输入不能为空", "警告", JOptionPane.ERROR_MESSAGE);
				}else {
					try {
						a1.add(new MyAccount(t_id.getText(),sdf.parse(t_date.getText()),c_type.getSelectedItem().toString(),c_item.getSelectedItem().toString(),t_bal.getText()));
					} catch (ParseException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
						JOptionPane.showMessageDialog(null,"日期输入格式错误", "警告", JOptionPane.ERROR_MESSAGE);
					}	
				}
			}else {
				JOptionPane.showMessageDialog(null,"id重复，重新编辑", "警告", JOptionPane.ERROR_MESSAGE);
			}			
			this.dispatchEvent(new WindowEvent(this,WindowEvent.WINDOW_CLOSING) );
			m.delete();
			m.update(a1);
			//同步更新编辑界面			
			a1=m.loadList(a1);
			new BalEditFrame(a1);
		}else if(b_clear==e.getSource()){   //清空输入框
			//添加代码
			method m=new method();
			ArrayList<MyAccount> a1=new ArrayList<MyAccount>();	
			a1=m.loadList(a1);
			this.dispatchEvent(new WindowEvent(this,WindowEvent.WINDOW_CLOSING) );
			new BalEditFrame(a1);
		}	
	}
}


class method{
	//对主界面构造函数数组进行赋值
	@SuppressWarnings("unchecked")
	public Object showDetail(Object row[][]) {
		ArrayList<MyAccount> a1=new  ArrayList<MyAccount>();
		try {
			FileInputStream fis=new FileInputStream("E:/xu.txt");
			ObjectInputStream ois=new ObjectInputStream(fis);
			a1=(ArrayList<MyAccount>)(ois.readObject());
			ois.close();
			fis.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();				
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}catch(Exception e) {
			e.printStackTrace();
		}
		SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		for(int i=0;i<a1.size();i++) {
			row[i][0]=a1.get(i).getId();
			row[i][1]=sdf.format(a1.get(i).getDate());
		 	row[i][2]=a1.get(i).getType();
		    row[i][3]=a1.get(i).getContent();
		    row[i][4]=a1.get(i).getAmount();
		}
		return row;
	}
	
	//对主界面构造函数数组赋值
	public Object showDetail(Object row[][],ArrayList<MyAccount> al) {
		SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd");
		for(int i=0;i<al.size();i++) {
			row[i][0]=al.get(i).getId();
			row[i][1]=sdf.format(al.get(i).getDate());
		 	row[i][2]=al.get(i).getType();
		    row[i][3]=al.get(i).getContent();
		    row[i][4]=al.get(i).getAmount();
		}
		return row;
	}
	
	//加载目标文件信息，并以ArrayList<MyAccount>形式返回
	@SuppressWarnings("unchecked")
	public ArrayList<MyAccount> loadList(ArrayList<MyAccount> a1) {			
			try {
				FileInputStream fis= new FileInputStream("E:/xu.txt");
				ObjectInputStream ois=new ObjectInputStream(fis);
				a1=(ArrayList<MyAccount>)(ois.readObject());
				ois.close();
				fis.close();				
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			} catch (Exception e) {
				e.printStackTrace();
			}
			return a1;
	}
	
	//用于删除原文件
	public void delete() {
		File f=new File("E:/xu.txt");
		f.delete();
	}
	
	//创建新文件并写入信息
	public void update(ArrayList<MyAccount> a1){		
		try {
			File f=new File("E:/xu.txt");
			FileOutputStream fos=new FileOutputStream(f);
			ObjectOutputStream oos=new ObjectOutputStream(fos);
			oos.writeObject(a1);			
			oos.close();
			fos.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}


 
