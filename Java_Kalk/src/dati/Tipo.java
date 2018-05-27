package dati;

public interface Tipo {
	Tipo somma(Tipo t);
	Tipo differenza(Tipo t);
	Tipo moltiplicazione(int n);
	Tipo divisione(int n);
	boolean equals(Tipo t);
	boolean min(Tipo t);
	String toString();
}
