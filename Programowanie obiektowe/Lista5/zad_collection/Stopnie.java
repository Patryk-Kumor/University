import java.util.Comparator;

public abstract class Stopnie implements Comparable<Stopnie>
{
	
	public String nazwa;
	public abstract int numer();
	
	public int compareTo(Stopnie S)
	{
		if(S.numer() == this.numer()) return 0;
		else if(S.numer() < this.numer()) return 1;
		else return -1;
	}
	
	public String toString()
	{
        return "Stopieñ: " + nazwa + ", wa¿noœæ:" + numer() + "\n";
    }
	
}