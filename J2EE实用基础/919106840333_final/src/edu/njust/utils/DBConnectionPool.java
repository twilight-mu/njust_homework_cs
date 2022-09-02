package edu.njust.utils;

import com.mchange.v2.c3p0.ComboPooledDataSource;
import com.mchange.v2.c3p0.DataSources;

import java.beans.PropertyVetoException;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.Properties;


public class DBConnectionPool {
    private static volatile DBConnectionPool dbConnection;
    private ComboPooledDataSource cpds;

  
    private DBConnectionPool() {
        try {
        	String driverClassName = null;
            String url = null;
            String username = null;
            String password = null;
            Properties properties = new Properties();
//            FileInputStream fileInputStream = new FileInputStream("src/config/jdbc-mysql.properties");;
            InputStream is = DBConnectionPool.class.getClassLoader().getResourceAsStream("/db.properties");
            if(is!=null){
                properties.load(is);
                System.out.println("here");
                driverClassName = properties.getProperty("driver");            
                url = properties.getProperty("url");
                username = properties.getProperty("username");
                password = properties.getProperty("password");
             }else {
            	 driverClassName = "com.mysql.jdbc.Driver";            
                 url = "jdbc:mysql://localhost:3306/919106840333_rf";
                 username = "root";
                 password = "root";
             }  

            cpds = new ComboPooledDataSource();

            cpds.setDriverClass(driverClassName);
            cpds.setJdbcUrl(url);
            cpds.setUser(username);
            cpds.setPassword(password);

            cpds.setInitialPoolSize(3);
            cpds.setMaxPoolSize(10);
            cpds.setAcquireIncrement(1);
            cpds.setIdleConnectionTestPeriod(60);
            cpds.setMaxIdleTime(3000);

            cpds.setTestConnectionOnCheckout(true);

            cpds.setTestConnectionOnCheckin(true);
            
            cpds.setAcquireRetryAttempts(30);
            
            cpds.setAcquireRetryDelay(1000);
      
            cpds.setBreakAfterAcquireFailure(true);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (PropertyVetoException e) {
            e.printStackTrace();
        }

    }

 
    public static DBConnectionPool getInstance() {
        if (dbConnection == null) {
            synchronized (DBConnectionPool.class) {
                if (dbConnection == null) {
                    dbConnection = new DBConnectionPool();
                }
            }
        }
        return dbConnection;
    }

   
    public final synchronized Connection getConnection() throws SQLException {
        return cpds.getConnection();
    }

    protected void finalize() throws Throwable {
        DataSources.destroy(cpds);
        super.finalize();
    }
}
