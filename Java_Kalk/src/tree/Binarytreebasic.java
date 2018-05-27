package tree;
import dati.*;
import java.util.ArrayList;
import java.lang.IllegalArgumentException;

public abstract class Binarytreebasic {
	
	protected static class Nodo{
		protected Tipo info;
		protected Nodo father;
		protected Nodo left;
		protected Nodo right;
		protected Nodo(Tipo t, Nodo f, Nodo l, Nodo r) {
			info=t;
			father=f;
			left=l;
			right=r;
		}
		protected Nodo(Tipo t, Nodo f, Nodo l) {this(t, f, l, null);}
		protected Nodo(Tipo t, Nodo f) {this(t, f, null, null);}
		protected Nodo(Tipo t) {this(t, null, null, null);}
		protected Nodo() {this(null, null, null, null);}
		protected static String stampa(Nodo n) {
			if(n==null)
				return "_";
			return "('"+n.info.toString()+"',"+stampa(n.left)+","+stampa(n.right)+")";
		}
	}
	Nodo root=null;
	private Nodo constrRic(String s, Tipo[] t, Nodo f, int t_i, int s_i) {
		Nodo x=new Nodo(t[t_i], f);
		s_i+=3;
		int s_left=balance_brackets(s, s_i, s_i);
		int s_right=balance_brackets(s, s_i+s_left+2, s_i+s_left+2);
		if(s_left!=0)
			x.left=constrRic(s, t, x, t_i+1, s_i);
		if(s_right!=0) {
			t_i+=n_nodes_stringa(s, s_i)+1;
			x.right=constrRic(s, t, x, t_i, s_i+s_left+2);
		}
		return x;
	}
	public Binarytreebasic(Tipo[] t, String s) throws IllegalArgumentException{
		if(!controlla_input(t, s))
			throw new IllegalArgumentException("input non validi");
		
		root=constrRic(s, t, null, 0, 0);
	}
	public Binarytreebasic() {}
	protected static boolean parser(String s, int begin, int end) {
		if(begin==end)
			return true;
		if(s.charAt(begin)!='(' || s.charAt(++begin)!='*' || s.charAt(++begin)!=',')
			return false;
		if(s.charAt(begin+1)=='_' && s.charAt(begin+2)==',' && s.charAt(begin+3)=='_' && s.charAt(begin+4)==')')
			return true;
		
		begin++;
		boolean a=true, b=true;
		int aux_end;
		
		if(s.charAt(begin)!='_' && s.charAt(begin)!='(')
			return false;
		if(s.charAt(begin)=='(') {
			int l=balance_brackets(s, begin, end);
			if(l==-1)
				return false;
			aux_end=begin+l+1;
			if(s.charAt(aux_end)!=',')
				return false;
			a=parser(s, begin, aux_end);
			begin=aux_end+1;
		}
		else
			begin+=2;
		
		if(s.charAt(begin)!='_' && s.charAt(begin)!='(')
			return false;
		if(s.charAt(begin)=='(') {
			int r=balance_brackets(s, begin, end);
			if(r==-1)
				return false;
			aux_end=begin+r+1;
			if(s.charAt(aux_end)!=')')
				return false;
			b=parser(s, begin, aux_end);
		}
		
		return a && b;
	}
	protected static int balance_brackets(String s, int begin, int end) {
		if(s.charAt(begin)=='_')
			return 0;
		int k=1, m=1;
		if(begin==end)
			end--;
		
		for(; k>0 && begin+m!=end; m++)
			if(s.charAt(begin+m)=='(')
				k++;
			else if(s.charAt(begin+m)==')')
				k--;
		if(k!=0)
			return -1;
		return m-1;
	}
	protected static int n_nodes_stringa(String s, int begin) {
		int count=0, id=1;
		if(s.charAt(begin)=='_')
			return 0;
		for(int i=1; id!=0; i++) {
			if(s.charAt(begin+i)=='*')
				count++;
			else if(s.charAt(begin+i)=='(')
				id++;
			else if(s.charAt(begin+i)==')')
				id--;
		}
		return count;
	}
	protected static Nodo somma(Nodo a, Nodo b, Nodo f) {
		Nodo x=null;
		if(a==null && b!=null) {
			x=new Nodo(b.info, f);
			x.left=somma(a, b.left, x);
			x.right=somma(a, b.right, x);
		}
		else if(a!=null && b==null) {
			x=new Nodo(a.info, f);
			x.left=somma(a.left, b, x);
			x.right=somma(a.right, b, x);
		}
		else if(a!=null && b!=null && a.left==null && a.right==null && b.left==null && b.right==null && a.info.moltiplicazione(-1).equals(b.info))
			return x;
		else if(a!=null && b!=null) {
			x=new Nodo(a.info.somma(b.info), f);
			x.left=somma(a.left, b.left, x);
			x.right=somma(a.right, b.right, x);
		}
		return x;
	}
	protected static Nodo differenza(Nodo a, Nodo b, Nodo f) {
		Nodo x=null;
		if(a==null && b!=null) {
			x=new Nodo(b.info.moltiplicazione(-1), f);
			x.left=differenza(a, b.left, x);
			x.right=differenza(a, b.right, x);
		}
		else if(a!=null && b==null) {
			x=new Nodo(a.info, f);
			x.left=differenza(a.left, b, x);
			x.right=differenza(a.right, b, x);
		}
		else if(a!=null && b!=null && a.left==null && a.right==null && b.left==null && b.right==null && a.info.equals(b.info))
			return x;
		else if(a!=null && b!=null) {
			x=new Nodo(a.info.differenza(b.info), f);
			x.left=differenza(a.left, b.left, x);
			x.right=somma(a.right, b.right, x);
		}
		return x;
	}
	protected static Nodo moltiplicazione(Nodo a, int k, Nodo f) {
		Nodo x=null;
		if(a!=null) {
			if(k==0)
				return new Nodo(a.info.moltiplicazione(0));
			x=new Nodo(a.info.moltiplicazione(k), f);
			x.left=moltiplicazione(a.left, k, x);
			x.right=moltiplicazione(a.right, k, x);
		}
		return x;
	}
	protected static Nodo divisione(Nodo a, int k, Nodo f) {
		Nodo x=null;
		if(a!=null) {
			x=new Nodo(a.info.divisione(k), f);
			x.left=divisione(a.left, k, x);
			x.right=divisione(a.right, k, x);
		}
		return x;
	}
	protected static ArrayList<Tipo> nodes(Nodo n) {
		ArrayList<Tipo> a=new ArrayList<Tipo>(), b=new ArrayList<Tipo>();
		if(n==null)
			return a;
		if(n.left==null && n.right==null) {
			a.add(n.info);
			return a;
		}
		ArrayList<Tipo> c=new ArrayList<Tipo>();
		c.add(n.info);
		a=nodes(n.left);
		b=nodes(n.right);
		a.addAll(b);
		c.addAll(a);
		return c;
	}
	protected static boolean controlla_percorso(String s) {
		for(int i=0; i<s.length(); i++)
			if(s.charAt(i)!='0' && s.charAt(i)!='1')
				return false;
		return true;
	}
	protected static boolean controlla_input(Tipo[] t, String s) {
		for(int i=0; i<t.length; i++)
			if(t[0].getClass()!=t[i].getClass())
				return false;
		return parser(s, 0, s.length()) && (t.length==n_nodes_stringa(s, 0)) && (s.length()==0 || s.length()==5 || s.length()%6==1);
	}
	protected static String tree_to_string(Nodo r) {
		if(r==null)
			return "_";
		return "(*,"+tree_to_string(r.left)+","+tree_to_string(r.right)+")";
	}
	public static int n_nodes(Nodo n) {
		if(n==null)
			return 0;
		return 1+n_nodes(n.left)+n_nodes(n.right);
	}
	public Tipo cerca(String s) throws IllegalArgumentException{
		Nodo x=root;
		if(!controlla_percorso(s) || x==null)
			throw new IllegalArgumentException("percorso non valido");
		
		for(int i=0; i<s.length(); i++)
			if(s.charAt(i)=='0')
				x=x.left;
			else
				x=x.right;
		if(x!=null)
			return x.info;
		System.out.println("Elemento non trovato\n");
		return null;
	}
	public String struttura_tree() {
		return tree_to_string(root);
	}
	public String toString() {
		if(root!=null)
			return Nodo.stampa(root);
		return new String();
	}
	
	public abstract void add(Tipo t);
	public abstract Tipo remove(String s);
	public abstract Tipo remove(Tipo t);
	public abstract Tipo search(Tipo t);
	public abstract Binarytreebasic somma(Binarytreebasic b);
	public abstract Binarytreebasic differenza(Binarytreebasic b);
	public abstract Binarytreebasic moltiplicazione(int p);
	public abstract Binarytreebasic divisione(int p);
}
