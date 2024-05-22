public class App {
    public static void main(String[] args) throws Exception {
        Termometro t = new Termometro();

        Mapa m = new Mapa();
        Grafico g = new Grafico();

        t.addTemperatureListener(m);
        t.addTemperatureListener(g);
        t.addTemperatureListener(new TemperatureListener() {
            @Override
            public void atualizarTemperatura(float temp) {
                System.out.println("Dados atualizado. Nova temp: " + temp);
            }
        });

        t.setTemperatura(10);
        t.setTemperatura(11);
    }
}
