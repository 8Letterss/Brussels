import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class TestMyAccount {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ArrayList<MyAccount> a1=new ArrayList<MyAccount>();
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
		try {
			a1.add(new MyAccount("1",sdf.parse("2022-05-01"),"收入","工资","8000"));
			a1.add(new MyAccount("2",sdf.parse("2022-05-02"),"支出","购物","1000"));
			a1.add(new MyAccount("3",sdf.parse("2022-05-03"),"收入","奖金","5000"));
			a1.add(new MyAccount("4",sdf.parse("2022-05-04"),"支出","餐饮","80"));
			a1.add(new MyAccount("5",sdf.parse("2022-05-04"),"支出","购物","100"));
		} catch (ParseException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		try {
			FileOutputStream fos=new FileOutputStream("E:/xu.txt");
			ObjectOutputStream oos=new ObjectOutputStream(fos);
			oos.writeObject(a1);
			oos.flush();
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

class MyAccount implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String id;
	private Date date;
	private String type;
	private String content;
	private String amount;
	public MyAccount(String id, Date date, String type, String content, String amount) {
		super();
		this.id = id;
		this.date = date;
		this.type = type;
		this.content = content;
		this.amount = amount;
	}
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public Date getDate() {
		return date;
	}
	public void setDate(Date date) {
		this.date = date;
	}
	public String getType() {
		return type;
	}
	public void setType(String type) {
		this.type = type;
	}
	public String getContent() {
		return content;
	}
	public void setContent(String content) {
		this.content = content;
	}
	public String getAmount() {
		return amount;
	}
	public void setAmount(String amount) {
		this.amount = amount;
	}
	
}
