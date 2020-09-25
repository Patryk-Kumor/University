class Dodaj implements Wyra�enie 
{
	Wyra�enie a;
	Wyra�enie b;
	
	public Dodaj (Wyra�enie a, Wyra�enie b)
	{
		this.a = a;
		this.b = b;
	}
	
	public int Oblicz() 
	{
		return a.Oblicz() + b.Oblicz();
	}
	
	public String toString() 
	{
		return "(" + a + "+" + b + ")"; 
	}	
}
class Odejmij implements Wyra�enie 
{
	Wyra�enie a;
	Wyra�enie b;
	
	public Odejmij (Wyra�enie a, Wyra�enie b)
	{
		this.a = a;
		this.b = b;
	}
	
	public int Oblicz() 
	{
		return a.Oblicz() - b.Oblicz();
	}
	
	public String toString() 
	{
		return "(" + a + "-" + b + ")"; 
	}		
}
class Podziel implements Wyra�enie 
{
	Wyra�enie a;
	Wyra�enie b;
	
	public Podziel (Wyra�enie a, Wyra�enie b) 
	{ 
		this.a = a; 
		this.b = b; 
	}
	public int Oblicz()
	{ 
		return a.Oblicz() / b.Oblicz(); 
	}
	public String toString()
	{ 
		return "(" + a + "/" + b + ")";
	}	
}
class Pomn� implements Wyra�enie 
{
	Wyra�enie a;
	Wyra�enie b;
	
	public Pomn� (Wyra�enie a, Wyra�enie b) 
	{
		this.a = a;
		this.b = b;
	}
	public int Oblicz() 
	{
		return a.Oblicz() * b.Oblicz();
	}
	public String toString()
	{ 
		return "(" + a + "*" + b + ")";
	}	
}
