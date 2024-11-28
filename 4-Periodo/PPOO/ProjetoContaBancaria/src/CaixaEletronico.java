import java.util.Scanner;

public class CaixaEletronico {
    private ContaBancaria contas[];
    private int numContas;
    private int contContas;
    private Scanner entrada;

    public CaixaEletronico(){
        entrada = new Scanner(System.in);
        numContas = 2;
        contas = new ContaBancaria[numContas];
        contContas = 0;
    }

    public void executar(){
        mostrarMenu();
        while(!menu()){
            mostrarMenu();
        }
    }

    private void mostrarMenu(){
        System.out.println("1. Criar conta ");
        System.out.println("2. Consultar saldo ");
        System.out.println("3. Depositar ");
        System.out.println("4. Sacar ");
        System.out.println("5. Transferencia entre contas");
        System.out.println("6. Render uma conta");
        System.out.println("7. Alterar Rendimento");
        System.out.println("8. Sair ");
        System.out.print("Escolhe uma opcao: ");
    }

    private boolean menu(){
        boolean sair = false;
        int opcao = Integer.parseInt(entrada.nextLine());
        int id;
        switch(opcao){
            case 1:
                criarConta();
                criarConta();
                break;
            case 2:
                id = buscarConta();
                if(id != -1)
                    consultarSaldo(id);
                else
                    System.out.println("Conta nao criada");
                break;
            case 3:
                id = buscarConta();
                if(id != -1)
                    depositar(id);
                else
                    System.out.println("Conta nao criada");
                break;
            case 4:
                id = buscarConta();
                if(id != -1)
                    sacar(id);
                else
                    System.out.println("Conta nao criada");
                break;
            case 5:
                int id1 = buscarConta();
                int id2 = buscarConta();
                if(id1 != id2 && id1 != -1 && id2 != -1)
                    transferir(id1, id2);
                else
                    System.out.println("Erro ao transferir");
                break;
            case 6:
                id = buscarConta();
                if(id != -1)
                    render(id);
                else
                    System.out.println("Conta nao criada");
                break;
            case 7:
                alterarRendimento();
                break;
            case 8:
                sair = true;
                break;
            default:
                System.out.println("Opcao invalida");
                break;
        }

        return sair;
    }

    private int buscarConta(){
        System.out.print("Digite o numero da conta: ");
        int numConta = Integer.parseInt(entrada.nextLine());
        for(int i=0; i<numContas; i++)
            if(contas[i] != null && contas[i].getNumConta() == numConta)
                return i;
        
        return -1;
    }

    private void criarConta(){
        System.out.print("Digite o nome no cliente: ");
        String nome = entrada.nextLine();
        System.out.print("Digite o CPF do cliente: ");
        String cpf = entrada.nextLine();
        Cliente cliente = new Cliente(nome, cpf);

        System.out.print("Informar o saldo? (s/n) ");
        String opcao = entrada.nextLine();

        if(opcao.equals("s")){
            System.out.print("Digite o saldo: ");
            float saldo = Float.parseFloat(entrada.nextLine());
            contas[contContas] = new ContaBancaria(saldo, 1000, cliente);
        }
        else{
            contas[contContas] = new ContaBancaria(1000, cliente);
        }

        System.out.println("Conta criada. Numero da Conta: " + contas[contContas].getNumConta());

        contContas++;
    }

    private void consultarSaldo(int id){
        System.out.println("Nome do cliente: " + contas[id].getNomeTitular());
        System.out.println("Saldo: " + contas[id].getSaldo());
    }

    private void depositar(int id){
        System.out.print("Informe um valor: ");
        float valor = Float.parseFloat(entrada.nextLine());
        contas[id].depositar(valor);
        System.out.println("Deposito efetuado");
    }

    private void sacar(int id){
        System.out.print("Informe um valor: ");
        float valor = Float.parseFloat(entrada.nextLine());
        if(contas[id].sacar(valor))
            System.out.println("Saque efetuado");
        else
            System.out.println("Limite excedido");
    }

    private void transferir(int id1, int id2){
        System.out.print("Informe um valor: ");
        float valor = Float.parseFloat(entrada.nextLine());
        if(contas[id1].transferir(valor, contas[id2]))
            System.out.println("Transferencia efetuada");
        else
            System.out.println("Limite excedido");
    }

    private void render(int id){
        contas[id].render();
        System.out.println("Novo valor: " + contas[id].getSaldo());
    }

    private void alterarRendimento(){
        System.out.print("Digite a nova taxa: ");
        int taxa = Integer.parseInt(entrada.nextLine());
        ContaBancaria.alterarRendimento(taxa);
        System.out.println("Rendimento alterado");
    }
}
