public class Sta³a implements Wyra¿enie
{
	int wartoœæ;
	
	public Sta³a(int x) 
	{
		wartoœæ = x; 
	}
	public int Oblicz() 
	{
		return wartoœæ;
	}
	public String toString() 
	{
		return "" + wartoœæ; 
	}
}