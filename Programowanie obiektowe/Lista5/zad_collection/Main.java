import java.util.ArrayList;
import java.util.Collections;

public class Main
{

	public static void main(String[] args)
	{
		
		System.out.println("Hello!");
		System.out.println("Hierarchia Klas:");
		System.out.println("");
		
        ArrayList<Stopnie> T = new ArrayList<Stopnie>();
        
		T.add(new Kapral("Kapral A"));
		T.add(new Szeregowy("Szeregowy B"));
		T.add(new Plutonowy("Plutonowy C"));
		T.add(new Sier¿ant("Sier¿ant D"));
		
		Collections.sort(T);		
        for(Stopnie t : T) System.out.println(t);
	}

}
