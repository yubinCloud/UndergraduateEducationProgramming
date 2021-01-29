package decoratorPattern.condiments;

import decoratorPattern.Beverage;
import decoratorPattern.CondimentDecorator;

/**
 * 蛋奶水果甜点心
 */
public class Whip extends CondimentDecorator {
    private final Beverage beverage;

    public Whip(Beverage beverage) {
        this.beverage = beverage;
    }

    @Override
    public String getDescription() {
        return beverage.getDescription() + ", Whip";
    }

    @Override
    public double cost() {
        return beverage.cost() + 0.5;
    }
}
