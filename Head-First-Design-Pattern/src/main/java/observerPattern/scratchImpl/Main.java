package observerPattern.scratchImpl;

import observerPattern.scratchImpl.boards.CurrentConditionBoard;
import observerPattern.scratchImpl.boards.PressureBoard;

public class Main {
    public static void main(String[] args) {
        CurrentConditionBoard conditionBoard = new CurrentConditionBoard();
        PressureBoard pressureBoard = new PressureBoard();

        WeatherData weatherData = new WeatherData();

        // 注册观察者
        weatherData.registerObserver(conditionBoard);
        weatherData.registerObserver(pressureBoard);

        weatherData.setMeasurements(10.0f, 5.8f, 4.0f);
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        weatherData.setMeasurements(16.5f, 4.7f, 3.6f);
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        weatherData.setMeasurements(25.4f, 3.1f, 0.9f);

    }
}
