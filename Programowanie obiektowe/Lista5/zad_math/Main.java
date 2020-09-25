import java.util.Hashtable;

public class Main
{

	public static void main(String[] args)
	{
		Hashtable<String, Integer> T = new Hashtable<String, Integer>();
		T.put("x",2);
		System.out.println("x = " + T.get("x"));
		Wyra¿enie strin = new Dodaj(new Sta³a(2), new Zmienna("x", T));
		strin = new Odejmij(strin, new Sta³a(1));
		System.out.println(strin.toString() + " = " + strin.Oblicz());
	}

}
