package intro.duck;

import intro.Duck;
import intro.fly.FlyWithWings;
import intro.quack.Squeak;

/**
 * 野鸭
 */
public class MallardDuck extends Duck {
        public MallardDuck() {
            super(new FlyWithWings(), new Squeak());
        }
}
