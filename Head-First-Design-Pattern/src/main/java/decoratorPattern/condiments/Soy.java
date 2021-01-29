package decoratorPattern.condiments;

import decoratorPattern.Beverage;
import decoratorPattern.CondimentDecorator;

/**
 * 大豆
 */
public class Soy extends CondimentDecorator {
    private final Beverage beverage;

    public Soy(Beverage beverage) {
        this.beverage = beverage;
    }

    @Override
    public String getDescription() {
        return beverage.getDescription() + ", Soy";
    }

    @Override
    public double cost() {
        return beverage.cost() + 0.25;
    }
}
