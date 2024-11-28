public class Grafico implements TemperatureListener{
    @Override
    public void atualizarTemperatura(float temp) {
        System.out.println("Grafico atualizado. Nova temp: " + temp);
    }
}
