import java.sql.*;

public class JDBCTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
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
	public void menu(){
		
	}

}
