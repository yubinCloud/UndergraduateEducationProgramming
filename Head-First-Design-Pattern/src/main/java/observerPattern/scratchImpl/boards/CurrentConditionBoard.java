package observerPattern.scratchImpl.boards;

import observerPattern.scratchImpl.DisplayElement;
import observerPattern.scratchImpl.Observer;
import observerPattern.scratchImpl.Subject;


public class CurrentConditionBoard implements Observer, DisplayElement {
    private float temperature;
    private float humidity;
    private Subject weatherData;

    @Override
    public void display() {
        System.out.println("Current conditions: " + temperature + "F degrees and " + humidity + "% humidity");
    }

    @Override
    public void update(float temperature, float humidity, float pressure) {
        this.temperature = temperature;
        this.humidity = humidity;
        display();
    }
}
