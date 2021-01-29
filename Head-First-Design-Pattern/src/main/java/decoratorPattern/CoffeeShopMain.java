package decoratorPattern;

import decoratorPattern.condiments.Mocha;
import decoratorPattern.condiments.Soy;
import decoratorPattern.condiments.Whip;
import decoratorPattern.drinks.Espresso;
import decoratorPattern.drinks.HouseBlend;

public class CoffeeShopMain {
    public static void main(String[] args) {
        Beverage b = new Espresso();
        b = new Soy(b);
        b = new Mocha(b);

        System.out.println(b.getDescription() + " $" + b.cost());

        Beverage b2 = new HouseBlend();
        b2 = new Whip(b2);
        b2 = new Mocha(b2);
        b2 = new Soy(b2);

        System.out.println(b2.getDescription() + " $" + b2.cost());
    }
}
