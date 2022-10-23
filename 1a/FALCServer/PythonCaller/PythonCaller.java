package PythonCaller;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public final class PythonCaller {

	public PythonCaller() {}
	
	public final void runPythonScript(String[] cmd) {

		Runtime rt = Runtime.getRuntime();
		
		try {
			Process pr = rt.exec(cmd);
			
			int exitVal = pr.waitFor();
			System.out.println(exitVal);
			int len;
			if ((len = pr.getErrorStream().available()) > 0) {
				byte[] buf = new byte[len];
				pr.getErrorStream().read(buf);
				System.err.println("Command error:\t\""+new String(buf)+"\"");
			}
			
		} catch (IOException e) {e.printStackTrace();} 
		  catch (InterruptedException e) {e.printStackTrace();}
		
	}
	
	public final String getTextFromFile(String path) {
		
		String text = "";
		
		try(FileReader fileReader = new FileReader(path);
			BufferedReader reader = new BufferedReader(fileReader);){
            	 
			String line = reader.readLine();

			while(line != null) {

					text = text + line;	

					line = reader.readLine();					 
				}		 
			
        } 
		  catch(FileNotFoundException e) { e.printStackTrace();;}
		  catch(IOException e) 			 { e.printStackTrace();;}
		
		return text;
	}
}
