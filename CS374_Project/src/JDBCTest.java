import java.sql.*;
import java.util.Scanner;

public class JDBCTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int x = menu();
		
		try
		{
			double maxPrice = 20.0;
			if (args.length > 0)
				maxPrice = Double.parseDouble(args[0]);
			
			/*=String stSQL = "SELECT C.Company, E.[Last Name] "
                + "FROM Customers C, Employees E, Orders O "
                + "WHERE E.ID=O.[Employee ID] AND C.ID=O.[Customer ID] AND "
                + "O.[Shipping Fee] < " + String.valueOf(maxPrice)
                + " ORDER BY O.[Shipping Fee]";
	*/
			Class.forName("net.ucanaccess.jdbc.UcanaccessDriver");
			Connection conn = DriverManager.getConnection("jdbc:ucanaccess://C:\\Users\\mgalle19\\Documents\\GitHub\\CS374_Final\\Final_Project_CS374.accdb");
			Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			//stmt.execute(stSQL);

			ResultSet rs = stmt.getResultSet();
			while (rs.next() == true) {
				System.out.println("<" + rs.getString(1) + ", " + 	rs.getString(2) + ">");
			}
		} 
		catch (Exception ex) {
			System.out.println(String.format("Error: %s", ex.getMessage()));
		}
	}
	public static int menu(){
		System.out.println("1. Look in Fridge");
		System.out.println("2. Add to Fridge");
		System.out.println("3. Delete from Fridge ");
		System.out.println("4. Create Shopping list");
		Scanner in = new Scanner(System.in);
		int choice = 0;
		choice = in.nextInt();
		switch(choice){
		case 1: choice = 1;
			break;
		case 2: choice = 2;
			break;
		case 3: choice = 3;
			break;
		case 4: choice = 4;
			break;
		}
		return choice;
	}

}
