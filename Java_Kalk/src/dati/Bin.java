/**
 * Classe per rappresentare stringhe binarie. E' presente un ArrayList per
 * rappresentare la parte intera ed uno per la parte frazionaria. Inoltre è
 * un boolean per indicarne il segno
 */
package dati;
import java.util.ArrayList;
import java.lang.Math;
import java.lang.ArithmeticException;
import java.lang.ClassCastException;

public class Bin implements Tipo{
	private ArrayList<Boolean> intera=new ArrayList<Boolean>();
	private ArrayList<Boolean> frazionaria=new ArrayList<Boolean>();
	private Boolean segno;
	public Bin(int d) {
		if(d>=0)
			segno=Boolean.FALSE;
		else {
			segno=Boolean.TRUE;
			d=-d;
		}
		
		int quoziente=d;
		Boolean resto=Boolean.FALSE;
		
		while(quoziente!=0) {
			resto= quoziente%2==0 ? Boolean.FALSE : Boolean.TRUE;
			intera.add(0, resto);
			quoziente=quoziente/2;
		}
		frazionaria.add(Boolean.FALSE);
	}
	public Bin() {
		this(1);
	}
	public Bin(double d) {
		if(d>=0)
			segno=Boolean.FALSE;
		else {
			segno=Boolean.TRUE;
			d=-d;
		}
		
		int intero=(int) d;
		double frazionario=d-intero;
		int quoziente=intero;
		Boolean resto=Boolean.FALSE;
		
		while(quoziente!=0) {
			resto=quoziente%2==0 ? Boolean.FALSE : Boolean.TRUE;
			intera.add(0, resto);
			quoziente=quoziente/2;
		}
		
		if(frazionario==0)
			frazionaria.add(Boolean.FALSE);
		else {
			int i=0;
			while(frazionario!=0 && i<10) {
				frazionario=frazionario*2;
				
				if(frazionario>=1) {
					frazionaria.add(Boolean.TRUE);
					frazionario-=1;
				}
				else
					frazionaria.add(Boolean.FALSE);
				i++;
			}
		}
	}
	//conversione da numero binario a decimale
	public double base10() {
		int i_out=0;
		double f_out=0;
		for(int i=intera.size(); i>0; i--) {
			//l'hashCode ritorna 1231 se intera[i]==true, 1237 se intera[i]==false
			int count=intera.get(i-1).hashCode()-1231==0 ? 1 : 0;
			i_out+=count*Math.pow(2, intera.size()-i);
		}
		
		for(int i=0; i<frazionaria.size(); i++) {
			int count=frazionaria.get(i).hashCode()-1231==0 ? 1 : 0;
			f_out+=count*Math.pow(2, -(i+1));
		}
		
		f_out+=i_out;
		
		if(segno)
			f_out=-f_out;
		
		return f_out;
	}
	//conversione da numero binario a esadecimale
	public String base16() {
		int quoziente=(int)base10();
		String out=new String();
		
		int resto=0;
		
		while(quoziente!=0) {
			resto=quoziente%16;
			if(resto<10)
				out=String.valueOf(resto)+out;
			else {
				switch (resto) {
				case 10:
					out="A"+out;
					break;
					
				case 11:
					out="B"+out;
					break;
					
				case 12:
					out="C"+out;
					break;
				case 13:
					out="D"+out;
					break;
				case 14:
					out="E"+out;
					break;
				case 15:
					out="F"+out;
					break;
				}
			}
			quoziente=quoziente/16;
		}
		
		return out;
	}
	public int getDimIntera() {return intera.size();}
	public int getDimFrazionaria() {return frazionaria.size();}
	public Bin moltiplicazione(Bin bin) {
		double a=base10();
		double b=bin.base10();
		return new Bin(a*b);
	}
	public Bin divisione(Bin bin) throws ArithmeticException{
		double a=base10();
		double b=bin.base10();
		
		if(b<0)
			throw new ArithmeticException("divisione per 0");
		
		return new Bin(a/b);
	}
	
	public Tipo somma(Tipo t) throws ClassCastException{
		if(!(t instanceof Bin))
			throw new ClassCastException("tipi incompatibili per l'operazione");
			
		Bin bin=(Bin)t;
		double a=base10();
		double b=bin.base10();
		return new Bin(a+b);
	}
	public Tipo differenza(Tipo t) throws ClassCastException{
		if(!(t instanceof Bin))
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Bin bin=(Bin)t;
		double a=base10();
		double b=bin.base10();
		return new Bin(a-b);
	}
	public Tipo moltiplicazione(int n) {
		return moltiplicazione(new Bin(n));
	}
	public Tipo divisione(int n) {
		return divisione(new Bin(n));
	}
	public boolean equals(Tipo t) throws ClassCastException{
		if(!(t instanceof Bin))
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Bin bin=(Bin)t;
		for(int i=0; i<intera.size(); i++)
			if((intera.size()!=bin.intera.size()) || !(intera.get(i).equals(bin.intera.get(i))))
				return false;
		
		for(int i=0; i<frazionaria.size(); i++)
			if((intera.size()!=bin.intera.size()) || !(frazionaria.get(i).equals(bin.frazionaria.get(i))))
				return false;
		return true;
	}
	public boolean min(Tipo t) throws ClassCastException{
		if(!(t instanceof Bin))
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Bin bin=(Bin)t;
		double a=base10();
		double b=bin.base10();
		
		return a<=b;
	}
	public String toString() {
		String out=new String();
		
		if(segno)
			out+="-";
		else
			out+="+";
		
		for(int i=0; i<intera.size(); i++) {
			int count=intera.get(i).hashCode()-1231==0 ? 1 : 0;
			out+=String.valueOf(count);
		}
		
		out+=".";
		
		for(int i=0; i<frazionaria.size(); i++) {
			int count=frazionaria.get(i).hashCode()-1231==0 ? 1 : 0;
			out+=String.valueOf(count);
		}
		
		return out;
	}
}
