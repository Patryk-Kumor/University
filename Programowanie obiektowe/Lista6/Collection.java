import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.Serializable;
import java.util.Scanner;

class Collection<V, T extends Comparable<T>> implements Serializable
{
	private static final long serialVersionUID = 1L;

	String val;
	String key;
	Collection<String, String> next;
	Collection<String, String> prev;

	public Collection() {}
	
	public Collection(String val, String key)
	{
		this.val = val;
		this.key = key;
		this.next = null;
	}
	
	public Collection<String, String> Pobierz()
	{
		Collection<String, String> wsk = this.next;
		if(this.next != null) this.next = this.next.next;
		return wsk;
	}
	
	public void Dodaj(String val, String key)
	{
		if(this.val==null)
		{
			this.val=val;
			this.key=key;
		}
		if(this.next != null)
		{
			if (this.next.key.compareTo(key)>=0)
			{
 				Collection<String,String> k=this.next;
 				this.next=new Collection<String,String>(val, key);
 				this.next.next=k;
			}
			else this.next.Dodaj(val, key);
		}
		else this.next=new Collection<String,String>(val, key);
	}
	public void Wypisz()
	{
 			System.out.print(this.toString());
 			
 	}
        public String toString()
        {	
             String w = (this.val + " " + this.key +  " \n");
	     if (this.next != null)
	     {
		return w += this.next.toString();
	     }
             return w;
    }
      public void print() { System.out.println(toString()); } 
         
      public void WriteToFile(String S) throws FileNotFoundException
    	{
	    	PrintWriter zapis = new PrintWriter(S);
	    	zapis.print(this.toString());
	  		zapis.close();
    	}  
      
      public void LoadFromFile(String FileName) throws FileNotFoundException
    	{
    	 
    	  File plik = new File(FileName);
	      Scanner odczyt = new Scanner(plik);
	      
	      String zdanie = odczyt.nextLine();

	      	
	      while(odczyt.hasNext())
	      {
	    	  zdanie = odczyt.nextLine();
	    	  String[] T = zdanie.split(" ");
	    	  
	    	  this.Dodaj(T[0], T[1]);
	    	  
	      }
	      odczyt.close();
	      
	      
    	}



	
      
      
      
      
      
      
      
      
      
      
      
}
