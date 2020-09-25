import java.util.*;

public class Zmienna implements Wyra¿enie
{
	String s;
	Hashtable<String, Integer> T;
	
	public Zmienna(String s, Hashtable<String, Integer> NT)
	{
		this.s = s; this.T = NT;
	}
	public int Oblicz() 
	{ 
		return T.get(s);
	}
	public String toString()
	{ 
		return s;
	}
}