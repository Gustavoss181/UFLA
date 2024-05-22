import java.util.Scanner;

public class Principal {
    private Carro[] carro;
    private int tam;
    private int pos;

    public void mostrarMenu(){
        System.out.println("1) Criar o carro");
        System.out.println("2) Acelerar o carro");
        System.out.println("3) Reduzir a velocidade");
        System.out.println("4) Exibir os dados do carro");
        System.out.println("5) Sair");
    }

    public boolean menu(Scanner entrada, int opcao){
        boolean sair = false;
        String modelo;
        boolean achou = false;
        switch (opcao) {
            case 1:
                if(pos < 5){
                    System.out.print("Modelo: ");
                    modelo = entrada.nextLine();
                    carro[pos] = new Carro(modelo);
                    pos++;
                }
                else{
                    System.out.println("Vetor cheio!");
                }
                break;
            case 2:
                System.out.println("Digite o modelo do carro: ");
                modelo = entrada.nextLine();
                for(int i=0; i<(pos) && !achou; i++){
                    if(carro[i].getModelo().equals(modelo)){
                        carro[i].acelerar();
                        System.out.println("Celera!");
                        achou = true;
                    }
                }
                if(!achou)
                    System.out.println("Carro nao encontrado");
                break;
            case 3:
                System.out.println("Digite o modelo do carro: ");
                modelo = entrada.nextLine();
                for(int i=0; i<(pos) && !achou; i++){
                    if(carro[i].getModelo().equals(modelo)){
                        carro[i].reduzir();
                        System.out.println("Freiaa!");
                        achou = true;
                    }
                }
                if(!achou)
                    System.out.println("Carro nao encontrado");
                break;
            case 4:
                for(int i=0; i<pos; i++){
                    System.out.println("Carro " + i + ":");
                    System.out.println("Modelo: " + carro[i].getModelo());
                    System.out.println("Velocidade: " + carro[i].getVelocidade());
                }
                break;
            case 5:
                System.out.println("Adeus :'(");
                sair = true;
                break;
        
            default:
                break;
        }
        return sair;
    }

    public void executar(){
        Scanner entrada = new Scanner(System.in);
        tam = 5;
        carro = new Carro[tam];
        pos = 0;

        boolean sair = false;
        while(!sair){
            mostrarMenu();
            int opcao = Integer.parseInt(entrada.nextLine());
            sair = menu(entrada, opcao);
        }

        entrada.close();
    }
}
