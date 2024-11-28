import java.util.Scanner;
public class Programa{
	public static void main(String[] args){
		Scanner entrada = new Scanner(System.in);
		System.out.print("Digite um numero: ");
		int n = Integer.parseInt(entrada.nextLine());
		if(n < 0)
			System.out.println("Não ha raizes para esse numero");
		else{
			double result = Math.sqrt(n);
			System.out.println(result);
		}
	}
}
