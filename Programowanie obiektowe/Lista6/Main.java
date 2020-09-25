

import java.io.FileNotFoundException;


public class Main 
{

	public static void main(String[] args) throws FileNotFoundException
	{
		System.out.println("Hello!");
		
		
        Collection<String,String> C = new Collection<String,String>();
		C.Dodaj("A", "1");
		C.Dodaj("B", "2");
		C.Dodaj("C", "0");
		C.Dodaj("D", "-1");
        C.WriteToFile("dic2.txt");
        
        System.out.println("----");
        C.Wypisz();
        Collection<String,String> G = new Collection<String,String>();
        try 
        {
        	G.LoadFromFile("dic2.txt");
            System.out.println("----");
            G.Wypisz();
			
		} 
        catch (FileNotFoundException e) 
        { e.printStackTrace(); }
        
        
        
	}

}
