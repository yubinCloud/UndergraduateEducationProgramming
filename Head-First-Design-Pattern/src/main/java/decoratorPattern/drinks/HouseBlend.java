package decoratorPattern.drinks;

import decoratorPattern.Beverage;

/**
 * House Blend, 星巴克咖啡名
 */
public class HouseBlend extends Beverage {
    public HouseBlend() {
        description = "House Blend";
    }

    @Override
    public double cost() {
        return 0.89;
    }
}
