public class Mapa implements TemperatureListener {



    @Override
    public void atualizarTemperatura(float temp) {
        System.out.println("Mapa atualizado. Nova temp: " + temp);
    }
    
}
