/**
 * classe di razionali dove ogni oggetto è formato da un numeratore
 * e un denominatore
 */
package dati;
import java.lang.Math;
import java.lang.ArithmeticException;
import java.lang.ClassCastException;

public class Raz implements Tipo{
	private int num;
	private int den;
	public Raz(int n, int d) throws ArithmeticException{
		num=n;
		if(d==0)
			new ArithmeticException("divisione per 0");
		
		else if(num==0)
			den=1;
		else if(d<0) {
			num=-num;
			den=-d;
		}
		else
			den=d;
		riduzione();
	}
	public Raz(int n) {
		this(n, 1);
	}
	public Raz() {
		this(0, 1);
	}
	public Raz(double n, double d) throws ArithmeticException{
		if(d==0)
			new ArithmeticException("divisione per 0");
		
		if(n==0) {
			num=0;
			den=1;
		}
		else {
			//numeratore
			int degree_num=degree(n);
			int num_num=(int)(n*Math.pow(10, degree_num));
			int den_num=(int)(Math.pow(10, degree_num));
			Raz x=new Raz(num_num, den_num);
			
			//denominatore
			int degree_den=degree(d);
			int num_den=(int)(d*Math.pow(10, degree_den));
			int den_den=(int)(Math.pow(10, degree_den));
			Raz y=new Raz(num_den, den_den);
			
			Raz z=x.divisione(y);
			num=z.num;
			den=z.den;
		}
		riduzione();
	}
	public Raz(Double n) {
		this(n, 1.0);
	}
	public int getNum() {return num;}
	public int getDen() {return den;}
	public static Raz inverso(Raz r) {return new Raz(r.den, r.num);}
	//metodi per la conversione
	public double toDouble() {double d=num/den; return d;}
	public int toInt() {return num/den;}
	public static Raz pow(Raz r, int n) {return new Raz(Math.pow(r.num, n), Math.pow(r.den, n));}
	public static Raz sqrt(Raz r) {return new Raz(Math.sqrt(r.num), Math.sqrt(r.den));}
	public static Raz cbrt(Raz r) {return new Raz(Math.cbrt(r.num), Math.sqrt(r.den));}
	//riduzione ai minimi termini del razionale
	public void riduzione() {
		if(num==den)
			num=den=1;
		else if(num!=0) {
			int aux=Math.abs(num)<Math.abs(den)?Math.abs(num):Math.abs(den);
			for(int i=2; i<=aux; i++) {
				if(num%i==0 && den%i==0) {
					num=num/i;
					den=den/i;
					aux=num<den?num:den;
					i--;
				}
			}
		}
		else
			den=1;
	}
	//indica quante cifre dpo la virgola ci sono
	private int degree(double d) {
		int i=0;
		while(((d*Math.pow(10, i)-Math.floor(d*Math.pow(10, i)))!=0) && i<=10)
			i++;
		return i;
	}
	
	public Raz clone() {
		return new Raz(num, den);
	}
	public Raz moltiplicazione(Raz r) {
		return new Raz(num*r.num, den*r.den);
	}
	public Raz divisione(Raz r) throws ArithmeticException{
		if(r.num==0)
			throw new ArithmeticException("divisione per 0");
		
		return new Raz(num*r.den, den*r.num);
	}
	
	public Tipo somma(Tipo t) throws ClassCastException{
		if(!(t instanceof Raz))
				throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Raz r=(Raz)t;
		if(num==0)
			return new Raz(r.num, r.den);
		if(r.num==0)
			return clone();
		int n=num*r.den+r.num*den;
	    int d=den*r.den;
	    
	    return new Raz(n, d);
	}
	public Tipo differenza(Tipo t) throws ClassCastException{
		if(!(t instanceof Raz))
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Raz r=(Raz)t;
		int n=num*r.den-r.num*den;
	    int d=den*r.den;
	    
	    return new Raz(n, d);
	}
	public Tipo moltiplicazione(int n) {
		return moltiplicazione(new Raz(n));
	}
	public Tipo divisione(int n) {
		return divisione(new Raz(n));
	}
	public boolean equals(Tipo t) throws ClassCastException{
		if(!(t instanceof Raz))
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Raz r=(Raz)t;
		return num==r.num && den==r.den;
	}
	public boolean min(Tipo t) throws ClassCastException{
		if(!(t instanceof Raz))
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Raz r=(Raz)t;
		return num*r.den<r.num*den;
	}
	public String toString() {
		if(num==0)
			return String.valueOf(0);
		else if(den==1)
			return String.valueOf(num);
		else
			return String.valueOf(num)+"/"+String.valueOf(den);
	}
}
