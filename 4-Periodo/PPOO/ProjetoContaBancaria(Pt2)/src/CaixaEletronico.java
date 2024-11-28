import java.util.ArrayList;
import java.util.Scanner;

public class CaixaEletronico {
    private ArrayList<ContaBancaria> contas;
    private Scanner entrada;

    public CaixaEletronico(){
        entrada = new Scanner(System.in);
        contas = new ArrayList<>();
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
        System.out.println("8. Listar todas as contas");
        System.out.println("9. Remover uma conta");
        System.out.println("10. Buscar pelo nome");
        System.out.println("0. Sair");
        System.out.print("Escolha uma opcao: ");
    }

    private boolean menu(){
        boolean sair = false;
        int opcao = Integer.parseInt(entrada.nextLine());
        ContaBancaria conta;
        switch(opcao){
            case 1:
                criarConta();
                break;
            case 2:
                conta = buscarConta();
                if(conta != null)
                    consultarSaldo(conta);
                else
                    System.out.println("Conta nao criada");
                break;
            case 3:
                conta = buscarConta();
                if(conta != null)
                    depositar(conta);
                else
                    System.out.println("Conta nao criada");
                break;
            case 4:
                conta = buscarConta();
                if(conta != null)
                    sacar(conta);
                else
                    System.out.println("Conta nao criada");
                break;
            case 5:
                ContaBancaria conta1 = buscarConta();
                ContaBancaria conta2 = buscarConta();
                if(conta1 != conta2 && conta1 != null && conta2 != null)
                    transferir(conta1, conta2);
                else
                    System.out.println("Erro ao transferir");
                break;
            case 6:
                conta = buscarConta();
                if(conta != null)
                    render(conta);
                else
                    System.out.println("Conta nao criada");
                break;
            case 7:
                alterarRendimento();
                break;
            case 8:
                listarTodasAsContas();
                break;
            case 9:
                int id = buscarContaId();
                if(id != -1)
                    removerConta(id);
                else
                    System.out.println("Conta nao criada");
                break;
            case 10:
                buscarContasNome();
                break;
            case 0:
                sair = true;
                break;
            default:
                System.out.println("Opcao invalida");
                break;
        }

        return sair;
    }

    private ContaBancaria buscarConta(){
        System.out.print("Digite o numero da conta: ");
        int numConta = Integer.parseInt(entrada.nextLine());
        for(ContaBancaria conta : contas)
            if(conta.getNumConta() == numConta)
                return conta;
        
        return null;
    }

    private int buscarContaId(){
        System.out.print("Digite o numero da conta: ");
        int numConta = Integer.parseInt(entrada.nextLine());
        for(int i=0; i<contas.size(); i++)
            if(contas.get(i) != null && contas.get(i).getNumConta() == numConta)
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

        ContaBancaria novaConta;
        if(opcao.equals("s")){
            System.out.print("Digite o saldo: ");
            float saldo = Float.parseFloat(entrada.nextLine());
            novaConta = new ContaBancaria(saldo, 1000, cliente);
        }
        else{
            novaConta = new ContaBancaria(1000, cliente);
        }
        contas.add(novaConta);

        System.out.println("Conta criada. Numero da Conta: " + novaConta.getNumConta());
    }

    private void consultarSaldo(ContaBancaria conta){
        System.out.println("Nome do cliente: " + conta.getNomeTitular());
        System.out.println("Saldo: " + conta.getSaldo());
    }

    private void depositar(ContaBancaria conta){
        System.out.print("Informe um valor: ");
        float valor = Float.parseFloat(entrada.nextLine());
        conta.depositar(valor);
        System.out.println("Deposito efetuado");
    }

    private void sacar(ContaBancaria conta){
        System.out.print("Informe um valor: ");
        float valor = Float.parseFloat(entrada.nextLine());
        if(conta.sacar(valor))
            System.out.println("Saque efetuado");
        else
            System.out.println("Limite excedido");
    }

    private void transferir(ContaBancaria conta1, ContaBancaria conta2){
        System.out.print("Informe um valor: ");
        float valor = Float.parseFloat(entrada.nextLine());
        if(conta1.transferir(valor, conta2))
            System.out.println("Transferencia efetuada");
        else
            System.out.println("Limite excedido");
    }

    private void render(ContaBancaria conta){
        conta.render();
        System.out.println("Novo valor: " + conta.getSaldo());
    }

    private void alterarRendimento(){
        System.out.print("Digite a nova taxa: ");
        int taxa = Integer.parseInt(entrada.nextLine());
        ContaBancaria.alterarRendimento(taxa);
        System.out.println("Rendimento alterado");
    }

    private void listarTodasAsContas(){
        for(ContaBancaria conta : contas)
            System.out.println(conta.getNumConta() + " - " + conta.getNomeTitular());
    }

    private void removerConta(int id){
        if(contas.get(id).getSaldo() == 0){
            contas.remove(id);
            System.out.println("Conta Removida");
        }
        else if(contas.get(id).getSaldo() < 0){
            System.out.println("Nao e possível cancelar contas com saldo disponivel");
        }
        else if(contas.get(id).getSaldo() > 0){
            System.out.println("Nao e possível cancelar contas em debito");
        }
    }

    private void buscarContasNome(){
        System.out.print("Digite um nome (ou parte) para busca: ");
        String subStr = entrada.nextLine();
        for(ContaBancaria conta : contas)
            if(conta.getNomeTitular().contains(subStr))
                System.out.println(conta.getNumConta() + " - " + conta.getNomeTitular());
    }
}
