public class ContaBancaria {
    private float saldo;
    private float limite;
    private Cliente titular;
    private int numConta;
    private static int ultimaConta = 100;
    private static int taxaRendimento = 3; // %

    public ContaBancaria(float limite, Cliente cliente){
        this(0, limite, cliente);
    }

    public ContaBancaria(float saldo, float limite, Cliente cliente){
        this.saldo = saldo;
        this.limite = limite;
        titular = cliente;
        ultimaConta++;
        numConta = ultimaConta;
    }

    public float getSaldo(){
        return saldo;
    }

    public boolean sacar(float valor){
        if((saldo-valor) > (limite*(-1)))
            saldo -= valor;
        else
            return false;
        return true;
    }

    public void depositar(float valor){
        saldo += valor;
    }

    public String getNomeTitular(){
        return titular.getNome();
    }

    public int getNumConta(){
        return numConta;
    }

    public boolean transferir(float valor, ContaBancaria contaDestino){
        if(sacar(valor)){
            contaDestino.depositar(valor);
            return true;
        }
        else
            return false;
    }

    public void render(){
        saldo += (saldo * taxaRendimento) / 100;
    }

    public static void alterarRendimento(int novaTaxa){
        taxaRendimento = novaTaxa;
    }
}
