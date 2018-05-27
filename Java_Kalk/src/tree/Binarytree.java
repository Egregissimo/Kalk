package tree;
import dati.*;
import java.lang.IllegalArgumentException;
import java.lang.ClassCastException;

public class Binarytree extends Binarytreebasic{
	
	public Binarytree(Tipo[] t, String s) {super(t,s);}
	public Binarytree() {}
	private static String min_path(Nodo x) {
		if(x==null)
			return new String();
		String a=min_path(x.left), b=min_path(x.right), c=new String();
		if(a.length()<=b.length())
			c=a;
		else
			c=b;
		if(x.father!=null) {
			if(x.father.left==x)
				c='0'+c;
			else
				c='1'+c;
		}
		return c;
	}
	private Tipo removeIt(Nodo y) {
		Nodo x=null, z=null;
		if(y.left!=null && y.right!=null)
			z=y.right;
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
		if(z!=null) {
			Nodo t=root;
			String path=min_path(root);
			for(int i=0; i<path.length(); i++)
				if(path.charAt(i)=='0')
					t=t.left;
				else
					t=t.right;
			
			if(t.left==null)
				t.left=z;
			else
				t.right=z;
		}
		return y.info;
	}
	private static Nodo searchIt(Nodo x, Tipo a) {
		if(x==null)
			return null;
		if(x.info.equals(a))
			return x;
		
		Nodo z=searchIt(x.left, a);
		if(z==null)
			z=searchIt(x.right, a);
		return z;
	}
	public void add(Tipo a) throws ClassCastException{
		if(root!=null && root.info.getClass()!=a.getClass())
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Nodo x=root;
		String path=min_path(root);
		for(int i=0; i<path.length(); i++)
			if(path.charAt(i)=='0')
				x=x.left;
			else
				x=x.right;
		if(x==null)
			x=new Nodo(a, x);
		else if(x.left==null)
			x.left=new Nodo(a, x);
		else
			x.right=new Nodo(a, x);
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
		if(x!=null)
			x=searchIt(x, a);
		if(x!=null)
			return removeIt(x);
		System.out.println("Elemento non trovato\n");
		return null;
	}
	public Tipo search(Tipo a) throws ClassCastException{
		if(root!=null && root.info.getClass()!=a.getClass())
			throw new ClassCastException("tipi incompatibili per l'operazione");
		
		Nodo x=root;
		if(x!=null)
			x=searchIt(x, a);
		if(x!=null)
			return x.info;
		System.out.println("Elemento non trovato\n");
		return null;
	}
	public Binarytreebasic somma(Binarytreebasic b) throws ClassCastException{
		if(b instanceof Binarytree==false)
			throw new ClassCastException("tipi incompatibili per l'operzione");
			
		Nodo x=super.somma(root, b.root, null);
		String s=tree_to_string(x);
		Tipo[] A=nodes(x).toArray(new Tipo[0]);
		return new Binarytree(A, s);
	}
	public Binarytreebasic differenza(Binarytreebasic b) throws ClassCastException{
		if(b instanceof Binarytree==false)
			throw new ClassCastException("tipi incompatibili per l'operzione");
			
		Nodo x=super.differenza(root, b.root, null);
		String s=tree_to_string(x);
		Tipo[] A=nodes(x).toArray(new Tipo[0]);
		return new Binarytree(A, s);
	}
	public Binarytreebasic moltiplicazione(int p) {
		Nodo x=super.moltiplicazione(root, p, null);
		String s=tree_to_string(x);
		Tipo[] A=nodes(x).toArray(new Tipo[0]);
		return new Binarytree(A, s);
	}
	public Binarytreebasic divisione(int p) {
		Nodo x=super.divisione(root, p, null);
		String s=tree_to_string(x);
		Tipo[] A=nodes(x).toArray(new Tipo[0]);
		return new Binarytree(A, s);
	}
}
