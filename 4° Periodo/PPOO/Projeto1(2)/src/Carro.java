public class Carro{
    private String modelo;
    private double velocidade;

    Carro(String modelo){
        this.modelo = modelo;
    }

    public double getVelocidade() {
        return velocidade;
    }

    public String getModelo() {
        return modelo;
    }

    public void acelerar(){
        velocidade += 5;
    }

    public void reduzir(){
        velocidade -= 5;
    }

}