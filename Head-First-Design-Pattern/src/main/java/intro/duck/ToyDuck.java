package intro.duck;

import intro.Duck;
import intro.fly.FlyNoWay;
import intro.quack.MuteQuack;

/**
 *
 */
public class ToyDuck extends Duck {
    public ToyDuck() {
        super(new FlyNoWay(), new MuteQuack());
    }
}
