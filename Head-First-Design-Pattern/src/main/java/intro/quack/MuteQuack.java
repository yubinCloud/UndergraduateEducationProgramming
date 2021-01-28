package intro.quack;

import intro.QuackBehavior;

/**
 * 不能发出叫声
 */
public class MuteQuack implements QuackBehavior {
    @Override
    public void quack() {
        System.out.println("I can't quack.");
    }
}