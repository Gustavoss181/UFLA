import java.util.ArrayList;
import java.util.List;

public class Termometro {
    private float temperatura;

    private List<TemperatureListener> tempList;

    public Termometro(){
        tempList = new ArrayList<>();
    }

    public void addTemperatureListener(TemperatureListener t){
        tempList.add(t);
    }

    public void setTemperatura(float temperatura) {
        this.temperatura = temperatura;
        for(TemperatureListener t : tempList)
            t.atualizarTemperatura(temperatura);
    }
}
