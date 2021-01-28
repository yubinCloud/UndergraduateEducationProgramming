package observerPattern.scratchImpl.boards;

import observerPattern.scratchImpl.DisplayElement;
import observerPattern.scratchImpl.Observer;

public class PressureBoard implements Observer, DisplayElement {
    private float pressure;

    @Override
    public void display() {
        System.out.println("Current pressure: " + pressure);
    }

    @Override
    public void update(float temperature, float humidity, float pressure) {
        this.pressure = pressure;
        display();
    }
}
