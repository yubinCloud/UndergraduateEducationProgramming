package decoratorPattern.condiments;

import decoratorPattern.Beverage;
import decoratorPattern.CondimentDecorator;

/**
 * 抹茶
 */
public class Mocha extends CondimentDecorator {
    private final Beverage beverage;

    public Mocha(Beverage beverage) {
        this.beverage = beverage;
    }

    @Override
    public String getDescription() {
        return beverage.getDescription() + ", Mocha";
    }

    @Override
    public double cost() {
        return 0.20 + beverage.cost();
    }
}
