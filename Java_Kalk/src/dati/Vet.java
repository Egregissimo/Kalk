package dati;
import java.lang.Math;
import java.lang.ArithmeticException;
import java.lang.ClassCastException;

public class Vet implements Tipo{
	private int r;
	private int c;
	private int[] v_m;
	public Vet(int row, int col) {
		r=row;
		c=col;
		v_m=new int[r*c];
	}
	public Vet(int row) {
		this(row, 1);
	}
	public Vet() {
		this(0, 1);
	}
	public Vet(int[] vet, int row, int col) {
		this(row, col);
		for(int i=0; i<vet.length && i<v_m.length; i++)
			v_m[i]=vet[i];
	}
	public Vet(int[] vet, int row) {
		this(vet, row, 1);
	}
	public Vet(int[] vet) {
		this(vet, 0, 1);
	}
	public int getRow() {return r;}
	public int getColumn() {return c;}
	public void trasposed() {
		int[] tmp=new int[c*r];
		int index=0;
		for(int j=0; j<c; j++)
			for(int i=0; i<r; i++) {
				tmp[index]=get(i, j);
				index++;
			}
		
		v_m=tmp;
		int ttmp=c;
		c=r;
		r=ttmp;
	}
	public int norma() {
		int max=0;
		for(int i=0; i<c; i++) {
			int count=0;
			for(int j=0; j<r; j++)
				count+=Math.abs(get(j,i));
			
			if(count>max)
				max=count;
		}
		
		return max;
	}
	public int get(int row, int col) {
		return v_m[col+(row*c)];
	}
	public Vet moltiplicazione(Vet v) throws ArithmeticException{
		if(!isMoltiplicazione(v))
			throw new ArithmeticException("dimensioni delle matrici errate");
		
		Vet out=new Vet(r, v.c);
		int valore=0;
		
		for(int i=0; i<r; i++)
			for(int k=0; k<v.c; k++) {
				for(int j=0; j<c; j++)
					valore+=get(i,j)*v.get(j,k);
				
				out.v_m[k+(i*v.c)]=valore;
			}
		
		return out;
	}
	protected boolean isMoltiplicazione(Vet tmp) {return c==tmp.r;}
	protected boolean isQuadrata() {return r==c; }
	protected boolean sameSize(Vet tmp) {return r==tmp.r && c==tmp.c;}
	
	public Tipo somma(Tipo t) throws ClassCastException, ArithmeticException{
		if(!(t instanceof Vet))
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Vet v=(Vet)t;
		if(!sameSize(v))
			throw new ArithmeticException("dimensioni delle matrici errate");
		
		Vet out=new Vet(r, c);
		for(int i=0; i<r; i++)
			for(int j=0; j<c; j++)
				out.v_m[j+(i*c)]=get(i,j)+v.get(i,j);
		
		return out;
	}
	public Tipo differenza(Tipo t) throws ClassCastException, ArithmeticException{
		if(!(t instanceof Vet)) 
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Vet v=(Vet)t;
		if(!sameSize(v))
			throw new ArithmeticException("dimensioni delle matrici errate");
		
		Vet out=new Vet(r, c);
		for(int i=0; i<r; i++)
			for(int j=0; j<c; j++)
				out.v_m[j+(i*c)]=get(i,j)-v.get(i,j);
		
		return out;
	}
	public Tipo moltiplicazione(int n) {
		Vet out=new Vet(r, c);
		for(int i=0; i<r; i++)
			for(int j=0; j<c; j++)
				out.v_m[j+(i*c)]=get(i,j)*n;
		
		return out;
	}
	public Tipo divisione(int n) {
		Vet out=new Vet(r, c);
		for(int i=0; i<r; i++)
			for(int j=0; j<c; j++)
				out.v_m[j+(i*c)]=get(i,j)/n;
		
		return out;
	}
	public boolean equals(Tipo t) throws ClassCastException{
		if(!(t instanceof Vet)) {
			throw new ClassCastException("tipi incompatibili per l'operazione");
		}
		Vet v=(Vet)t;
		if(sameSize(v)) {
			for(int i=0; i<r; i++)
				for(int j=0; i<c; j++)
					if(get(i,j)!=v.get(i,j))
						return false;
			return true;
		}
		return false;
	}
	public boolean min(Tipo t) throws ClassCastException{
		if(!(t instanceof Vet)) {
			throw new ClassCastException("tipi incompatibili per l'operazione");
		}
		Vet v=(Vet)t;
		return norma()<v.norma();
	}
	public String toString() {
		String out=new String("[");
		for(int i=0; i<r; i++) {
			for(int j=0; j<c-1; j++)
				out+=String.valueOf(get(i,j))+", ";
			
			out+=String.valueOf(get(i,c-1))+"; ";
		}
		out+="]";
		return out;
	}
}
