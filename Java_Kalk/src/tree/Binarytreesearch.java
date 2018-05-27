package tree;
import dati.*;
import java.util.Arrays;
import java.lang.IllegalArgumentException;

public class Binarytreesearch extends Binarytreebasic{
	
	public Binarytreesearch(Tipo[] t, String s) {super(ordina(t, s), s);}
	public Binarytreesearch() {}
	private static void merge(Tipo[] left, Tipo[] right, Tipo[] bars) {
		int nL=left.length;
		int nR=right.length;
		int i=0, j=0, k=0;
		
		while(j<nL && k<nR) {
			if(left[j].min(right[k])) {
				bars[i]=left[j];
				j++;
			}
			else {
				bars[i]=right[k];
				k++;
			}
			i++;
		}
		while(j<nL) {
			bars[i]=left[j];
			j++;
			i++;
		}
		while(k<nR) {
			bars[i]=right[k];
			k++;
			i++;
		}
	}
	private static void merge_sort(Tipo[] bar) {
		if(bar.length<=1)
			return;
		
		int mid=bar.length/2;
		Tipo[] left=new Tipo[mid];
		Tipo[] right=new Tipo[bar.length-mid];
		
		for(int j=0; j<mid; j++)
			left[j]=bar[j];
		for(int j=0; j<(bar.length-mid); j++)
			right[j]=bar[mid+j];
		
		merge_sort(left);
		merge_sort(right);
		merge(left, right, bar);
	}
	private static void ordinaRic(Tipo[] A, String s, int begin, Tipo[] B, int it) {
		int size=A.length;
		if(size>1) {
			begin+=3;
			int q=n_nodes_stringa(s, begin);
			int l=balance_brackets(s, begin, begin);
			B[it]=A[q];
			Tipo[] LEFT=new Tipo[q];
			Tipo[] RIGHT=new Tipo[size-q-1];
			for(int i=0; i<q; i++)
				LEFT[i]=A[i];
			for(int i=0; i<size-q-1; i++)
				RIGHT[i]=A[q+1+i];
			ordinaRic(LEFT, s, begin, B, it+1);
			it+=n_nodes_stringa(s, begin)+1;
			ordinaRic(RIGHT, s, begin+l+2, B, it);
		}
		else if(size==1) {
			B[it]=A[0];
			it++;
		}
	}
	private static Tipo[] ordina(Tipo[] t, String s) throws IllegalArgumentException{
		if(!controlla_input(t, s))
			throw new IllegalArgumentException("percorso non valido");
		
		Tipo[] A=Arrays.copyOf(t, t.length);
		Tipo[] B=new Tipo[t.length];
		merge_sort(A);
		ordinaRic(A, s, 0, B, 0);
		return B;
	}
	private static String crea_stringa(int n) {
		if(n==0)
			return "_";
		int q=(n+1)/2;
		return "(*,"+crea_stringa(q-1)+","+crea_stringa(n-q)+")";
	}
	private static Nodo minimum(Nodo r) {
		if(r==null)
			return null;
		while(r.left!=null)
			r=r.left;
		return r;
	}
	private static Nodo successor(Nodo r) {
		if(r==null)
			return null;
		if(r.right!=null)
			return minimum(r.right);
		
		Nodo y=r.father;
		while(y!=null && r==y.right) {
			r=y;
			y=y.father;
		}
		return y;
	}
	private Tipo removeIt(Nodo z) {
		Nodo x=null, y=null;
		if(z.left==null || z.right==null)
			y=z;
		else
			y=successor(z);
		if(y.left!=null)
			x=y.left;
		else
			x=y.right;
		if(x!=null)
			x.father=y.father;
		if(y.father==null)
			root=x;
		else if(y==y.father.left)
			y.father.left=x;
		else
			y.father.right=x;
		if(x!=z)
			x.info=z.info;
		return z.info;		
	}
	public void add(Tipo a) throws ClassCastException{
		if(root!=null && root.info.getClass()!=a.getClass())
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Nodo y=null, x=root;
		while(x!=null) {
			y=x;
			if(a.min(x.info))
				x=x.left;
			else
				x=x.right;
		}
		if(y==null)
			root=new Nodo(a);
		else if(a.min(y.info))
			y.left=new Nodo(a, y);
		else
			y.right=new Nodo(a, y);
	}
	public Tipo remove(String s) throws IllegalArgumentException{
		if(!controlla_percorso(s))
			throw new IllegalArgumentException("percorso non valido");
		
		Nodo x=root;
		for(int i=0; x!=null && i<s.length(); i++) {
			if(s.charAt(i)=='0')
				x=x.left;
			else
				x=x.right;
		}
		if(x!=null)
			return removeIt(x);
		System.out.println("Elemento non trovato\n");
		return null;
	}
	public Tipo remove(Tipo a) throws ClassCastException{
		if(root!=null && root.info.getClass()!=a.getClass())
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Nodo x=root;
		while(x!=null && !(x.info.equals(a)))
			if(a.min(x.info))
				x=x.left;
			else
				x=x.right;
		if(x!=null)
			return removeIt(x);
		System.out.println("Elemento non trovato\n");
		return null;
	}
	public Tipo search(Tipo a) throws ClassCastException{
		if(root!=null && root.info.getClass()!=a.getClass())
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Nodo x=root;
		while(x!=null && !(x.info.equals(a)))
			if(a.min(x.info))
				x=x.left;
			else
				x=x.right;
		if(x!=null)
			return x.info;
		System.out.println("Elemento non trovato\n");
		return null;
	}
	public Binarytreesearch balance() {
		int n=n_nodes(root);
		Tipo[] A=nodes(root).toArray(new Tipo[0]);
		String s=crea_stringa(n);
		return new Binarytreesearch(A, s);
	}
	public Binarytreebasic somma(Binarytreebasic b) throws ClassCastException{
		if(b instanceof Binarytreesearch==false)
			throw new ClassCastException("tipi incompatibili per l'operzione");
			
		Nodo x=super.somma(root, b.root, null);
		String s=tree_to_string(x);
		Tipo[] A=nodes(x).toArray(new Tipo[0]);
		return new Binarytreesearch(A, s);
	}
	public Binarytreebasic differenza(Binarytreebasic b) throws ClassCastException{
		if(b instanceof Binarytreesearch==false)
			throw new ClassCastException("tipi incompatibili per l'operzione");
			
		Nodo x=super.differenza(root, b.root, null);
		String s=tree_to_string(x);
		Tipo[] A=nodes(x).toArray(new Tipo[0]);
		return new Binarytreesearch(A, s);
	}
	public Binarytreebasic moltiplicazione(int p) {
		Nodo x=super.moltiplicazione(root, p, null);
		String s=tree_to_string(x);
		Tipo[] A=nodes(x).toArray(new Tipo[0]);
		return new Binarytreesearch(A, s);
	}
	public Binarytreebasic divisione(int p) {
		Nodo x=super.divisione(root, p, null);
		String s=tree_to_string(x);
		Tipo[] A=nodes(x).toArray(new Tipo[0]);
		return new Binarytreesearch(A, s);
	}
}
